/* Hash tables.
   Copyright (C) 2000, 2001 Free Software Foundation, Inc.

This file is part of GNU Wget.

GNU Wget is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

GNU Wget is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wget; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

In addition, as a special exception, the Free Software Foundation
gives permission to link the code of its release of Wget with the
OpenSSL project's "OpenSSL" library (or with modified versions of it
that use the same license as the "OpenSSL" library), and distribute
the linked executables.  You must obey the GNU General Public License
in all respects for all of the code used other than "OpenSSL".  If you
modify this file, you may extend this exception to your version of the
file, but you are not obligated to do so.  If you do not wish to do
so, delete this exception statement from your version.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#else
# include <strings.h>
#endif /* HAVE_STRING_H */
#include <stdlib.h>
#include <assert.h>

#include "wget.h"
#include "utils.h"

#include "hash.h"

#ifdef STANDALONE
# undef xmalloc
# undef xrealloc
# undef xfree

# define xmalloc malloc
# define xrealloc realloc
# define xfree free

# undef TOLOWER
# define TOLOWER(x) ('A' <= (x) && (x) <= 'Z' ? (x) - 32 : (x))
#endif

/* INTERFACE:

   Hash tables are an implementation technique used to implement
   mapping between objects.  Assuming a good hashing function is used,
   they provide near-constant-time access and storing of information.
   Duplicate keys are not allowed.

   This file defines the following entry points: hash_table_new
   creates a hash table, and hash_table_destroy deletes it.
   hash_table_put establishes a mapping between a key and a value.
   hash_table_get retrieves the value that corresponds to a key.
   hash_table_contains queries whether a key is stored in a table at
   all.  hash_table_remove removes a mapping that corresponds to a
   key.  hash_table_map allows you to map through all the entries in a
   hash table.  hash_table_clear clears all the entries from the hash
   table.

   The number of mappings in a table is not limited, except by the
   amount of memory.  As you add new elements to a table, it regrows
   as necessary.  If you have an idea about how many elements you will
   store, you can provide a hint to hash_table_new().

   The hashing and equality functions depend on the type of key and
   are normally provided by the user.  For the special (and frequent)
   case of using string keys, you can use the pre-canned
   make_string_hash_table(), which provides an efficient string
   hashing function, and a string equality wrapper around strcmp().

   When specifying your hash and test functions, make sure the
   following holds true:

   - The test function returns non-zero for keys that are considered
     "equal", zero otherwise.

   - The hash function returns a number that represents the
     "distinctness" of the object.  In more precise terms, it means
     that for any two objects that test "equal" under the test
     function, the hash function MUST produce the same result.

     This does not mean that each distinct object must produce a
     distinct value, only that non-distinct objects must produce the
     same values!  For instance, a hash function that returns 0 for
     any given object is a perfectly valid (albeit extremely bad) hash
     function.  A hash function that hashes a string by adding up all
     its characters is another example of a valid (but quite bad) hash
     function.

     The above stated rule is quite easy to enforce.  For example, if
     your testing function compares strings case-insensitively, all
     your function needs to do is lower-case the string characters
     before calculating a hash.  That way you have easily guaranteed
     that case differences will not result in a different hash.

   - If you care about performance, choose a hash function with as
     good "spreading" as possible.  A good hash function will react to
     even a small change in its input with a completely different
     resulting hash.  Finally, don't make the hash function itself
     overly slow, because you'll be incurring a non-negligible
     overhead to reads and writes to the hash table.

   Note that neither keys nor values are copied when inserted into the
   hash table, so they must exist for the lifetime of the table.  This
   means that e.g. the use of static strings is OK, but objects with a
   shorter life-time need to be copied (with strdup() or the like in
   the case of strings) before being inserted.  */

/* IMPLEMENTATION:

   All the hash mappings (key-value pairs of pointers) are stored in a
   contiguous array.  The position of each mapping is determined by
   the hash value of its key and the size of the table: location :=
   hash(key) % size.  If two different keys end up on the same
   position (hash collision), the one that came second is placed at
   the next empty position following the occupied place.  This
   collision resolution technique is called "linear probing".

   There are more advanced collision resolution mechanisms (quadratic
   probing, double hashing), but we don't use them because they incur
   more non-sequential access to the array, which results in worse
   cache behavior.  Linear probing works well as long as the
   fullness/size ratio is kept below 75%.  We make sure to regrow or
   rehash the hash table whenever this threshold is exceeded.

   Collisions make deletion tricky because finding collisions again
   relies on new empty spots not being created.  That's why
   hash_table_remove is careful to rehash the mappings that follow the
   deleted one.  */

