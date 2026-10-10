
#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include "field.h"

typedef struct
{
    size_t length;
    long p;
    FieldElement *data;
} Vector;

bool vector_init(Vector *v, size_t length, long p);
void vector_free(Vector *v);
bool vector_get(const Vector *v, size_t index, FieldElement *result);
bool vector_add(const Vector *a, const Vector *b, Vector *result);
bool vector_scale(const Vector *v, FieldElement scalar, Vector *result);
bool vector_dot(const Vector *a, const Vector *b, FieldElement *result);
bool vector_equal(const Vector *a, const Vector *b);

#endif
