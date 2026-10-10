#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdbool.h>
#include "field.h"

typedef struct {
    size_t rows;
    size_t cols;
    long p;
    FieldElement *data;
} Matrix;

bool matrix_init(Matrix *m, size_t rows, size_t cols, long p);
void matrix_free(Matrix *m);
bool matrix_get(const Matrix *m, size_t row, size_t col, FieldElement *result);
bool matrix_add(const Matrix *a, const Matrix *b, Matrix *result);
bool matrix_scale(const Matrix *m, FieldElement scalar, Matrix *result);
bool matrix_transpose(const Matrix *m, Matrix *result);
bool matrix_multiply(const Matrix *a, const Matrix *b, Matrix *result);
bool matrix_equal(const Matrix *a, const Matrix *b);

#endif