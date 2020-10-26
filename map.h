
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
 *  macro which is:
 *   
 *   * create_pair_with_strig_key(pair_name, str, val) ==> creates pair with
 *   {string, value}
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
 *   * destroy_map(map_name) ==> returns nothing, frees map
 *
 *   * mreplace_element(map_name, index, pair) ==> returns nothing, replaces
 *     pair at specified index.
 *
 *  For stack map you can simply create pairs with:
 *  
 *  pair p1 = { "Personel" , &personel_object };
 *  
 *  and add with:
 *
 *  mpush_back(&map_name, p1);
 *
 *  For heap map you can create { string key, value } pairs with:
 *
 *  create_pair_with_strig_key(pair_name, str, val);
 *
 *  and add with:
 *
 *  mpush_back(map_name, pair_name); // Pay attention to
 *  first argument for heap map pass directly map_name(because pointer),
 *  for stack map pass map_name adress with '&map_name' !
 *
 *  -----------------------------------------------------------------
 *                           SAMPLE CODE
 *  -----------------------------------------------------------------
 *   
 *  #include "map.h"
 *    typedef struct
 *    {
 *      int a;
 *      char *name;
 *    } block;
 *  
 *    map *
 *    create ()
 *    {
 *      block *q1 = malloc (sizeof (block)); // dynamically allocated pair's value
 *      block *e2 = malloc (sizeof (block)); // dynamically allocated pair's value
 *      block *w3 = malloc (sizeof (block)); // dynamically allocated pair's value
 *      q1->a = 10;
 *      q1->name = strdup("aragorn");
 *      e2->a = 9;
 *      e2->name = strdup("morpheus");
 *      w3->a = 8;
 *      w3->name = strdup("hagrid");
 *      initMap_h (m); // dynamically created map
 *      create_pair_with_strig_key (p1, "the lord of the rings", q1); // creation of pairs
 *      create_pair_with_strig_key (p2, "matrix", e2);                // creation of pairs
 *      create_pair_with_strig_key (p3, "harry potter", w3);          // creation of pairs
 *      mpush_back (m, p1);  // Add pairs to map
 *      mpush_back (m, p2);  // Add pairs to map
 *      mpush_back (m, p3);  // Add pairs to map
 *      return m;   //  return map from function
 *    }
 *  
 *    int
 *    main (int argc, char *argv[])
 *    {
 *    #if 1 // heap example
 *    
 *      map *m = create ();
 *      if (mfind_by_string_key (m, "jango") != NULL)
 *        printf ("FOUND------------>VALUE: {%d, %s}\n",
 *                ((block *)mfind_by_string_key (m, "jango"))->a,
 *                ((block *)mfind_by_string_key (m, "jango"))->name);
 *  
 *      if (mfind_by_string_key (m, "matrix") != NULL)
 *        printf ("FOUND------------>VALUE: {%d, %s}\n",
 *                ((block *)mfind_by_string_key (m, "matrix"))->a,
 *                ((block *)mfind_by_string_key (m, "matrix"))->name);
 *  
 *      for (ssize_t i = 0; i < m->size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d, %s}\n", (char *)m->pairs[i]->key,
 *                ((block *)m->pairs[i]->value)->a,
 *                ((block *)m->pairs[i]->value)->name);
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 *      free(((block*)m->pairs[0]->value)->name);
 *      mdeleteAt (m, 0);
 *      for (ssize_t i = 0; i < m->size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d, %s}\n", (char *)m->pairs[i]->key,
 *                ((block *)m->pairs[i]->value)->a,
 *                ((block *)m->pairs[i]->value)->name);
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 *      free(((block*)m->pairs[m->size-1]->value)->name);
 *      mpop_back (m);
 *      for (ssize_t i = 0; i < m->size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d, %s}\n", (char *)m->pairs[i]->key,
 *                ((block *)m->pairs[i]->value)->a,
 *                ((block *)m->pairs[i]->value)->name);
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 *      free(((block*)m->pairs[0]->value)->name);
 *      mclear (m);
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 *  
 *      mdeleteAt(m, 321);
 *      mdeleteAt(m, 0);
 *      mpop_back(m);
 *      block* extra_data = malloc (sizeof(block));
 *      extra_data->a = 7;
 *      extra_data->name = strdup("age of empires");
 *      create_pair_with_strig_key (p4, "EA GAMES", extra_data); // creation of pairs
 *      mpush_back(m, p4);
 *      for (ssize_t i = 0; i < m->size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d, %s}\n", (char *)m->pairs[i]->key,
 *                ((block *)m->pairs[i]->value)->a,
 *                ((block *)m->pairs[i]->value)->name);
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 *  
 *      mdeleteAt(m, 243);
 *      for (ssize_t i = 0; i < m->size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
 *                (*(int *)m->pairs[i]->value));
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 *      free(((block*)m->pairs[0]->value)->name);
 *      mpop_back(m);
 *      for (ssize_t i = 0; i < m->size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
 *                (*(int *)m->pairs[i]->value));
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 *  
 *  
 *      destroy_map (m);  // DON NOT FORGET TO FREE THE MEMORY AFTER USAGE OF MAP
 *  
 *    #else // stack example
 *  
 *      initMap_s (m);  // stack map initialization
 *      int a = 1998, b = 2001, c = 1980, d = 1982;
 *      mpush_back (&m, &(pair){ "google", &a });
 *      mpush_back (&m, &(pair){ "yahoo", &b });
 *      mpush_back (&m, &(pair){ "linux", &c });
 *      if (mfind_by_string_key (&m, "jango") != NULL)
 *        printf ("FOUND------------>VALUE: {%d}\n",
 *                (*(int *)mfind_by_string_key (&m, "jango")));
 *      if (mfind_by_string_key (&m, "linux") != NULL)
 *        printf ("FOUND------------>VALUE: {%d}\n",
 *                (*(int *)mfind_by_string_key (&m, "linux")));
 *  
 *      for (ssize_t i = 0; i < m.size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m.pairs[i]->key,
 *                (*(int *)m.pairs[i]->value));
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *      mdeleteAt (&m, 0);
 *      for (ssize_t i = 0; i < m.size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m.pairs[i]->key,
 *                (*(int *)m.pairs[i]->value));
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *      mpop_back (&m);
 *      for (ssize_t i = 0; i < m.size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m.pairs[i]->key,
 *                (*(int *)m.pairs[i]->value));
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *      mclear (&m);
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *  
 *      mpop_back(&m);
 *      mdeleteAt(&m,32);
 *      mdeleteAt(&m,0);
 *      for (ssize_t i = 0; i < m.size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m.pairs[i]->key,
 *                (*(int *)m.pairs[i]->value));
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *      mpush_back(&m, &(pair){ "xerox", &d  });
 *      for (ssize_t i = 0; i < m.size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m.pairs[i]->key,
 *                (*(int *)m.pairs[i]->value));
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *      mdeleteAt(&m, 243);
 *      for (ssize_t i = 0; i < m.size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m.pairs[i]->key,
 *                (*(int *)m.pairs[i]->value));
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *      mpop_back(&m);
 *      for (ssize_t i = 0; i < m.size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m.pairs[i]->key,
 *                (*(int *)m.pairs[i]->value));
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *  
 *      destroy_map(&m);
 *      for (ssize_t i = 0; i < m.size; ++i)
 *        printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m.pairs[i]->key,
 *                (*(int *)m.pairs[i]->value));
 *      printf ("\nmap->size: %zu, map->capacity: %zu\n", m.size, m.capacity);
 *  
 *    #endif
 *      return 0;
 *    }
 *
 *
 */