/* When hash table's fullness exceeds this threshold, the hash table
   is resized.  */
#define HASH_FULLNESS_THRESHOLD 0.75

/* The hash table size is multiplied by this factor with each resize.
   This guarantees infrequent resizes.  */
#define HASH_RESIZE_FACTOR 2

struct mapping {
  void *key;
  void *value;
};

struct hash_table {
  unsigned long (*hash_function) PARAMS ((const void *));
  int (*test_function) PARAMS ((const void *, const void *));

  int size;			/* size of the array */
  int count;			/* number of non-empty, non-deleted
                                   fields. */

  int resize_threshold;		/* after size exceeds this number of
				   entries, resize the table.  */
  int prime_offset;		/* the offset of the current prime in
				   the prime table. */

  struct mapping *mappings;	/* the array of mapping pairs. */
};

/* We use NULL key to mark a mapping as empty.  It is consequently
   illegal to store NULL keys.  */
#define NON_EMPTY(mp) (mp->key != NULL)

/* "Next" mapping is the mapping after MP, but wrapping back to
   MAPPINGS when MP would reach MAPPINGS+SIZE.  */
#define NEXT_MAPPING(mp, mappings, size) (mp != mappings + (size - 1)	\
					  ? mp + 1 : mappings)

/* Loop over non-empty mappings starting at MP. */
#define LOOP_NON_EMPTY(mp, mappings, size)				\
  for (; NON_EMPTY (mp); mp = NEXT_MAPPING (mp, mappings, size))

/* #### We might want to multiply with the "golden ratio" here to get
   better randomness for keys that do not result from a good hash
   function.  This is currently not a problem in Wget because we only
   use the string hash tables.  */

#define HASH_POSITION(ht, key) (ht->hash_function (key) % ht->size)

/* Find a prime near, but greather than or equal to SIZE.  Of course,
   the primes are not calculated, but looked up from a table.  The
   table does not contain all primes in range, just a selection useful
   for this purpose.

   PRIME_OFFSET is a minor optimization: if specified, it starts the
   search for the prime number beginning with the specific offset in
   the prime number table.  The final offset is stored in the same
   variable.  */

static int
prime_size (int size, int *prime_offset)
{
  static const unsigned long primes [] = {
    13, 19, 29, 41, 59, 79, 107, 149, 197, 263, 347, 457, 599, 787, 1031,
    1361, 1777, 2333, 3037, 3967, 5167, 6719, 8737, 11369, 14783,
    19219, 24989, 32491, 42257, 54941, 71429, 92861, 120721, 156941,
    204047, 265271, 344857, 448321, 582821, 757693, 985003, 1280519,
    1664681, 2164111, 2813353, 3657361, 4754591, 6180989, 8035301,
    10445899, 13579681, 17653589, 22949669, 29834603, 38784989,
    50420551, 65546729, 85210757, 110774011, 144006217, 187208107,
    243370577, 316381771, 411296309, 534685237, 695090819, 903618083,
    1174703521, 1527114613, 1985248999,
    (unsigned long)0x99d43ea5, (unsigned long)0xc7fa5177
  };
  int i = *prime_offset;

  for (; i < countof (primes); i++)
    if (primes[i] >= size)
      {
	/* Set the offset to the next prime.  That is safe because,
	   next time we are called, it will be with a larger SIZE,
	   which means we could never return the same prime anyway.
	   (If that is not the case, the caller can simply reset
	   *prime_offset.)  */
	*prime_offset = i + 1;
	return primes[i];
      }

  abort ();
  return 0;
}

/* Create a hash table with hash function HASH_FUNCTION and test
   function TEST_FUNCTION.  The table is empty (its count is 0), but
   pre-allocated to store at least ITEMS items.

   ITEMS is the number of items that the table can accept without
   needing to resize.  It is useful when creating a table that is to
   be immediately filled with a known number of items.  In that case,
   the regrows are a waste of time, and specifying ITEMS correctly
   will avoid them altogether.

   Note that hash tables grow dynamically regardless of ITEMS.  The
   only use of ITEMS is to preallocate the table and avoid unnecessary
   dynamic regrows.  Don't bother making ITEMS prime because it's not
   used as size unchanged.  To start with a small table that grows as
   needed, simply specify zero ITEMS.

   If HASH_FUNCTION is not provided, identity table is assumed,
   i.e. key pointers are compared as keys.  If you want strings with
   equal contents to hash the same, use make_string_hash_table.  */

