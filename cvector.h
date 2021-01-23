#ifndef _CVECTOR_H_
#define _CVECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define vcreate(name, type) struct{ type **data; size_t size; size_t capacity; }(*name) = malloc(sizeof(type**) + 2 * sizeof(size_t));(name)->data = malloc(2*sizeof(type**));(name)->size = 0;(name)->capacity = 2

#define vpush_back(vec , elem) \
  do{\
    if ((vec)->size < (vec)->capacity)\
      {\
        (vec)->data[(vec)->size] = (elem);\
        (vec)->size++;\
      }\
    else\
      {\
        (vec)->capacity *= 2;\
        (vec)->data = realloc ((vec)->data, sizeof(void *) * (vec)->capacity);\
        if ((vec)->data == NULL)\
          {\
            puts ("memory allocation is failed!");\
            break;\
          }\
        (vec)->data[(vec)->size] = (elem);\
        (vec)->size++;\
      }\
  }while(0) 

#define vdeleteAt(vec, index) \
  do{\
   if ((vec))\
      {\
        if ((index < 0) || (index >= (vec)->size))\
          break;\
        (vec)->data[index] = NULL;\
        for (size_t i = index; (i < (vec)->size - 1); ++i)\
          {\
            (vec)->data[i] = (vec)->data[i + 1];\
            (vec)->data[i + 1] = NULL;\
          }\
        (vec)->size--;\
        if (((vec)->size > 0) && ((vec)->size <= ((vec)->capacity / 4)))\
          {\
            (vec)->capacity /= 2;\
            (vec)->data = realloc ((vec)->data, sizeof (void *) * (vec)->capacity);\
            if ((vec)->data == NULL)\
              {\
                puts ("memory allocation is failed!");\
                break;\
              }\
          }\
     }\
  }while(0) 

#define vpop_back(vec)\
do\
{\
  vdeleteAt(vec, (vec)->size - 1);\
} while(0)

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !_CVECTOR_H_
