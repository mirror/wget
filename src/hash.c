/* Hash tables.
   Copyright (C) 2000 Free Software Foundation, Inc.

This file is part of Wget.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

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
   value that corresponds to a key.  hash_table_exists queries whether
   a key is stored in a table at all.  hash_table_remove removes a
   mapping that corresponds to a key.  hash_table_map allows you to
   map through all the entries in a hash table.  hash_table_clear
   clears all the entries from the hash table.

   The number of mappings in a table is not limited, except by the
   amount of memory.  As you add new elements to a table, it regrows
   as necessary.  If you have an idea about how many elements you will
   store, you can provide a hint to hash_table_new().

   The hashing and equality functions are normally provided by the
   user.  For the special (and frequent) case of hashing strings, you
   can use the pre-canned make_string_hash_table(), which provides the
   string hashing function from the Dragon Book, and a string equality
   wrapper around strcmp().

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
     function.

     The above stated rule is quite easy to enforce.  For example, if
     your testing function compares strings case-insensitively, all
     your function needs to do is lower-case the string characters
     before calculating a hash.  That way you have easily guaranteed
     that changes in case will not result in a different hash.

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
   hash_table_remove only marks the spot as deleted rather than really
   making it empty. */

struct mapping {
  void *key;
  void *value;
};

struct hash_table {
  unsigned long (*hash_function) (const void *);
  int (*test_function) (const void *, const void *);

  int size;			/* size of the array */
  int fullness;			/* number of non-empty fields */
  int count;			/* number of non-empty, non-deleted
                                   fields. */

  struct mapping *mappings;
};

#define ENTRY_DELETED ((void *)0xdeadbeef)
#define ENTRY_EMPTY   NULL

#define DELETED_ENTRY_P(ptr) ((ptr) == ENTRY_DELETED)
#define EMPTY_ENTRY_P(ptr)   ((ptr) == ENTRY_EMPTY)

/* Find a prime near, but greather than or equal to SIZE. */

int
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
   HASH_FUNCTION and test function TEST_FUNCTION.  If you wish to
   start out with a "small" table which will be regrown as needed,
   specify 0 as INITIAL_SIZE.  */

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
  ht->fullness = 0;
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
   whose KEY is equal to key, using a linear probing loop.  Returns
   the offset of the mapping in ht->mappings.  This should probably be
   declared inline.  */

static int
find_mapping (struct hash_table *ht, const void *key)
{
  struct mapping *mappings = ht->mappings;
  int size = ht->size;
  int location = ht->hash_function (key) % size;
  while (1)
    {
      struct mapping *mp = mappings + location;
      void *mp_key = mp->key;

      if (EMPTY_ENTRY_P (mp_key))
	return -1;
      else if (DELETED_ENTRY_P (mp_key)
	       || !ht->test_function (key, mp_key))
	{
	  if (++location == size)
	    location = 0;
	}
      else
	return location;
    }
}

/* Get the value that corresponds to the key KEY in the hash table HT.
   If no value is found, return NULL.  Note that NULL is a legal value
   for value; if you are storing NULLs in your hash table, you can use
   hash_table_exists to be sure that a (possibly NULL) value exists in
   the table.  Or, you can use hash_table_get_pair instead of this
   function.  */

void *
hash_table_get (struct hash_table *ht, const void *key)
{
  int location = find_mapping (ht, key);
  if (location < 0)
    return NULL;
  else
    return ht->mappings[location].value;
}

/* Like hash_table_get, but writes out the pointers to both key and
   value.  Returns non-zero on success.  */

int
hash_table_get_pair (struct hash_table *ht, const void *lookup_key,
		     void *orig_key, void *value)
{
  int location = find_mapping (ht, lookup_key);
  if (location < 0)
    return 0;
  else
    {
      struct mapping *mp = ht->mappings + location;
      if (orig_key)
	*(void **)orig_key = mp->key;
      if (value)
	*(void **)value = mp->value;
      return 1;
    }
}

/* Return 1 if KEY exists in HT, 0 otherwise. */

int
hash_table_exists (struct hash_table *ht, const void *key)
{
  return find_mapping (ht, key) >= 0;
}

#define MAX(i, j) (((i) >= (j)) ? (i) : (j))

/* Grow hash table HT as necessary, and rehash all the key-value
   mappings.  */