#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define create_pair_with_strig_key(pair_name, str, val)                       \
  pair *(pair_name) = malloc (sizeof (pair));                                 \
  (pair_name)->key = (void *)strdup ((str));                                  \
  (pair_name)->value = (void *)(val)

#define initMap_s(x)             \
  map x = { .memberType = 's' }; \
  init_map(&x)

#define initMap_h(x)            \
  map* x = malloc(sizeof(map)); \
  x->memberType = 'h';          \
  init_map(x)

#define INTERNAL

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  void* key;
  void* value;
} pair;

typedef struct map map;

struct map {
  size_t size;
  size_t capacity;
  pair** pairs;
  char memberType;
};

static void*
mfind_by_string_key(map* m, void* key)
{
  for (ssize_t i = 0; i < m->size; ++i)
    if (memcmp((void*)key, m->pairs[i]->key, strlen((char*)key)) == 0)
      return m->pairs[i]->value;
  return NULL;
}

static void
mdeleteAt(map* m, size_t index)
{
  int i = 0;
  if (m) {
    if ((index < 0) || (index >= m->size))
      return;
    if (m->memberType == 's') {
      m->pairs[index]->key = NULL;
      m->pairs[index]->value = NULL;
      m->pairs[index] = NULL;
    } else {
      free(m->pairs[index]->key);
      m->pairs[index]->key = NULL;
      free(m->pairs[index]->value);
      m->pairs[index]->value = NULL;
      free(m->pairs[index]);
      m->pairs[index] = NULL;
    }
    for (i = index; i < (m->size - 1); ++i) {
      m->pairs[i] = m->pairs[i + 1];
      m->pairs[i + 1] = NULL;
    }
    m->size--;
    if ((m->size > 0) && ((m->size) == (m->capacity / 4))) {
      m->capacity /= 2;
      m->pairs = (pair **)realloc(m->pairs, sizeof(pair*) * m->capacity);
      if (m->pairs == NULL) {
        puts("memory allocation failed!");
        return;
      }
    }
  }
}

