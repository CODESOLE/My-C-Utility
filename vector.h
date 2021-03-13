
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
 * -----------------------------------------------------------------
 *                             USAGE
 * -----------------------------------------------------------------
 *
 * There are two enums to create vector one for heap creation and other
 * one for stack creation, enums are :
 *
 *    * VEC_HEAP
 *    * VEC_STACK
 *
 * These enums are specify the what type of data member it stores,
 * vector itself always on heap therefore you should always call
 * destroy_vector() function, if your data that you will store
 * created on heap call Vector* vec = init_vec(VEC_HEAP,.......)
 * otherwise call Vector* vec = init_vec(VEC_STACK,.......)
 *
 *
 * There are 3 funtion pointer;
 * 
 *  _grow_pattern     => void (*grow_pattern) (size_t*)
 *
 *  _shrink_condition => int  (*shrink_condition) (size_t*,size_t*)
 *
 *  _shrink_pattern   => void (*shrink_pattern) (size_t*)
 *
 *
 * _grow_pattern, _shrink_pattern, _shrink_condition these are function
 * pointers that specifies how vector will be grow, shrink and which condition
 * it will shrink. If you don't want to specify particular function then pass
 * NULL for three of them. Their default patterns are:
 *
 * grown            => vector.capacity = vector.capacity * 2
 *
 * shrink_condition => if(vector.size <= vector.capacity / 4)
 *
 * shrink           => v.capacity = vector.capacity / 2;
 *
 * Functions:
 *  * vec_push_back(vector_name, data) ==> returns nothing, adds data
 *    end of vector.
 *
 *  * vec_pop_back(vector_name) ==> returns nothing, removes data from
 *    end of vector.
 *
 *  * vec_clear(vector_name) ==> returns nothing, removes all data from
 *    vector.
 *
 *  * vec_delete_at(vector_name, index) ==> returns nothing, removes data
 *    at specified index.
 *
 *  * destroy_vector(vector_name) ==> returns nothing, frees vector container
 *
 *  * vec_replace_element(vector_name, index, data) ==> returns nothing, replaces
 *    data at specified index.
 *
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct Vector Vector;

struct Vector
{
  size_t size;
  size_t capacity;
  void **data;
  char memberType[1];
  void (*grow_pattern) (size_t *);
  void (*shrink_pattern) (size_t *);
  int (*shrink_condition) (size_t *, size_t *);
};

typedef enum
{
  VEC_HEAP = 0,
  VEC_STACK
}VecType;

static void
vec_delete_at (Vector *v, size_t index)
{
  int i = 0;
  if (v)
    {
      if ((index < 0) || (index >= v->size))
        return;
      if (v->memberType[0] == 's')
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
      if ((v->size > 0)
          && ((v->shrink_condition != NULL)
                  ? v->shrink_condition (&v->size, &v->capacity)
                  : (v->size <= (v->capacity / 4))))
        {
          if (v->shrink_pattern == NULL)
            v->capacity /= 2;
          else
            v->shrink_pattern (&v->capacity);

          v->data
              = (void **)realloc (v->data, sizeof (void *) * v->capacity);
          if (v->data == NULL)
            {
              puts ("memory allocation is failed!");
              return;
            }
        }
    }
}

static void
vec_clear (Vector *v)
{
  if (v->memberType[0] == 's')
    {
      free (v->data);
    }
  else
    {
      for (size_t i = 0; i < v->size; ++i)
        {
          free (v->data[i]);
          v->data[i] = NULL;
        }
      free (v->data);
    }
  v->data = NULL;
  v->size = 0;
  v->capacity = 0;
}

static void
destroy_vector (Vector *v)
{
  vec_clear (v);
  if (v->memberType[0] == 'h')
    {
      free (v);
      v = NULL;
    }
  else
    return;
}

static void
vec_push_back (Vector *v, void *d)
{
  if (v->size < v->capacity)
    {
      v->data[v->size] = d;
      v->size++;
    }
  else
    {
      if (v->grow_pattern == NULL)
        {
          if (v->capacity == 0)
            v->capacity = (v->capacity + 1) * 2;
          else
            v->capacity *= 2;
        }
      else
        v->grow_pattern (&v->capacity);

      v->data = (void **)realloc (v->data, sizeof (void *) * v->capacity);
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
vec_replace_element (Vector *v, size_t index, void *d)
{
  if (index >= v->size || d == NULL)
    return;
  if (v->memberType[0] == 's')
    v->data[index] = d;
  else
    {
      free (v->data[index]);
      v->data[index] = NULL;
      v->data[index] = d;
    }
}

static void
vec_pop_back (Vector *v)
{
  vec_delete_at (v, v->size - 1);
}

static Vector*
init_vec (VecType vecType, void (*grw_patrn) (size_t *),
          void (*shrnk_patrn) (size_t *),
          int (*_shrink_condition) (
              size_t *, size_t *))

{
  Vector* vec = NULL;
  vec = (Vector *)malloc (sizeof (Vector));

  if (!vec)
    {
      puts ("memory allocation failed at Vector creation!");
      return NULL;
    }
  if (vecType == VEC_HEAP)
    {
      memcpy (vec->memberType, (char[1]){ 'h' }, 1);
    }
  else if (vecType == VEC_STACK)
    {
      vec->memberType[0] = 's';
    }
  else
    {
      puts ("VecType should be either VEC_HEAP or VEC_STACK! Vector NOT "
            "initialized!");
      return NULL;
    }

  vec->data = (void **)malloc (2 * sizeof (void *));
  vec->size = 0;
  vec->capacity = 2;
  if (grw_patrn == NULL)
    vec->grow_pattern = NULL;
  else
    vec->grow_pattern = grw_patrn;

  if (shrnk_patrn == NULL)
    vec->shrink_pattern = NULL;
  else
    vec->shrink_pattern = shrnk_patrn;

  if (_shrink_condition == NULL)
    vec->shrink_condition = NULL;
  else
    vec->shrink_condition = _shrink_condition;
  return vec;
}

#ifdef __cplusplus
}
#endif

#endif /* _VECTOR_H_ */
