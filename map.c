#include "map.h"
typedef struct
 {
   int a;
   char *name;
 } block;

map*
create ()
{
 block *q1 = malloc (sizeof (block)); // dynamically allocated pair's value
 block *e2 = malloc (sizeof (block)); // dynamically allocated pair's value
 block *w3 = malloc (sizeof (block)); // dynamically allocated pair's value
 q1->a = 10;
 q1->name = strdup("aragorn");
 e2->a = 9;
 e2->name = strdup("morpheus");
 w3->a = 8;
 w3->name = strdup("hagrid");
 map* m = init_map (MAP_HEAP); // dynamically created map
 create_pair_with_strig_key (p1, "the lord of the rings", q1); // creation of pairs
 create_pair_with_strig_key (p2, "matrix", e2);                // creation of pairs
 create_pair_with_strig_key (p3, "harry potter", w3);          // creation of pairs
 mpush_back (m, p1);  // Add pairs to map
 mpush_back (m, p2);  // Add pairs to map
 mpush_back (m, p3);  // Add pairs to map
 return m;   //  return map from function
}

int
main (int argc, char *argv[])
{
#if 0 // heap example

 map *m = create ();
 if (mfind_by_string_key (m, "jango") != NULL)
   printf ("FOUND------------>VALUE: {%d, %s}\n",
           ((block *)mfind_by_string_key (m, "jango"))->a,
           ((block *)mfind_by_string_key (m, "jango"))->name);

 if (mfind_by_string_key (m, "The lord Of The Rings and fellowship of the ring") != NULL)
   printf ("FOUND------------>VALUE: {%d, %s}\n",
           ((block *)mfind_by_string_key (m, "jango"))->a,
           ((block *)mfind_by_string_key (m, "jango"))->name);

 if (mfind_by_string_key (m, "matrix") != NULL)
   printf ("FOUND------------>VALUE: {%d, %s}\n",
           ((block *)mfind_by_string_key (m, "matrix"))->a,
           ((block *)mfind_by_string_key (m, "matrix"))->name);

 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d, %s}\n", (char *)m->pairs[i]->key,
           ((block *)m->pairs[i]->value)->a,
           ((block *)m->pairs[i]->value)->name);
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 free(((block*)m->pairs[0]->value)->name);
 mdeleteAt (m, 0);
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d, %s}\n", (char *)m->pairs[i]->key,
           ((block *)m->pairs[i]->value)->a,
           ((block *)m->pairs[i]->value)->name);
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 free(((block*)m->pairs[m->size-1]->value)->name);
 mpop_back (m);
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d, %s}\n", (char *)m->pairs[i]->key,
           ((block *)m->pairs[i]->value)->a,
           ((block *)m->pairs[i]->value)->name);
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 free(((block*)m->pairs[0]->value)->name);
 mclear (m);
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);

 mdeleteAt(m, 321);
 mdeleteAt(m, 0);
 mpop_back(m);
 block* extra_data = malloc (sizeof(block));
 extra_data->a = 7;
 extra_data->name = strdup("age of empires");
 create_pair_with_strig_key (p4, "EA GAMES", extra_data); // creation of pairs
 mpush_back(m, p4);
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d, %s}\n", (char *)m->pairs[i]->key,
           ((block *)m->pairs[i]->value)->a,
           ((block *)m->pairs[i]->value)->name);
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);

 mdeleteAt(m, 243);
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
           (*(int *)m->pairs[i]->value));
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 free(((block*)m->pairs[0]->value)->name);
 mpop_back(m);
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
           (*(int *)m->pairs[i]->value));
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);


 destroy_map (m);  // DON NOT FORGET TO FREE THE MEMORY AFTER USAGE OF MAP

#else // stack example

 map* m = init_map (MAP_STACK); // stack map initialization
                                // (map itself on heap but data members are on stack)

 int a = 1998, b = 2001, c = 1980, d = 1982;
 mpush_back (m, &(pair){ "google", &a });
 mpush_back (m, &(pair){ "yahoo", &b });
 mpush_back (m, &(pair){ "linux", &c });
 if (mfind_by_string_key (m, "jango") != NULL)
   printf ("FOUND------------>VALUE: {%d}\n",
           (*(int *)mfind_by_string_key (m, "jango")));
 if (mfind_by_string_key (m, "linux") != NULL)
   printf ("FOUND------------>VALUE: {%d}\n",
           (*(int *)mfind_by_string_key (m, "linux")));

 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
           (*(int *)m->pairs[i]->value));
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 mdeleteAt (m, 0);
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
           (*(int *)m->pairs[i]->value));
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 mpop_back (m);
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
           (*(int *)m->pairs[i]->value));
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 mclear (m);
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);

 mpop_back(m);
 mdeleteAt(m,32);
 mdeleteAt(m,0);
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
           (*(int *)m->pairs[i]->value));
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 mpush_back(m, &(pair){ "xerox", &d  });
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
           (*(int *)m->pairs[i]->value));
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 mdeleteAt(m, 243);
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
           (*(int *)m->pairs[i]->value));
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);
 mpop_back(m);
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
           (*(int *)m->pairs[i]->value));
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);

 destroy_map(m);
 for (ssize_t i = 0; i < m->size; ++i)
   printf ("KEY: %s, VALUE: b1{%d}\n", (char *)m->pairs[i]->key,
           (*(int *)m->pairs[i]->value));
 printf ("\nmap->size: %zu, map->capacity: %zu\n", m->size, m->capacity);

#endif
 return 0;
}