static void
grow_hash_table (struct hash_table *ht)
{
  int i;
  struct mapping *old_mappings = ht->mappings;
  int old_count = ht->count;	/* for assert() below */
  int old_size = ht->size;

  /* To minimize the number of regrowth, we'd like to resize the hash
     table exponentially.  Normally, this would be done by doubling
     ht->size (and round it to next prime) on each regrow:

         ht->size = prime_size (ht->size * 2);

     But it is possible that the table has large fullness because of
     the many deleted entries.  If that is the case, we don't want to
     blindly grow the table; we just want to rehash it.  For that
     reason, we use ht->count as the relevant parameter.  MAX is used
     only because we don't want to actually shrink the table.  (But
     maybe that's wrong.)  */

  int needed_size = prime_size (ht->count * 3);
  ht->size = MAX (old_size, needed_size);

#if 0
  printf ("growing from %d to %d\n", old_size, ht->size);
#endif

  ht->mappings = xmalloc (ht->size * sizeof (struct mapping));
  memset (ht->mappings, '\0', ht->size * sizeof (struct mapping));

  /* Need to reset these two; hash_table_put will reinitialize them.  */
  ht->fullness = 0;
  ht->count    = 0;
  for (i = 0; i < old_size; i++)
    {
      struct mapping *mp = old_mappings + i;
      void *mp_key = mp->key;

      if (!EMPTY_ENTRY_P (mp_key)
	  && !DELETED_ENTRY_P (mp_key))
	hash_table_put (ht, mp_key, mp->value);
    }
  assert (ht->count == old_count);
  xfree (old_mappings);
}

/* Put VALUE in the hash table HT under the key KEY.  This regrows the
   table if necessary.  */

void
hash_table_put (struct hash_table *ht, const void *key, void *value)
{
  /* Cannot use find_mapping here because we're actually looking for
     an *empty* entry.  */

  struct mapping *mappings = ht->mappings;
  int size = ht->size;
  int location = ht->hash_function (key) % size;
  while (1)
    {
      struct mapping *mp = mappings + location;
      void *mp_key = mp->key;

      if (EMPTY_ENTRY_P (mp_key))
	{
	  ++ht->fullness;
	  ++ht->count;
	just_insert:
	  mp->key = (void *)key; /* const? */
	  mp->value = value;
	  break;
	}
      else if (DELETED_ENTRY_P (mp_key)
	       || !ht->test_function (key, mp_key))
	{
	  if (++location == size)
	    location = 0;
	}
      else			/* equal to key and not deleted */
	{
	  /* We're replacing an existing entry, so ht->count and
             ht->fullness remain unchanged.  */
	  goto just_insert;
	}
    }
  if (ht->fullness * 4 > ht->size * 3)
    /* When fullness exceeds 75% of size, regrow the table. */
    grow_hash_table (ht);
}

/* Remove KEY from HT. */

int
hash_table_remove (struct hash_table *ht, const void *key)
{
  int location = find_mapping (ht, key);
  if (location < 0)
    return 0;
  else
    {
      struct mapping *mappings = ht->mappings;
      struct mapping *mp = mappings + location;
      /* We don't really remove an entry from the hash table: we just
	 mark it as deleted.  This is because there may be other
	 entries located after this entry whose hash points to a
	 location before this entry.  (Example: keys A, B and C have
	 the same hash.  If you were to really *delete* B from the
	 table, C could no longer be found.) */

      /* Optimization addendum: if the mapping that follows LOCATION
	 is already empty, that is a sure sign that nobody depends on
	 LOCATION being non-empty.  (This is because we're using
	 linear probing.  This would not be the case with double
	 hashing.)  In that case, we may safely delete the mapping.  */

      /* This could be generalized so that the all the non-empty
	 locations following LOCATION are simply shifted leftward.  It
	 would make deletion a bit slower, but it would remove the
	 ugly DELETED_ENTRY_P checks from all the rest of the code,
	 making the whole thing faster.  */
      int location_after = (location + 1) == ht->size ? 0 : location + 1;
      struct mapping *mp_after = mappings + location_after;

      if (EMPTY_ENTRY_P (mp_after->key))
	{
	  mp->key = ENTRY_EMPTY;
	  --ht->fullness;
	}
      else
	mp->key = ENTRY_DELETED;

      --ht->count;
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
  ht->fullness = 0;
  ht->count    = 0;
}

/* Map MAPFUN over all the mappings in hash table HT.  MAPFUN is
   called with three arguments: the key, the value, and the CLOSURE.
   Don't add or remove entries from HT while hash_table_map is being
   called, or strange things may happen.  */

void
hash_table_map (struct hash_table *ht,
		int (*mapfun) (void *, void *, void *),
		void *closure)
{
  struct mapping *mappings = ht->mappings;
  int i;
  for (i = 0; i < ht->size; i++)
    {
      struct mapping *mp = mappings + i;
      void *mp_key = mp->key;

      if (!EMPTY_ENTRY_P (mp_key)
	  && !DELETED_ENTRY_P (mp_key))
	if (mapfun (mp_key, mp->value, closure))
	  return;
    }
}

/* Support for hash tables whose keys are strings.  */

/* supposedly from the Dragon Book P436. */
unsigned long
string_hash (const void *sv)
{
  unsigned int h = 0;
  unsigned const char *x = (unsigned const char *) sv;

  while (*x)
    {
      unsigned int g;
      h = (h << 4) + *x++;
      if ((g = h & 0xf0000000) != 0)
	h = (h ^ (g >> 24)) ^ g;
    }

  return h;
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
      if (!hash_table_exists (ht, line))
	hash_table_put (ht, strdup (line), "here I am!");
#if 1
      if (len % 3)
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
  printf ("%d %d %d\n", ht->count, ht->fullness, ht->size);
#endif
  return 0;
}
#endif
