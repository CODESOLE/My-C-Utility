
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
 * There are two macros to create vector one for heap creation and other
 * one for stack creation, macros are :
 *
 * initVec_s(vector_name, _grow_pattern, _shrink_pattern, _shrink_condition) ==> for stack
 *
 * initVec_h(vector_name, _grow_pattern, _shrink_pattern, _shrink_condition) ==> for heap
 * 
 *  _grow_pattern     => void (*grow_pattern) (size_t*)
 *                                                
 *  _shrink_condition => int  (*shrink_condition) (size_t*,size_t*)
 *                                                
 *  _shrink_pattern   => void (*shrink_pattern) (size_t*)
 *
 * 
 * _grow_pattern, _shrink_pattern, _shrink_condition these are function pointers
 * that specifies how vector will be grow, shrink and which condition it will shrink.
 * If you don't want to specify particular function then pass NULL for three of them.
 * Their default patterns are:
 *
 * grown            => vector.capacity = vector.capacity * 2
 *
 * shrink_condition => if(vector.size <= vector.capacity / 4)
 *
 * shrink           => v.capacity = vector.capacity / 2;
 *
 * Functions:
 *  * vpush_back(vector_name, data) ==> returns nothing, adds data
 *    end of vector.
 *
 *  * vpop_back(vector_name) ==> returns nothing, removes data from
 *    end of vector.
 *
 *  * vclear(vector_name) ==> returns nothing, removes all data from
 *    vector.
 *
 *  * vdeleteAt(vector_name, index) ==> returns nothing, removes data
 *    at specified index.
 *
 *  * destroy_vector(vector_name) ==> returns nothing, frees vector container
 *
 *  * vreplace_element(vector_name, index, data) ==> returns nothing, replaces
 *    data at specified index.
 *
 * ---------------------------------------------------------------------------
 *                          SAMPLE CODE
 * ---------------------------------------------------------------------------
 *    void
 *    shr (size_t *cap) // our custom shrink pattern
 *    {
 *      puts("shr is calling");
 *      *(cap) = *(cap) - 2;
 *    }
 *
 *    void
 *    grw (size_t *cap) // our custom grow pattern
 *    {
 *      puts("grw is calling");
 *      *(cap) = *(cap) + 1;
 *    }
 *
 *    int
 *    shr_con (size_t *sz, size_t *cap) // our custom shrink_condition
 *    {
 *      puts("shr_con is calling");
 *      if (*(sz) == *(cap) - 2)
 *        {
 *          return 1;
 *        }
 *      return 0;
 *    }
 *
 *    typedef struct
 *    {
 *      int a;
 *    } st;
 *
 *    vector *
 *    create ()
 *    {
 *      st *g1 = malloc (sizeof (st));
 *      g1->a = 123;
 *      st *g2 = malloc (sizeof (st));
 *      g2->a = 456;
 *      st *g3 = malloc (sizeof (st));
 *      g3->a = 789;
 *      initVec_h (v, grw, shr, shr_con);
 *      vpush_back (v, g1);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *      vpush_back (v, g2);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *      vpush_back (v, g3);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *      return v;
 *    }
 *
 *    int
 *    main (int argc, char *argv[])
 *    {
 *    #if 0 // heap vector
 *
 *      vector *v = create ();
 *
 *      for (ssize_t i = 0; i < v->size; ++i)
 *        printf ("vector data: %d\n", *(int *)v->data[i]);
 *      vdeleteAt (v, 0);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *      for (ssize_t i = 0; i < v->size; ++i)
 *        printf ("vector data: %d\n", *(int *)v->data[i]);
 *      vpop_back (v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *      for (ssize_t i = 0; i < v->size; ++i)
 *        printf ("vector data: %d\n", *(int *)v->data[i]);
 *      vclear (v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *      for (ssize_t i = 0; i < v->size; ++i)
 *        printf ("vector data: %d\n", *(int *)v->data[i]);
 *      vclear (v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *      vdeleteAt (v, 5);
 *      vdeleteAt (v, 0);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *      int* a = malloc(4);
 *      *a = 1998;
 *      vpush_back(v, a);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *      for (ssize_t i = 0; i < v->size; ++i)
 *        printf ("vector data: %d\n", *(int *)v->data[i]);
 *      vdeleteAt(v, 156);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *      vpop_back(v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *      vclear(v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
 *
 *      destroy_vector(v);
 *
 *    #else  // stack vector
 *
 *      initVec_s (v, grw, shr,shr_con);
 *      vpush_back (&v, &(int){ 10 });
 *      vpush_back (&v, &(int){ 20 });
 *      vpush_back (&v, &(int){ 30 });
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      for (ssize_t i = 0; i < v.size; ++i)
 *        printf ("vector data: %d\n", *(int *)v.data[i]);
 *      vdeleteAt (&v, 0);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      for (ssize_t i = 0; i < v.size; ++i)
 *        printf ("vector data: %d\n", *(int *)v.data[i]);
 *      vpop_back (&v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      for (ssize_t i = 0; i < v.size; ++i)
 *        printf ("vector data: %d\n", *(int *)v.data[i]);
 *      vclear (&v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      for (ssize_t i = 0; i < v.size; ++i)
 *        printf ("vector data: %d\n", *(int *)v.data[i]);
 *      vclear (&v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      vdeleteAt (&v, 5);
 *      vdeleteAt (&v, 0);
 *      vpush_back(&v, &(int){56});
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      vpush_back(&v, &(int){50});
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      vpush_back(&v, &(int){50});
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      vpop_back(&v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      vpop_back(&v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      vpop_back(&v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      vclear(&v);
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      vpush_back(&v, &(int){56});
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      vpush_back(&v, &(int){50});
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *      vpush_back(&v, &(int){50});
 *      printf ("SIZE: %zu, CAPACITY: %zu\n", v.size, v.capacity);
 *
 *      destroy_vector(&v);
 *
 *    #endif
 *
 *      return 0;
 *    }
 *
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdio.h>
#include <stdlib.h>

#define initVec_s(vec_name, _grow_pattern, _shrink_pattern,                   \
                  _shrink_condition)                                          \
  vector vec_name = { .memberType = 's' };                                    \
  init_vec (&(vec_name), _grow_pattern, _shrink_pattern, _shrink_condition)

#define initVec_h(vec_name, _grow_pattern, _shrink_pattern,                   \
                  _shrink_condition)                                          \
  vector *vec_name = malloc (sizeof (vector));                                \
  (vec_name)->memberType = 'h';                                               \
  init_vec (vec_name, _grow_pattern, _shrink_pattern, _shrink_condition)

#define INTERNAL

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct vector vector;

  struct vector
  {
    size_t size;
    size_t capacity;
    void **data;
    char memberType;
    void (*grow_pattern) (size_t *);
    void (*shrink_pattern) (size_t *);
    int (*shrink_condition) (size_t *, size_t *);
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
            v->data[i] = NULL;
          }
        free (v->data);
      }
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
  }

  static void
  destroy_vector (vector *v)
  {
    vclear (v);
    if (v->memberType == 'h')
      {
        free (v);
        v = NULL;
      }
    else
      return;
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
  vreplace_element (vector *v, size_t index, void *d)
  {
    if (index >= v->size || d == NULL)
      return;
    if (v->memberType == 's')
      v->data[index] = d;
    else
    {
      free(v->data[index]);
      v->data[index] = NULL;
      v->data[index] = d;
    }
  }

  static void
  vpop_back (vector *v)
  {
    vdeleteAt (v, v->size - 1);
  }

  static void INTERNAL
  init_vec (vector *vec, void (*grw_patrn) (size_t *),
            void (*shrnk_patrn) (size_t *),
            int (*_shrink_condition) (size_t *, size_t *)) /* INTERNAL FUNCTION DON'T CALL INSTEAD
                                                              USE initVec_s(variable_name) or
                                                              initVec_h(variable_name) MACROS */

  {
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
  }

#ifdef __cplusplus
}
#endif

#endif /* _VECTOR_H_ */
