#pragma once

/*
 * header only simple vector implementation in C
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

#define initVec_s(x)                                                          \
  vector x = { .memberType = 's' };                                           \
  init_vec (&x)

#define initVec_h(x)                                                          \
  vector *x = malloc (sizeof (vector));                                       \
  x->memberType = 'h';                                                        \
  init_vec (x)

typedef struct vector vector;

struct vector
{
  size_t size;
  size_t capacity;
  void **data;
  char memberType;
  void (*vpush_back) (vector *, void *);
  void (*vpop_back) (vector *);
  void (*vclear) (vector *);
  void (*vdeleteAt) (vector *, size_t);
};

static void
vdeleteAt (vector *v, size_t index)
{
  int i = 0;
  if (v)
    {
      if ((index < 0) || (index >= v->size))
        return;
      if (v->memberType == 's')
        {
          v->data[index] = NULL;
        }
      else
        {
          free (v->data[index]);
          v->data[index] = NULL;
        }
      for (i = index; (i < v->size - 1); ++i)
        {
          v->data[i] = v->data[i + 1];
          v->data[i + 1] = NULL;
        }
      v->size--;
      if ((v->size > 0) && ((v->size) == (v->capacity / 4)))
        {
          v->capacity /= 2;
          v->data = realloc (v->data, sizeof (void *) * v->capacity);
          if (v->data == NULL)
            {
              puts ("memory allocation is failed!");
              return;
            }
        }
    }
}

static void
vclear (vector *v)
{
  if (v->memberType == 's')
    {
      free (v->data);
    }
  else
    {
      for (size_t i = 0; i < v->size; ++i)
        {
          free (v->data[i]);
        }
      free (v->data);
    }
  v->data = NULL;
  v->size = 0;
}

static void
vpush_back (vector *v, void *d)
{
  if (v->size < v->capacity)
    {
      v->data[v->size] = d;
      v->size++;
    }
  else
    {
      v->capacity *= 2;
      v->data = realloc (v->data, sizeof (void *) * v->capacity);
      if (v->data == NULL)
        {
          puts ("memory allocation is failed!");
          return;
        }
      v->data[v->size] = d;
      v->size++;
    }
}

static void
vpop_back (vector *v)
{
  v->vdeleteAt (v, v->size - 1);
}

static void
init_vec (vector *vec)
{
  vec->data = malloc (2 * sizeof (void *));
  vec->size = 0;
  vec->capacity = 2;
  vec->vpush_back = vpush_back;
  vec->vpop_back = vpop_back;
  vec->vdeleteAt = vdeleteAt;
  vec->vclear = vclear;
}
