/* Hash tables.
   Copyright (C) 2000 Free Software Foundation, Inc.

This file is part of Wget.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

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
# define xmalloc malloc
# define xrealloc realloc
#endif

/* This file implements simple hash tables based on linear probing.
   The hash table stores key-value pairs in a contiguous array.  Both
   key and value are void pointers that the hash and test functions
   know how to handle.

   Although Knuth & co. recommend double hashing over linear probing,
   we use the latter because it accesses array elements sequentially
   in case of a collision, yielding in better cache behaviour and
   ultimately in better speed.  To avoid collision problems with
   linear probing, we make sure that the table grows as soon as the
   fullness/size ratio exceeds 75%.  */

struct ht_pair {
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

  struct ht_pair *pairs;
};

#define ENTRY_DELETED ((void *)0xdeadbeef)

#define DELETED_ENTRY_P(ptr) ((ptr) == ENTRY_DELETED)
#define EMPTY_ENTRY_P(ptr)   ((ptr) == NULL)

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
  ht->pairs = xmalloc (ht->size * sizeof (struct ht_pair));
  memset (ht->pairs, '\0', ht->size * sizeof (struct ht_pair));
  return ht;
}

/* Free the data associated with hash table HT. */

void
hash_table_destroy (struct hash_table *ht)
{
  free (ht->pairs);
  free (ht);
}

/* Get the value that corresponds to the key KEY in the hash table HT.
   If no value is found, return NULL.  Note that NULL is a legal value
   for value; if you are storing NULLs in your hash table, you can use
   hash_table_exists to be sure that a (possibly NULL) value exists in
   the table.  */

void *
hash_table_get (struct hash_table *ht, const void *key)
{
  int location = ht->hash_function (key) % ht->size;
  while (1)
    {
      struct ht_pair *the_pair = ht->pairs + location;
      if (EMPTY_ENTRY_P (the_pair->key))
	return NULL;
      else if (DELETED_ENTRY_P (the_pair->key)
	       || !ht->test_function (key, the_pair->key))
	{
	  ++location;
	  if (location == ht->size)
	    location = 0;
	}
      else
	return the_pair->value;
    }
}

/* Return 1 if KEY exists in HT, 0 otherwise. */

int
hash_table_exists (struct hash_table *ht, const void *key)
{
  int location = ht->hash_function (key) % ht->size;
  while (1)
    {
      struct ht_pair *the_pair = ht->pairs + location;
      if (EMPTY_ENTRY_P (the_pair->key))
	return 0;
      else if (DELETED_ENTRY_P (the_pair->key)
	       || !ht->test_function (key, the_pair->key))
	{
	  ++location;
	  if (location == ht->size)
	    location = 0;
	}
      else
	return 1;
    }
}

#define MAX(i, j) (((i) >= (j)) ? (i) : (j))

/* Grow hash table HT as necessary, and rehash all the key-value
   pairs.  */

static void
grow_hash_table (struct hash_table *ht)
{
  int i;
  struct ht_pair *old_pairs = ht->pairs;
  int old_count = ht->count;	/* for assert() below */
  int old_size = ht->size;

  /* Normally, the idea is to double ht->size (and round it to next
     prime) on each regrow:

         ht->size = prime_size (ht->size * 2);

     But it is possible that the table has large fullness because of
     the many deleted entries.  If that is the case, we don't want to
     blindly grow the table; we just want to rehash it.  For that
     reason, we use ht->count as the relevant parameter.  MAX is used
     only because we don't want to actually shrink the table.  (But
     maybe that's wrong.)  */

  int needed_size = prime_size (ht->count * 2);
  ht->size = MAX (old_size, needed_size);

  ht->pairs = xmalloc (ht->size * sizeof (struct ht_pair));
  memset (ht->pairs, '\0', ht->size * sizeof (struct ht_pair));

  /* Need to reset these two; hash_table_put will reinitialize them.  */
  ht->fullness = 0;
  ht->count    = 0;
  for (i = 0; i < old_size; i++)
    {
      struct ht_pair *the_pair = old_pairs + i;
      if (!EMPTY_ENTRY_P (the_pair->key)
	  && !DELETED_ENTRY_P (the_pair->key))
	hash_table_put (ht, the_pair->key, the_pair->value);
    }
  assert (ht->count == old_count);
  free (old_pairs);
}

