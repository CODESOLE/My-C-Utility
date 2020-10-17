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
  void *(*mfind_by_char_key) (map *, void *);
};

static void *
mfind_by_char_key (map *m, void *key)
{
  for (ssize_t i = 0; i < m->size; ++i)
    if (memcmp (key, m->pairs[i]->key, strlen ((char *)key)) == 0)
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
init_map (map *m)
{
  m->pairs = malloc (2 * sizeof (pair *));
  m->size = 0;
  m->capacity = 2;
  m->mpush_back = mpush_back;
  m->mpop_back = mpop_back;
  m->mdeleteAt = mdeleteAt;
  m->mclear = mclear;
  m->mfind_by_char_key = mfind_by_char_key;
}
