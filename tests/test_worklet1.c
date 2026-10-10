
#include <stdio.h>
#include <stdlib.h>
#include "field.h"
#include "vector.h"
#include "matrix.h"

static int failed = 0;

static void check(const char *name, int result)
{
    printf("%s: %s\n", result ? "PASS" : "FAIL", name);
    if (!result)
        failed++;
}

int main(void)
{
    FieldElement a, b, result;

    check("Prime check", field_is_prime(7));
    check("Reject composite", !field_is_prime(8));
    check("Initialize field element", field_init(&a, 10, 7));
    check("Normalize field element", a.value == 3);
    check("Initialize second field element", field_init(&b, 6, 7));
    check("Field addition", field_add(a, b, &result) &&
          result.value == 2);
    check("Field subtraction", field_sub(a, b, &result) &&
          result.value == 4);
    check("Field multiplication", field_mul(a, b, &result) &&
          result.value == 4);
    check("Field inverse", field_inverse(a, &result) &&
          result.value == 5);

    Vector v = {0}, w = {0};
    check("Vector initialization", vector_init(&v, 2, 7));
    check("Second vector initialization", vector_init(&w, 2, 7));

    if (v.data != NULL && w.data != NULL)
    {
        v.data[0].value = 1;
        v.data[1].value = 2;
        w.data[0].value = 3;
        w.data[1].value = 4;

        check("Vector dot product",
              vector_dot(&v, &w, &result) && result.value == 4);
    }

    vector_free(&v);
    vector_free(&w);

    Matrix m = {0}, n = {0}, product = {0};
    check("Matrix initialization", matrix_init(&m, 2, 2, 7));
    check("Second matrix initialization", matrix_init(&n, 2, 2, 7));

    if (m.data != NULL && n.data != NULL)
    {
        m.data[0].value = 1;
        m.data[1].value = 2;
        m.data[2].value = 3;
        m.data[3].value = 4;

        n.data[0].value = 1;
        n.data[1].value = 0;
        n.data[2].value = 0;
        n.data[3].value = 1;

        check("Matrix identity multiplication",
              matrix_multiply(&m, &n, &product) &&
              matrix_equal(&m, &product));
    }

    matrix_free(&m);
    matrix_free(&n);
    matrix_free(&product);

    printf("\nTest result: %s\n", failed == 0 ? "PASS" : "FAIL");
    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