/* Put VALUE in the hash table HT under the key KEY.  This regrows the
   table if necessary.  */

void
hash_table_put (struct hash_table *ht, const void *key, void *value)
{
  int location = ht->hash_function (key) % ht->size;
  while (1)
    {
      struct ht_pair *the_pair = ht->pairs + location;
      if (EMPTY_ENTRY_P (the_pair->key))
	{
	  ++ht->fullness;
	  ++ht->count;
	just_insert:
	  the_pair->key = (void *)key; /* const? */
	  the_pair->value = value;
	  break;
	}
      else if (DELETED_ENTRY_P (the_pair->key))
	{
	  /* We're replacing a deleteed entry, so ht->count gets
             increased, but ht->fullness remains unchanged.  */
	  ++ht->count;
	  goto just_insert;
	}
      else if (ht->test_function (key, the_pair->key))
	{
	  /* We're replacing an existing entry, so ht->count and
             ht->fullness remain unchanged.  */
	  goto just_insert;
	}
      else
	{
	  ++location;
	  if (location == ht->size)
	    location = 0;
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
  int location = ht->hash_function (key) % ht->size;
  while (1)
    {
      struct ht_pair *the_pair = ht->pairs + location;
      if (EMPTY_ENTRY_P (the_pair->key))
	return 0;
      else if (DELETED_ENTRY_P (the_pair->key)
	       || !ht->test_function (key, the_pair->key))
	{
	  ++location;
	  if (location == ht->size)
	    location = 0;
	}
      else
	{
	  /* We don't really remove an entry from the hash table: we
	     just mark it as deleted.  This is because there may be
	     other entries located after this entry whose hash number
	     points to a location before this entry.  (Example: keys
	     A, B and C have the same hash.  If you were to really
	     *delete* B from the table, C could no longer be found.)

	     As an optimization, it might be worthwhile to check
	     whether the immediately preceding entry is empty and, if
	     so, really delete the pair (set it to empty and decrease
	     the fullness along with the count).  I *think* it should
	     be safe.  */
	  the_pair->key = ENTRY_DELETED;
	  --ht->count;
	  return 1;
	}
    }
}

void
hash_table_clear (struct hash_table *ht)
{
  memset (ht->pairs, '\0', ht->size * sizeof (struct ht_pair));
  ht->fullness = 0;
  ht->count    = 0;
}

void
hash_table_map (struct hash_table *ht,
		int (*mapfun) (void *, void *, void *),
		void *closure)
{
  int i;
  for (i = 0; i < ht->size; i++)
    {
      struct ht_pair *the_pair = ht->pairs + i;
      if (!EMPTY_ENTRY_P (the_pair->key)
	  && !DELETED_ENTRY_P (the_pair->key))
	if (mapfun (the_pair->key, the_pair->value, closure))
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

int
string_cmp (const void *s1, const void *s2)
{
  return !strcmp ((const char *)s1, (const char *)s2);
}

struct hash_table *
make_string_hash_table (int initial_size)
{
  return hash_table_new (initial_size, string_hash, string_cmp);
}


#ifdef STANDALONE

#include <stdio.h>
#include <string.h>

int
print_hash_table_mapper (const void *key, void *value, void *count)
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
      hash_table_put (ht, strdup (line), "here I am!");
      if (len % 2)
	hash_table_remove (ht, line);
    }
  print_hash (ht);
#if 0
  printf ("%d %d %d\n", ht->count, ht->fullness, ht->size);
#endif
  return 0;
}
#endif
