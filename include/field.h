#ifndef FIELD_H
#define FIELD_H

#include <stdbool.h>

typedef struct {
    long value;
    long p;
} FieldElement;

bool field_is_prime(long p);
bool field_init(FieldElement *element, long value, long p);
bool field_add(FieldElement a, FieldElement b, FieldElement *result);
bool field_sub(FieldElement a, FieldElement b, FieldElement *result);
bool field_mul(FieldElement a, FieldElement b, FieldElement *result);
bool field_inverse(FieldElement a, FieldElement *result);
bool field_equal(FieldElement a, FieldElement b);

#endif