#pragma once

/*
 * header only simple map implementation in C
 *
 * Copyright © 2020 caner selcuk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * -----------------------------------------------------------------
 *                             USAGE
 * -----------------------------------------------------------------
 *
 *  There are two macro defined which are first one for stack frame;
 *  initMap_s (variable_name) ==> _s for stack
 *  initMap_h (variable_name) ==> _h for heap
 *
 *  For key value pair actually pair struct consist of 2 void*
 *  which is generic data pointer, you can create any key,  value pair.
 *  However for string key and generic value pair there are pre-defined
 *  macros which are:
 *
 *   * heap_char(variable_name, const char*) ==> creates string on heap
 *   
 *   * create_pair(pair_name, key_string, value) ==> creates {string, value}
 *     pair on heap.
 *   
 *   * create_pair_char(pair_name, key, string, value) ==> combination of
 *     both heap_char and create_pair macros to create pair in one line on
 *     heap.
 *
 *  Functions:
 *   * mpush_back(map_variable_name, pair) ==> returns nothing, adds pair
 *     end of the map.
 *
 *   * mpop_back(map_variable_name) ==> returns nothing, removes pair
 *     end of the map
 *
 *   * mclear(map_variable_name) ==> returns nothing, removes all of the
 *     entries from the map.
 *
 *   * mdeleteAt(map_variable_name, index) ==> returns nothing, removes
 *     element at specified index.
 *
 *   * mfind_by_string_key(map_variable_name, key_string) ==> returns void*
 *     if it finds match with the key, returns value of corresponding value,
 *     if not, returns NULL.
 *
 *  For stack map you can simply create pairs with:
 *  
 *  pair p1 = { "Personel" , &personel_object };
 *  
 *  and add with:
 *
 *  map_name.mpush_back(&map_name, p1);
 *
 *  For heap map ypu can create { string key, value } pairs with:
 *
 *  create_pair_char(pair_name, key_name, key_string, value_name);
 *
 *  and add with:
 *
 *  map_name->mpush_back(map_name, pair_name); // Pay attention to
 *  first argument for heap map pass directly map_name(because pointer),
 *  for stack map pass map_name adress with '&map_name' !
 *
 *  -----------------------------------------------------------------
 *                           SAMPLE CODE
 *  -----------------------------------------------------------------
 *   
 *  typedef struct
 *  {
 *    int a;
 *    char *name;
 *  } block;
 *
 *  map *
 *  create ()
 *  {
 *    block *q1 = malloc (sizeof (block)); // dynamically allocated pair's value
 *    block *e2 = malloc (sizeof (block)); // dynamically allocated pair's value
 *    block *w3 = malloc (sizeof (block)); // dynamically allocated pair's value
 *    q1->a = 10;
 *    q1->name = "aragorn";
 *    e2->a = 9;
 *    e2->name = "morpheus";
 *    w3->a = 8;
 *    w3->name = "hagrid";
 *    initMap_h (m); // dynamically created map
 *    create_pair_char (p1, k1, "the lord of the rings", q1); // creation of pairs
 *    create_pair_char (p2, k2, "matrix", e2);                // creation of pairs
 *    create_pair_char (p3, k3, "harry potter", w3);          // creation of pairs
 *    m->mpush_back (m, p1);  // Add pairs to map
 *    m->mpush_back (m, p2);  // Add pairs to map
 *    m->mpush_back (m, p3);  // Add pairs to map
 *    return m;   //  return map from function
 *  }
 *
 *  int
 *  main (int argc, char *argv[])
 *  {
 *  #if 0 // heap example
 *  
 *    map *m = create ();
 *    if (m->mfind_by_string_key (m, "jango") != NULL)
 *      printf ("FOUND------------>VALUE: {%d, %s}\n",
 *              ((block *)m->mfind_by_string_key (m, "jango"))->a,
 *              ((block *)m->mfind_by_string_key (m, "jango"))->name);
 *
 *    if (m->mfind_by_string_key (m, "matrix") != NULL)
 *      printf ("FOUND------------>VALUE: {%d, %s}\n",
 *              ((block *)m->mfind_by_string_key (m, "matrix"))->a,
 *              ((block *)m->mfind_by_string_key (m, "matrix"))->name);
 *
 *    for (ssize_t i = 0; i < m->size; ++i)
 *      printf ("KEY: %s, VALUE: b1{%d, %s}\n", (char *)m->pairs[i]->key,
 *              ((block *)m->pairs[i]->value)->a,
 *              ((block *)m->pairs[i]->value)->name);
 *    printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 *    m->mdeleteAt (m, 0);
 *    for (ssize_t i = 0; i < m->size; ++i)
 *      printf ("KEY: %s, VALUE: b1{%d, %s}\n", (char *)m->pairs[i]->key,
 *              ((block *)m->pairs[i]->value)->a,
 *              ((block *)m->pairs[i]->value)->name);
 *    printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 *    m->mpop_back (m);
 *    for (ssize_t i = 0; i < m->size; ++i)
 *      printf ("KEY: %s, VALUE: b1{%d, %s}\n", (char *)m->pairs[i]->key,
 *              ((block *)m->pairs[i]->value)->a,
 *              ((block *)m->pairs[i]->value)->name);
 *    printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 *    m->mclear (m);
 *    printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 *
 *    free (m);  // DON NOT FORGET TO FREE THE MEMORY AFTER USAGE OF MAP
 *
 *  #else // stack example
 *
 *    initMap_s (m);  // stack map initialization
 *    int a = 1998, b = 2001, c = 1980;
 *    m.mpush_back (&m, &(pair){ "google", &a });
 *    m.mpush_back (&m, &(pair){ "yahoo", &b });
 *    m.mpush_back (&m, &(pair){ "linux", &c });
 *    if (m.mfind_by_string_key (&m, "jango") != NULL)
 *      printf ("FOUND------------>VALUE: {%d}\n",
 *              (*(int *)m.mfind_by_string_key (&m, "jango")));
 *    if (m.mfind_by_string_key (&m, "linux") != NULL)
 *      printf ("FOUND------------>VALUE: {%d}\n",
 *              (*(int *)m.mfind_by_string_key (&m, "linux")));
 *
 *    for (ssize_t i = 0; i < m.size; ++i)
 *      printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m.pairs[i]->key,
 *              (*(int *)m.pairs[i]->value));
 *    printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *    m.mdeleteAt (&m, 0);
 *    for (ssize_t i = 0; i < m.size; ++i)
 *      printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m.pairs[i]->key,
 *              (*(int *)m.pairs[i]->value));
 *    printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *    m.mpop_back (&m);
 *    for (ssize_t i = 0; i < m.size; ++i)
 *      printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m.pairs[i]->key,
 *              (*(int *)m.pairs[i]->value));
 *    printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *    m.mclear (&m);
 *    printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *
 *  #endif
 *    return 0;
 *  }
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define heap_char(t, x)                                                       \
  char *(t) = malloc (strlen ((x)) + 1);                                      \
  strncpy ((t), (x), (strlen ((x))) + 1)

#define create_pair(x, y, z)                                                  \
  pair *(x) = malloc (sizeof (pair));                                         \
  (x)->key = (void *)(y);                                                     \
  (x)->value = (void *)(z)

#define create_pair_char(pair, key, str, value)                               \
  heap_char ((key), (str));                                                   \
  create_pair ((pair), (key), (value))

#define initMap_s(x)                                                          \
  map x = { .memberType = 's' };                                              \
  init_map (&x)

#define initMap_h(x)                                                          \
  map *x = malloc (sizeof (map));                                             \
  x->memberType = 'h';                                                        \
  init_map (x)

typedef struct
{
  void *key;
  void *value;
} pair;

typedef struct map map;

struct map
{
  size_t size;
  size_t capacity;
  pair **pairs;
  char memberType;
  void (*mpush_back) (map *, pair *);
  void (*mpop_back) (map *);
  void (*mclear) (map *);
  void (*mdeleteAt) (map *, size_t);
  void *(*mfind_by_string_key) (map *, void *);
};

static void *
mfind_by_string_key (map *m, void *key)
{
  for (ssize_t i = 0; i < m->size; ++i)
    if (memcmp ((void*)key, m->pairs[i]->key, strlen ((char *)key)) == 0)
      return m->pairs[i]->value;
  return NULL;
}

static void
mdeleteAt (map *m, size_t index)
{
  int i = 0;
  if (m)
    {
      if ((index < 0) || (index >= m->size))
        return;
      if (m->memberType == 's')
        {
          m->pairs[index]->key = NULL;
          m->pairs[index]->value = NULL;
          m->pairs[index] = NULL;
        }
      else
        {
          free (m->pairs[index]->key);
          m->pairs[index]->key = NULL;
          free (m->pairs[index]->value);
          m->pairs[index]->value = NULL;
          free (m->pairs[index]);
          m->pairs[index] = NULL;
        }
      for (i = index; i < (m->size - 1); ++i)
        {
          m->pairs[i] = m->pairs[i + 1];
          m->pairs[i + 1] = NULL;
        }
      m->size--;
      if ((m->size > 0) && ((m->size) == (m->capacity / 4)))
        {
          m->capacity /= 2;
          m->pairs = realloc (m->pairs, sizeof (pair *) * m->capacity);
          if (m->pairs == NULL)
            {
              puts ("memory allocation failed!");
              return;
            }
        }
    }
}

static void
mclear (map *m)
{
  if (m->memberType == 's')
    {
      free (m->pairs);
    }
  else
    {
      for (size_t i = 0; i < m->size; ++i)
        {
          free (m->pairs[i]->key);
          m->pairs[i]->key = NULL;
          free (m->pairs[i]->value);
          m->pairs[i]->value = NULL;
          free (m->pairs[i]);
          m->pairs[i] = NULL;
        }
      free (m->pairs);
    }
  m->pairs = NULL;
  m->size = 0;
}

static void
mpush_back (map *m, pair *p)
{
  if (m->size < m->capacity)
    {
      m->pairs[m->size] = p;
      m->size++;
    }
  else
    {
      m->capacity *= 2;
      m->pairs = realloc (m->pairs, sizeof (pair *) * m->capacity);
      if (m->pairs == NULL)
        {
          puts ("memory allocation failed!");
          return;
        }
      m->pairs[m->size] = p;
      m->size++;
    }
}

static void
mpop_back (map *m)
{
  m->mdeleteAt (m, m->size - 1);
}

static void
init_map (map *m) /* INTERNAL FUNCTION DON'T CALL INSTEAD USE initMap_s(variable_name) or initMap_h(variable_name) MACROS */
{
  m->pairs = malloc (2 * sizeof (pair *));
  m->size = 0;
  m->capacity = 2;
  m->mpush_back = mpush_back;
  m->mpop_back = mpop_back;
  m->mdeleteAt = mdeleteAt;
  m->mclear = mclear;
  m->mfind_by_string_key = mfind_by_string_key;
}
