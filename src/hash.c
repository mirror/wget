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
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

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
#endif

/* INTERFACE:

   Hash tables are an implementation technique used to implement
   mapping between objects.  Provided a good hashing function is used,
   they guarantee constant-time access and storing of information.
   Duplicate keys are not allowed.

   The basics are all covered.  hash_table_new creates a hash table,
   and hash_table_destroy deletes it.  hash_table_put establishes a
   mapping between a key and a value.  hash_table_get retrieves the
   value that corresponds to a key.  hash_table_contains queries
   whether a key is stored in a table at all.  hash_table_remove
   removes a mapping that corresponds to a key.  hash_table_map allows
   you to map through all the entries in a hash table.
   hash_table_clear clears all the entries from the hash table.

   The number of mappings in a table is not limited, except by the
   amount of memory.  As you add new elements to a table, it regrows
   as necessary.  If you have an idea about how many elements you will
   store, you can provide a hint to hash_table_new().

   The hashing and equality functions are normally provided by the
   user.  For the special (and frequent) case of hashing strings, you
   can use the pre-canned make_string_hash_table(), which provides an
   efficient string hashing function, and a string equality wrapper
   around strcmp().

   When specifying your own hash and test functions, make sure the
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

   - (optional) Choose the hash function to get as good "spreading" as
     possible.  A good hash function will react to even a small change
     in its input with a completely different resulting hash.
     Finally, don't make your hash function extremely slow, because
     you're then defeating the purpose of hashing.

   Note that neither keys nor values are copied when inserted into the
   hash table, so they must exist for the lifetime of the table.  This
   means that e.g. the use of static strings is OK, but objects with a
   shorter life-time need to be copied (with strdup() or the like in
   the case of strings) before being inserted.  */

/* IMPLEMENTATION:

   All the hash mappings (key-value pairs of pointers) are stored in a
   contiguous array.  The position of each mapping is determined by
   applying the hash function to the key: location = hash(key) % size.
   If two different keys end up on the same position, the collision is
   resolved by placing the second mapping at the next empty place in
   the array following the occupied place.  This method of collision
   resolution is called "linear probing".

   There are more advanced collision resolution mechanisms (quadratic
   probing, double hashing), but we don't use them because they
   involve more non-sequential access to the array, and therefore
   worse cache behavior.  Linear probing works well as long as the
   fullness/size ratio is kept below 75%.  We make sure to regrow or
   rehash the hash table whenever this threshold is exceeded.

   Collisions make deletion tricky because finding collisions again
   relies on new empty spots not being created.  That's why
   hash_table_remove is careful to rehash the mappings that follow the
   deleted one.  */

struct mapping {
  void *key;
  void *value;
};

struct hash_table {
  unsigned long (*hash_function) (const void *);
  int (*test_function) (const void *, const void *);

  int size;			/* size of the array */
  int count;			/* number of non-empty, non-deleted
                                   fields. */

  int resize_threshold;		/* after size exceeds this number of
				   entries, resize the table.  */

  struct mapping *mappings;
};

#define EMPTY_MAPPING_P(mp)  ((mp)->key == NULL)
#define NEXT_MAPPING(mp, mappings, size) (mp == mappings + (size - 1)	\
					  ? mappings : mp + 1)

#define LOOP_NON_EMPTY(mp, mappings, size)				\
  for (; !EMPTY_MAPPING_P (mp); mp = NEXT_MAPPING (mp, mappings, size))

#define HASH_POSITION(ht, key) (ht->hash_function (key) % ht->size)

/* Find a prime near, but greather than or equal to SIZE. */

static int
prime_size (int size)
{
  static const unsigned long primes [] = {
    19, 29, 41, 59, 79, 107, 149, 197, 263, 347, 457, 599, 787, 1031,
    1361, 1777, 2333, 3037, 3967, 5167, 6719, 8737, 11369, 14783,
    19219, 24989, 32491, 42257, 54941, 71429, 92861, 120721, 156941,
    204047, 265271, 344857, 448321, 582821, 757693, 985003, 1280519,
    1664681, 2164111, 2813353, 3657361, 4754591, 6180989, 8035301,
    10445899, 13579681, 17653589, 22949669, 29834603, 38784989,
    50420551, 65546729, 85210757, 110774011, 144006217, 187208107,
    243370577, 316381771, 411296309, 534685237, 695090819, 903618083,
    1174703521, 1527114613, 1985248999, 2580823717UL, 3355070839UL
  };
  int i;
  for (i = 0; i < ARRAY_SIZE (primes); i++)
    if (primes[i] >= size)
      return primes[i];
  /* huh? */
  return size;
}

/* Create a hash table of INITIAL_SIZE with hash function
   HASH_FUNCTION and test function TEST_FUNCTION.  INITIAL_SIZE will
   be rounded to the next prime, so you don't have to worry about it
   being a prime number.

   Consequently, if you wish to start out with a "small" table which
   will be regrown as needed, specify INITIAL_SIZE 0.  */

struct hash_table *
hash_table_new (int initial_size,
		unsigned long (*hash_function) (const void *),
		int (*test_function) (const void *, const void *))
{
  struct hash_table *ht
    = (struct hash_table *)xmalloc (sizeof (struct hash_table));

  ht->hash_function = hash_function;
  ht->test_function = test_function;

  ht->size = prime_size (initial_size);
  ht->resize_threshold = ht->size * 3 / 4;

  ht->count    = 0;

  ht->mappings = xmalloc (ht->size * sizeof (struct mapping));
  memset (ht->mappings, '\0', ht->size * sizeof (struct mapping));

  return ht;
}

