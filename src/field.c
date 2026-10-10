
#include <stdbool.h>
#include <stddef.h>
#include "field.h"

static long normalize(long value, long p)
{
    value %= p;
    if (value < 0)
        value += p;
    return value;
}

bool field_is_prime(long p)
{
    if (p < 2)
        return false;

    if (p == 2)
        return true;

    if (p % 2 == 0)
        return false;

    for (long i = 3; i <= p / i; i += 2)
    {
        if (p % i == 0)
            return false;
    }

    return true;
}

bool field_init(FieldElement *x, long value, long p)
{
    if (x == NULL || !field_is_prime(p))
        return false;

    x->value = normalize(value, p);
    x->p = p;
    return true;
}

bool field_add(FieldElement a, FieldElement b, FieldElement *result)
{
    if (result == NULL || a.p != b.p || !field_is_prime(a.p))
        return false;

    result->value = normalize(a.value + b.value, a.p);
    result->p = a.p;
    return true;
}

bool field_sub(FieldElement a, FieldElement b, FieldElement *result)
{
    if (result == NULL || a.p != b.p || !field_is_prime(a.p))
        return false;

    result->value = normalize(a.value - b.value, a.p);
    result->p = a.p;
    return true;
}

bool field_mul(FieldElement a, FieldElement b, FieldElement *result)
{
    if (result == NULL || a.p != b.p || !field_is_prime(a.p))
        return false;

    long x = normalize(a.value, a.p);
    long y = normalize(b.value, a.p);
    long product = 0;

    while (y > 0)
    {
        if (y % 2 == 1)
            product = normalize(product + x, a.p);

        x = normalize(x + x, a.p);
        y /= 2;
    }

    result->value = product;
    result->p = a.p;
    return true;
}

bool field_inverse(FieldElement a, FieldElement *result)
{
    if (result == NULL || !field_is_prime(a.p))
        return false;

    long value = normalize(a.value, a.p);

    if (value == 0)
        return false;

    for (long i = 1; i < a.p; i++)
    {
        if ((value * i) % a.p == 1)
        {
            result->value = i;
            result->p = a.p;
            return true;
        }
    }

    return false;
}

bool field_equal(FieldElement a, FieldElement b)
{
    if (a.p != b.p || !field_is_prime(a.p))
        return false;

    return normalize(a.value, a.p) == normalize(b.value, b.p);
}
