
#include <stdlib.h>
#include "vector.h"
#include "field.h"


bool vector_init(Vector *v, size_t length, long p)
{
    if (v == NULL || length == 0 || !field_is_prime(p))
        return false;

    v->length = length;
    v->p = p;
    v->data = calloc(length, sizeof(FieldElement));

    if (v->data == NULL)
    {
        v->length = 0;
        return false;
    }

    for (size_t i = 0; i < length; i++)
        v->data[i].p = p;

    return true;
}

void vector_free(Vector *v)
{
    if (v != NULL)
    {
        free(v->data);
        v->data = NULL;
        v->length = 0;
        v->p = 0;
    }
}

bool vector_get(const Vector *v, size_t index, FieldElement *result)
{
    if (v == NULL || v->data == NULL || result == NULL ||
        index >= v->length)
        return false;

    *result = v->data[index];
    return true;
}

bool vector_add(const Vector *a, const Vector *b, Vector *result)
{
    if (a == NULL || b == NULL || result == NULL ||
        a->data == NULL || b->data == NULL ||
        a->length != b->length || a->p != b->p)
        return false;

    if (!vector_init(result, a->length, a->p))
        return false;

    for (size_t i = 0; i < a->length; i++)
    {
        if (!field_add(a->data[i], b->data[i], &result->data[i]))
        {
            vector_free(result);
            return false;
        }
    }

    return true;
}

bool vector_scale(const Vector *v, FieldElement scalar, Vector *result)
{
    if (v == NULL || result == NULL || v->data == NULL ||
        v->p != scalar.p)
        return false;

    if (!vector_init(result, v->length, v->p))
        return false;

    for (size_t i = 0; i < v->length; i++)
    {
        if (!field_mul(v->data[i], scalar, &result->data[i]))
        {
            vector_free(result);
            return false;
        }
    }

    return true;
}

bool vector_dot(const Vector *a, const Vector *b, FieldElement *result)
{
    if (a == NULL || b == NULL || result == NULL ||
        a->data == NULL || b->data == NULL ||
        a->length != b->length || a->p != b->p)
        return false;

    FieldElement sum = {0, a->p};

    for (size_t i = 0; i < a->length; i++)
    {
        FieldElement product;
        FieldElement next;

        if (!field_mul(a->data[i], b->data[i], &product) ||
            !field_add(sum, product, &next))
            return false;

        sum = next;
    }

    *result = sum;
    return true;
}

bool vector_equal(const Vector *a, const Vector *b)
{
    if (a == NULL || b == NULL || a->data == NULL ||
        b->data == NULL || a->length != b->length || a->p != b->p)
        return false;

    for (size_t i = 0; i < a->length; i++)
    {
        if (!field_equal(a->data[i], b->data[i]))
            return false;
    }

    return true;
}
