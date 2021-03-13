#include "vector.h"

void
shr (size_t *cap) // our custom shrink pattern
{
  puts ("shr is calling");
  *(cap) = *(cap)-2;
}

void
grw (size_t *cap) // our custom grow pattern
{
  puts ("grw is calling");
  *(cap) = *(cap) + 1;
}

int
shr_con (size_t *sz, size_t *cap) // our custom shrink_condition
{
  puts ("shr_con is calling");
  if (*(sz) == *(cap)-2)
    {
      return 1;
    }
  return 0;
}

typedef struct
{
  int a;
} st;

Vector *
create ()
{
  st *g1 = malloc (sizeof (st));
  g1->a = 123;
  st *g2 = malloc (sizeof (st));
  g2->a = 456;
  st *g3 = malloc (sizeof (st));
  g3->a = 789;
  Vector* v = init_vec (VEC_HEAP, grw, shr, shr_con);
  vec_push_back (v, g1);
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_push_back (v, g2);
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_push_back (v, g3);
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  return v;
}

int
main (int argc, char *argv[])
{
#if 0 // heap vector

       Vector *v = create ();

       for (size_t i = 0; i < v->size; ++i)
         printf ("vector data: %d\n", *(int *)v->data[i]);
       vec_delete_at (v, 0);
       printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
       for (size_t i = 0; i < v->size; ++i)
         printf ("vector data: %d\n", *(int *)v->data[i]);
       vec_pop_back (v);
       printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
       for (size_t i = 0; i < v->size; ++i)
         printf ("vector data: %d\n", *(int *)v->data[i]);
       vec_clear (v);
       printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
       for (size_t i = 0; i < v->size; ++i)
         printf ("vector data: %d\n", *(int *)v->data[i]);
       vec_clear (v);
       printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
       vec_delete_at (v, 5);
       vec_delete_at (v, 0);
       printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
       int* a = malloc(4);
       *a = 1998;
       vec_push_back(v, a);
       printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
       for (size_t i = 0; i < v->size; ++i)
         printf ("vector data: %d\n", *(int *)v->data[i]);
       vec_delete_at(v, 156);
       printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
       vec_pop_back(v);
       printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
       vec_clear(v);
       printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);

       destroy_vector(v);

#else // stack vector

  Vector* v = init_vec (VEC_STACK, grw, shr, shr_con);
  vec_push_back (v, &(int){ 10 });
  vec_push_back (v, &(int){ 20 });
  vec_push_back (v, &(int){ 30 });
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  for (size_t i = 0; i < v->size; ++i)
    printf ("vector data: %d\n", *(int *)v->data[i]);
  vec_delete_at (v, 0);
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  for (size_t i = 0; i < v->size; ++i)
    printf ("vector data: %d\n", *(int *)v->data[i]);
  vec_pop_back (v);
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  for (size_t i = 0; i < v->size; ++i)
    printf ("vector data: %d\n", *(int *)v->data[i]);
  vec_clear (v);
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  for (size_t i = 0; i < v->size; ++i)
    printf ("vector data: %d\n", *(int *)v->data[i]);
  vec_clear (v);
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_delete_at (v, 5);
  vec_delete_at (v, 0);
  vec_push_back (v, &(int){ 56 });
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_push_back (v, &(int){ 50 });
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_push_back (v, &(int){ 50 });
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_pop_back (v);
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_pop_back (v);
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_pop_back (v);
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_clear (v);
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_push_back (v, &(int){ 56 });
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_push_back (v, &(int){ 50 });
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);
  vec_push_back (v, &(int){ 50 });
  printf ("SIZE: %zu, CAPACITY: %zu\n", v->size, v->capacity);

  destroy_vector (v);

#endif

  return 0;
}
