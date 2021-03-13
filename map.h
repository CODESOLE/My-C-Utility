
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
 *  map creation can be with;
 *
 *  Map* map_name = init_map(<memberType>)
 *
 *  memberType is a enum which is there are 2 possible values;
 *
 *      * MAP_HEAP = 0
 *      * MAP_STACK = 1
 *
 *  These enums are specify the memberType. If your pairs are on heap
 *  create with MAP_HEAP, if on the stack create with MAP_STACK.
 *
 *  For key value pair actually pair struct consist of 2 void*
 *  which is generic data pointer, you can create any key,  value pair.
 *  However for string key and generic value pair there is pre-defined
 *  macro which is:
 *
 *   * create_pair_with_strig_key(pair_name, str, val) ==> creates pair with
 *   {string, value}
 *
 *  Functions:
 *   * map_push_back(map_variable_name, pair) ==> returns nothing, adds pair
 *     end of the map.
 *
 *   * map_pop_back(map_variable_name) ==> returns nothing, removes pair
 *     end of the map
 *
 *   * map_clear(map_variable_name) ==> returns nothing, removes all of the
 *     entries from the map.
 *
 *   * map_delete_at(map_variable_name, index) ==> returns nothing, removes
 *     element at specified index.
 *
 *   * mfind_by_string_key(map_variable_name, key_string) ==> returns void*
 *     if it finds match with the key, returns value of corresponding value,
 *     if not, returns NULL.
 *
 *   * destroy_map(map_name) ==> returns nothing, frees map
 *
 *   * map_replace_element(map_name, index, pair) ==> returns nothing, replaces
 *     pair at specified index.
 *
 *  For stack map you can simply create pairs with:
 *
 *  pair p1 = { "Personel" , &personel_object };
 *
 *  and add with:
 *
 *  map_push_back(map_name, p1);
 *
 *  For heap map you can create { string key, value } pairs with:
 *
 *  create_pair_with_string_key(pair_name, str, val);
 *
 *  and add with:
 *
 *  map_push_back(map_name, pair_name);
 *
 *  To make simple there is also a function called
 *  map_push_back_with_string_key (Map* m, const char* keyString, void* d)
 *  you can push data to map easily with { string, data } pair
 *  without calling create_pair_with_string_key(pair_name, str, val)
 *
 */

#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define create_pair_with_string_key(pair_name, str, val)                      \
  pair *(pair_name) = (pair *)malloc (sizeof (pair));                         \
  (pair_name)->key = (void *)strdup ((str));                                  \
  (pair_name)->value = (void *)(val)

typedef enum
{
  MAP_HEAP = 0,
  MAP_STACK
} MapType;

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
  void *key;
  void *value;
} pair;

typedef struct Map Map;

struct Map
{
  size_t size;
  size_t capacity;
  pair **pairs;
  char memberType[1];
};

static void *
mfind_by_string_key (Map *m, void *key)
{
  for (size_t i = 0; i < m->size; ++i)
    if (memcmp ((void *)key, m->pairs[i]->key, strlen ((char *)key)) == 0)
      return m->pairs[i]->value;
  return NULL;
}

static void
map_delete_at (Map *m, size_t index)
{
  int i = 0;
  if (m)
    {
      if ((index < 0) || (index >= m->size))
        return;
      if (m->memberType[0] == 's')
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
          m->pairs
              = (pair **)realloc (m->pairs, sizeof (pair *) * m->capacity);
          if (m->pairs == NULL)
            {
              puts ("memory allocation failed!");
              return;
            }
        }
    }
}

static void
map_clear (Map *m)
{
  if (m->memberType[0] == 's')
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
  m->capacity = 0;
}

static void
destroy_map (Map *m)
{
  map_clear (m);
  if (m->memberType[0] == 'h')
    {
      free (m);
      m = NULL;
    }
  else
    return;
}

static void
map_replace_element (Map *m, size_t index, pair *d)
{
  if (index >= m->size || d == NULL)
    return;
  if (m->memberType[0] == 's')
    m->pairs[index] = d;
  else
    {
      free (m->pairs[index]->key);
      m->pairs[index]->key = NULL;
      free (m->pairs[index]->value);
      m->pairs[index]->value = NULL;
      free (m->pairs[index]);
      m->pairs[index] = NULL;
      m->pairs[index] = d;
    }
}

static void
map_push_back (Map *m, pair *p)
{
  if (m->size < m->capacity)
    {
      m->pairs[m->size] = p;
      m->size++;
    }
  else
    {
      if (m->capacity == 0)
        m->capacity = 2;
      else
        m->capacity *= 2;
      m->pairs = (pair **)realloc (m->pairs, sizeof (pair *) * m->capacity);
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
map_push_back_with_string_key (Map *m, const char *keyString, void *d)
{
  create_pair_with_string_key (_p1, keyString, d);
  if (m->size < m->capacity)
    {
      m->pairs[m->size] = _p1;
      m->size++;
    }
  else
    {
      if (m->capacity == 0)
        m->capacity = 2;
      else
        m->capacity *= 2;
      m->pairs = (pair **)realloc (m->pairs, sizeof (pair *) * m->capacity);
      if (m->pairs == NULL)
        {
          puts ("memory allocation failed!");
          return;
        }
      m->pairs[m->size] = _p1;
      m->size++;
    }
}

static void
map_pop_back (Map *m)
{
  map_delete_at (m, m->size - 1);
}

static Map *
init_map (MapType mapType)
{
  Map *m = NULL;
  m = (Map *)malloc (sizeof (Map));
  if (!m)
    {
      puts ("memory allocation failed at map creation!");
      return NULL;
    }
  if (mapType == MAP_HEAP)
    {
      memcpy (m->memberType, (char[1]){ 'h' }, 1);
    }
  else if (mapType == MAP_STACK)
    {
      m->memberType[0] = 's';
    }
  else
    {
      puts ("MapType should be either MAP_HEAP or MAP_STACK! Map NOT "
            "initialized!");
      return NULL;
    }
  m->pairs = (pair **)calloc (2, sizeof (pair *));
  if (!m->pairs)
    puts ("memory allocation failed!");
  m->size = 0;
  m->capacity = 2;
  return m;
}

#ifdef __cplusplus
}
#endif

#endif /* _MAP_H_ */