struct hash_table *
hash_table_new (int items,
		unsigned long (*hash_function) (const void *),
		int (*test_function) (const void *, const void *))
{
  int size;
  struct hash_table *ht
    = (struct hash_table *)xmalloc (sizeof (struct hash_table));

  ht->hash_function = hash_function ? hash_function : ptrhash;
  ht->test_function = test_function ? test_function : ptrcmp;

  ht->prime_offset = 0;

  /* Calculate the size that ensures that the table will store at
     least ITEMS keys without the need to resize.  */
  size = 1 + items / HASH_FULLNESS_THRESHOLD;
  size = prime_size (size, &ht->prime_offset);
  ht->size = size;
  ht->resize_threshold = size * HASH_FULLNESS_THRESHOLD;
  /*assert (ht->resize_threshold >= items);*/

  ht->mappings = xmalloc (ht->size * sizeof (struct mapping));
  memset (ht->mappings, '\0', ht->size * sizeof (struct mapping));

  ht->count = 0;

  return ht;
}

/* Free the data associated with hash table HT. */

void
hash_table_destroy (struct hash_table *ht)
{
  xfree (ht->mappings);
  xfree (ht);
}

/* The heart of most functions in this file -- find the mapping whose
   KEY is equal to key, using linear probing.  Returns the mapping
   that matches KEY, or the first empty mapping if none matches.  */

static inline struct mapping *
find_mapping (const struct hash_table *ht, const void *key)
{
  struct mapping *mappings = ht->mappings;
  int size = ht->size;
  struct mapping *mp = mappings + HASH_POSITION (ht, key);
  int (*equals) PARAMS ((const void *, const void *)) = ht->test_function;

  LOOP_NON_EMPTY (mp, mappings, size)
    if (equals (key, mp->key))
      break;
  return mp;
}

/* Get the value that corresponds to the key KEY in the hash table HT.
   If no value is found, return NULL.  Note that NULL is a legal value
   for value; if you are storing NULLs in your hash table, you can use
   hash_table_contains to be sure that a (possibly NULL) value exists
   in the table.  Or, you can use hash_table_get_pair instead of this
   function.  */

void *
hash_table_get (const struct hash_table *ht, const void *key)
{
  struct mapping *mp = find_mapping (ht, key);
  if (NON_EMPTY (mp))
    return mp->value;
  else
    return NULL;
}

/* Like hash_table_get, but writes out the pointers to both key and
   value.  Returns non-zero on success.  */

int
hash_table_get_pair (const struct hash_table *ht, const void *lookup_key,
		     void *orig_key, void *value)
{
  struct mapping *mp = find_mapping (ht, lookup_key);
  if (NON_EMPTY (mp))
    {
      if (orig_key)
	*(void **)orig_key = mp->key;
      if (value)
	*(void **)value = mp->value;
      return 1;
    }
  else
    return 0;
}

/* Return 1 if HT contains KEY, 0 otherwise. */

int
hash_table_contains (const struct hash_table *ht, const void *key)
{
  struct mapping *mp = find_mapping (ht, key);
  return NON_EMPTY (mp);
}

/* Grow hash table HT as necessary, and rehash all the key-value
   mappings.  */

static void
grow_hash_table (struct hash_table *ht)
{
  struct mapping *old_mappings = ht->mappings;
  struct mapping *old_end      = ht->mappings + ht->size;
  struct mapping *mp, *mappings;
  int newsize;

  newsize = prime_size (ht->size * HASH_RESIZE_FACTOR, &ht->prime_offset);
#if 0
  printf ("growing from %d to %d; fullness %.2f%% to %.2f%%\n",
	  ht->size, newsize,
	  100.0 * ht->count / ht->size,
	  100.0 * ht->count / newsize);
#endif

  ht->size = newsize;
  ht->resize_threshold = newsize * HASH_FULLNESS_THRESHOLD;

  mappings = xmalloc (ht->size * sizeof (struct mapping));
  memset (mappings, '\0', ht->size * sizeof (struct mapping));
  ht->mappings = mappings;

  for (mp = old_mappings; mp < old_end; mp++)
    if (NON_EMPTY (mp))
      {
	struct mapping *new_mp = mappings + HASH_POSITION (ht, mp->key);
	/* We don't need to test for uniqueness of keys because all
	   the keys come from the hash table and are therefore known
	   to be unique.  */
	LOOP_NON_EMPTY (new_mp, mappings, newsize)
	  ;
	*new_mp = *mp;
      }

  xfree (old_mappings);
}