static void
mclear(map* m)
{
  if (m->memberType == 's') {
    free(m->pairs);
  } else {
    for (size_t i = 0; i < m->size; ++i) {
      free(m->pairs[i]->key);
      m->pairs[i]->key = NULL;
      free(m->pairs[i]->value);
      m->pairs[i]->value = NULL;
      free(m->pairs[i]);
      m->pairs[i] = NULL;
    }
    free(m->pairs);
  }
  m->pairs = NULL;
  m->size = 0;
  m->capacity = 0;
}

static void
destroy_map(map * m)
{
  mclear(m);
  if (m->memberType == 'h') {
    free(m);
    m = NULL;
  }
  else
    return;
}

static void
mreplace_element (map *m, size_t index, pair *d)
{
  if (index >= m->size || d == NULL)
    return;
  if (m->memberType == 's')
    m->pairs[index] = d;
  else
  {
    free(m->pairs[index]->key);
    m->pairs [index]->key = NULL;
    free(m->pairs[index]->value);
    m->pairs [index]->value = NULL;
    free(m->pairs[index]);
    m->pairs[index] = NULL;
    m->pairs[index] = d;
  }
}

static void
mpush_back(map* m, pair* p)
{
  if (m->size < m->capacity) {
    m->pairs[m->size] = p;
    m->size++;
  } else {
    if (m->capacity == 0)
      m->capacity = 2;
    else
      m->capacity *= 2;
    m->pairs = (pair **)realloc(m->pairs, sizeof(pair*) * m->capacity);
    if (m->pairs == NULL) {
      puts("memory allocation failed!");
      return;
    }
    m->pairs[m->size] = p;
    m->size++;
  }
}

static void
mpop_back(map* m)
{
  mdeleteAt(m, m->size - 1);
}

INTERNAL static void
init_map(map* m) /* INTERNAL FUNCTION DON'T CALL INSTEAD USE initMap_s(variable_name) or initMap_h(variable_name) MACROS */
{
  m->pairs = (pair **)malloc(2 * sizeof(pair*));
  if(!m->pairs) puts("memory allocation failed!");
  m->size = 0;
  m->capacity = 2;
}

#ifdef __cplusplus
}
#endif

#endif /* _MAP_H_ */
