#ifndef MATRIX_TYPES_H
#define MATRIX_TYPES_H

#include "matrix.h"

int matrix_is_square(const Matrix *m);
int matrix_is_zero(const Matrix *m);
int matrix_is_diagonal(const Matrix *m);
int matrix_is_identity(const Matrix *m);
int matrix_is_scalar(const Matrix *m);
int matrix_is_symmetric(const Matrix *m);
int matrix_is_upper_triangular(const Matrix *m);
int matrix_is_lower_triangular(const Matrix *m);

void matrix_print_types(const Matrix *m);

#endif