/* Put VALUE in the hash table HT under the key KEY.  This regrows the
   table if necessary.  */

void
hash_table_put (struct hash_table *ht, const void *key, void *value)
{
  struct mapping *mp = find_mapping (ht, key);
  if (NON_EMPTY (mp))
    {
      /* update existing item */
      mp->key   = (void *)key; /* const? */
      mp->value = value;
      return;
    }

  /* If adding the item would make the table exceed max. fullness,
     grow the table first.  */
  if (ht->count >= ht->resize_threshold)
    {
      grow_hash_table (ht);
      mp = find_mapping (ht, key);
    }

  /* add new item */
  ++ht->count;
  mp->key   = (void *)key;	/* const? */
  mp->value = value;
}

/* Remove a mapping that matches KEY from HT.  Return 0 if there was
   no such entry; return 1 if an entry was removed.  */

int
hash_table_remove (struct hash_table *ht, const void *key)
{
  struct mapping *mp = find_mapping (ht, key);
  if (!NON_EMPTY (mp))
    return 0;
  else
    {
      int size = ht->size;
      struct mapping *mappings = ht->mappings;

      mp->key = NULL;
      --ht->count;

      /* Rehash all the entries following MP.  The alternative
	 approach is to mark the entry as deleted, i.e. create a
	 "tombstone".  That makes remove faster, but leaves a lot of
	 garbage and slows down hash_table_get and hash_table_put.  */

      mp = NEXT_MAPPING (mp, mappings, size);
      LOOP_NON_EMPTY (mp, mappings, size)
	{
	  const void *key2 = mp->key;
	  struct mapping *mp_new = mappings + HASH_POSITION (ht, key2);

	  /* Find the new location for the key. */

	  LOOP_NON_EMPTY (mp_new, mappings, size)
	    if (key2 == mp_new->key)
	      /* The mapping MP (key2) is already where we want it (in
		 MP_NEW's "chain" of keys.)  */
	      goto next_rehash;

	  *mp_new = *mp;
	  mp->key = NULL;

	next_rehash:
	  ;
	}
      return 1;
    }
}

/* Clear HT of all entries.  After calling this function, the count
   and the fullness of the hash table will be zero.  The size will
   remain unchanged.  */

void
hash_table_clear (struct hash_table *ht)
{
  memset (ht->mappings, '\0', ht->size * sizeof (struct mapping));
  ht->count = 0;
}

/* Map MAPFUN over all the mappings in hash table HT.  MAPFUN is
   called with three arguments: the key, the value, and MAPARG.

   It is undefined what happens if you add or remove entries in the
   hash table while hash_table_map is running.  The exception is the
   entry you're currently mapping over; you may remove or change that
   entry.  */

void
hash_table_map (struct hash_table *ht,
		int (*mapfun) (void *, void *, void *),
		void *maparg)
{
  struct mapping *mp  = ht->mappings;
  struct mapping *end = ht->mappings + ht->size;

  for (; mp < end; mp++)
    if (NON_EMPTY (mp))
      {
	void *key;
      repeat:
	key = mp->key;
	if (mapfun (key, mp->value, maparg))
	  return;
	/* hash_table_remove might have moved the adjacent
	   mappings. */
	if (mp->key != key && NON_EMPTY (mp))
	  goto repeat;
      }
}

/* Return the number of elements in the hash table.  This is not the
   same as the physical size of the hash table, which is always
   greater than the number of elements.  */

int
hash_table_count (const struct hash_table *ht)
{
  return ht->count;
}

/* Functions from this point onward are meant for convenience and
   don't strictly belong to this file.  However, this is as good a
   place for them as any.  */