/* Free the data associated with hash table HT. */

void
hash_table_destroy (struct hash_table *ht)
{
  xfree (ht->mappings);
  xfree (ht);
}

/* The heart of almost all functions in this file -- find the mapping
   whose KEY is equal to key, using linear probing.  Returns the
   mapping that matches KEY, or NULL if none matches.  */

static inline struct mapping *
find_mapping (struct hash_table *ht, const void *key)
{
  struct mapping *mappings = ht->mappings;
  int size = ht->size;
  struct mapping *mp = mappings + HASH_POSITION (ht, key);
  int (*equals) (const void *, const void *) = ht->test_function;

  LOOP_NON_EMPTY (mp, mappings, size)
    if (equals (key, mp->key))
      return mp;
  return NULL;
}

/* Get the value that corresponds to the key KEY in the hash table HT.
   If no value is found, return NULL.  Note that NULL is a legal value
   for value; if you are storing NULLs in your hash table, you can use
   hash_table_contains to be sure that a (possibly NULL) value exists
   in the table.  Or, you can use hash_table_get_pair instead of this
   function.  */

void *
hash_table_get (struct hash_table *ht, const void *key)
{
  struct mapping *mp = find_mapping (ht, key);
  if (mp)
    return mp->value;
  else
    return NULL;
}

/* Like hash_table_get, but writes out the pointers to both key and
   value.  Returns non-zero on success.  */

int
hash_table_get_pair (struct hash_table *ht, const void *lookup_key,
		     void *orig_key, void *value)
{
  struct mapping *mp = find_mapping (ht, lookup_key);

  if (mp)
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
hash_table_contains (struct hash_table *ht, const void *key)
{
  return find_mapping (ht, key) != NULL;
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

  newsize = prime_size (ht->size * 2);
#if 0
  printf ("growing from %d to %d\n", ht->size, newsize);
#endif

  ht->size = newsize;
  ht->resize_threshold = newsize * 3 / 4;

  mappings = xmalloc (ht->size * sizeof (struct mapping));
  memset (mappings, '\0', ht->size * sizeof (struct mapping));
  ht->mappings = mappings;

  for (mp = old_mappings; mp < old_end; mp++)
    if (!EMPTY_MAPPING_P (mp))
      {
	struct mapping *new_mp = mappings + HASH_POSITION (ht, mp->key);
	/* We don't need to call test function and worry about
	   collisions because all the keys come from the hash table
	   and are therefore guaranteed to be unique.  */
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
  struct mapping *mappings = ht->mappings;
  int size = ht->size;
  int (*equals) (const void *, const void *) = ht->test_function;

  struct mapping *mp = mappings + HASH_POSITION (ht, key);

  LOOP_NON_EMPTY (mp, mappings, size)
    if (equals (key, mp->key))
      {
	mp->key   = (void *)key; /* const? */
	mp->value = value;
	return;
      }

  ++ht->count;
  mp->key   = (void *)key;	/* const? */
  mp->value = value;

  if (ht->count > ht->resize_threshold)
    /* When table is 75% full, regrow it. */
    grow_hash_table (ht);
}

/* Remove a mapping that matches KEY from HT.  Return 0 if there was
   no such entry; return 1 if an entry was removed.  */

int
hash_table_remove (struct hash_table *ht, const void *key)
{
  struct mapping *mp = find_mapping (ht, key);
  if (!mp)
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
   called with three arguments: the key, the value, and the CLOSURE.

   It is undefined what happens if you add or remove entries in the
   hash table while hash_table_map is running.  The exception is the
   entry you're currently mapping over; you may remove or change that
   entry.  */

void
hash_table_map (struct hash_table *ht,
		int (*mapfun) (void *, void *, void *),
		void *closure)
{
  struct mapping *mp  = ht->mappings;
  struct mapping *end = ht->mappings + ht->size;

  for (; mp < end; mp++)
    if (!EMPTY_MAPPING_P (mp))
      {
	void *key;
      repeat:
	key = mp->key;
	if (mapfun (key, mp->value, closure))
	  return;
	/* hash_table_remove might have moved the adjacent
	   mappings. */
	if (mp->key != key && !EMPTY_MAPPING_P (mp))
	  goto repeat;
      }
}

/* Return the number of elements in the hash table.  This is not the
   same as the physical size of the hash table, which is always
   greater than the number of elements.  */

int
hash_table_count (struct hash_table *ht)
{
  return ht->count;
}

/* Functions from this point onward are meant for convenience and
   don't strictly belong to this file.  However, this is as good a
   place for them as any.  */

/* ========
   Support for hash tables whose keys are strings.
   ======== */

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

/* Return a hash table of initial size INITIAL_SIZE suitable to use
   strings as keys.  */

struct hash_table *
make_string_hash_table (int initial_size)
{
  return hash_table_new (initial_size, string_hash, string_cmp);
}

/* ========
   Support for hash tables whose keys are strings, but which are
   compared case-insensitively.
   ======== */

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
make_nocase_string_hash_table (int initial_size)
{
  return hash_table_new (initial_size, string_hash_nocase, string_cmp_nocase);
}

#if 0
/* If I ever need it: hashing of integers. */

unsigned int
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
