#pragma once

#include <stdio.h>
#include <stdlib.h>

#define initsVec_s(x)                    \
    vector x = { .memberType = 's' }; \
    init_vec(&x)

#define initsVec_h(x)                    \
    vector x = { .memberType = 'h' }; \
    init_vec(&x)

#define inithVec_s(x)                 \
    vector* x = malloc(sizeof(vector)); \
    x->memberType = 's';                \
    init_vec(x)

#define inithVec_h(x)                 \
    vector* x = malloc(sizeof(vector)); \
    x->memberType = 'h';                \
    init_vec(x)

typedef struct vector vector;

struct vector {
    size_t size;
    size_t capacity;
    void** data;
    char memberType;
    void (*push_back)(vector*, void*);
    void (*pop_back)(vector*);
    void (*clear)(vector*);
    void (*deleteAt)(vector*, size_t);
};

static void deleteAt(vector* v, size_t index)
{
    int i = 0;
    if (v) {
	if ((index < 0) || (index >= v->size))
	    return;
	if (v->memberType == 's') {
	    v->data[index] = NULL;
	} else {
	    free(v->data[index]);
	    v->data[index] = NULL;
	}
	for (i = index; (i < v->size - 1); ++i) {
	    v->data[i] = v->data[i + 1];
	    v->data[i + 1] = NULL;
	}
	v->size--;
	if ((v->size > 0) && ((v->size) == (v->capacity / 4))) {
	    v->data = realloc(v->data, sizeof(void*) * v->capacity / 2);
	    if (v->data == NULL) {
		puts("memory allocation is failed!");
		return;
	    }
	}
    }
}

static void clear(vector* v)
{
    if (v->memberType == 's') {
	free(v->data);
    } else {
	for (size_t i = 0; i < v->size; ++i) {
	    free(v->data[i]);
	}
	free(v->data);
    }
    v->data = NULL;
    v->data = malloc(2 * sizeof(void*));
    if (v->data == NULL) {
	puts("memory allocation is failed!");
	return;
    }
    v->size = 0;
    v->capacity = 2;
}

static void push_back(vector* v, void* d)
{
    if (v->size < v->capacity) {
	v->data[v->size] = d;
	v->size++;
    } else {
	v->capacity *= 2;
	v->data = realloc(v->data, sizeof(void*) * v->capacity);
	if (v->data == NULL) {
	    puts("memory allocation is failed!");
	    return;
	}
	v->data[v->size] = d;
	v->size++;
    }
}

static void pop_back(vector* v)
{
    v->deleteAt(v, v->size - 1);
}

static void init_vec(vector* vec)
{
    vec->data = malloc(2 * sizeof(void*));
    vec->size = 0;
    vec->capacity = 2;
    vec->push_back = push_back;
    vec->pop_back = pop_back;
    vec->deleteAt = deleteAt;
    vec->clear = clear;
}