/*
 * Support for hash tables whose keys are strings.
 *
 */
   
/* 31 bit hash function.  Taken from Gnome's glib, modified to use
   standard C types.

   We used to use the popular hash function from the Dragon Book, but
   this one seems to perform much better.  */

unsigned long
string_hash (const void *key)
{
  const char *p = key;
  unsigned int h = *p;
  
  if (h)
    for (p += 1; *p != '\0'; p++)
      h = (h << 5) - h + *p;
  
  return h;
}

/* Frontend for strcmp usable for hash tables. */

int
string_cmp (const void *s1, const void *s2)
{
  return !strcmp ((const char *)s1, (const char *)s2);
}

/* Return a hash table of preallocated to store at least ITEMS items
   suitable to use strings as keys.  */

struct hash_table *
make_string_hash_table (int items)
{
  return hash_table_new (items, string_hash, string_cmp);
}

/*
 * Support for hash tables whose keys are strings, but which are
 * compared case-insensitively.
 *
 */

/* Like string_hash, but produce the same hash regardless of the case. */

static unsigned long
string_hash_nocase (const void *key)
{
  const char *p = key;
  unsigned int h = TOLOWER (*p);
  
  if (h)
    for (p += 1; *p != '\0'; p++)
      h = (h << 5) - h + TOLOWER (*p);
  
  return h;
}

/* Like string_cmp, but doing case-insensitive compareison. */

static int
string_cmp_nocase (const void *s1, const void *s2)
{
  return !strcasecmp ((const char *)s1, (const char *)s2);
}

/* Like make_string_hash_table, but uses string_hash_nocase and
   string_cmp_nocase.  */

struct hash_table *
make_nocase_string_hash_table (int items)
{
  return hash_table_new (items, string_hash_nocase, string_cmp_nocase);
}

/* Hashing of pointers.  Used for hash tables that are keyed by
   pointer identity.  (Common Lisp calls them EQ hash tables, and Java
   calls them IdentityHashMaps.)  */

unsigned long
ptrhash (const void *ptr)
{
  unsigned long key = (unsigned long)ptr;
  key += (key << 12);
  key ^= (key >> 22);
  key += (key << 4);
  key ^= (key >> 9);
  key += (key << 10);
  key ^= (key >> 2);
  key += (key << 7);
  key ^= (key >> 12);
#if SIZEOF_LONG > 4
  key += (key << 44);
  key ^= (key >> 54);
  key += (key << 36);
  key ^= (key >> 41);
  key += (key << 42);
  key ^= (key >> 34);
  key += (key << 39);
  key ^= (key >> 44);
#endif
  return key;
}

int
ptrcmp (const void *ptr1, const void *ptr2)
{
  return ptr1 == ptr2;
}

#if 0
/* Currently unused: hashing of integers. */

unsigned long
inthash (unsigned int key)
{
  key += (key << 12);
  key ^= (key >> 22);
  key += (key << 4);
  key ^= (key >> 9);
  key += (key << 10);
  key ^= (key >> 2);
  key += (key << 7);
  key ^= (key >> 12);
  return key;
}
#endif

#ifdef STANDALONE

#include <stdio.h>
#include <string.h>

int
print_hash_table_mapper (void *key, void *value, void *count)
{
  ++*(int *)count;
  printf ("%s: %s\n", (const char *)key, (char *)value);
  return 0;
}

void
print_hash (struct hash_table *sht)
{
  int debug_count = 0;
  hash_table_map (sht, print_hash_table_mapper, &debug_count);
  assert (debug_count == sht->count);
}

int
main (void)
{
  struct hash_table *ht = make_string_hash_table (0);
  char line[80];
  while ((fgets (line, sizeof (line), stdin)))
    {
      int len = strlen (line);
      if (len <= 1)
	continue;
      line[--len] = '\0';
      if (!hash_table_contains (ht, line))
	hash_table_put (ht, strdup (line), "here I am!");
#if 1
      if (len % 5 == 0)
	{
	  char *line_copy;
	  if (hash_table_get_pair (ht, line, &line_copy, NULL))
	    {
	      hash_table_remove (ht, line);
	      xfree (line_copy);
	    }
	}
#endif
    }
#if 0
  print_hash (ht);
#endif
#if 1
  printf ("%d %d\n", ht->count, ht->size);
#endif
  return 0;
}
#endif
