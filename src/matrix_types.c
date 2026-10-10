#include <stdio.h>
#include "matrix_types.h"
#include "matrix.h"

static long get_value(const Matrix *m, size_t row, size_t col) {
    return m->data[row * m->cols + col].value;
}

int matrix_is_square(const Matrix *m) {
    return m != NULL && m->rows == m->cols;
}

int matrix_is_zero(const Matrix *m) {
    if (m == NULL) return 0;

    for (size_t i = 0; i < m->rows * m->cols; i++) {
        if (m->data[i].value != 0) return 0;
    }

    return 1;
}

int matrix_is_diagonal(const Matrix *m) {
    if (!matrix_is_square(m)) return 0;

    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) {
            if (i != j && get_value(m, i, j) != 0) return 0;
        }
    }

    return 1;
}

int matrix_is_identity(const Matrix *m) {
    if (!matrix_is_square(m)) return 0;

    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) {
            long expected = (i == j) ? 1 : 0;
            if (get_value(m, i, j) != expected) return 0;
        }
    }

    return 1;
}

int matrix_is_scalar(const Matrix *m) {
    if (!matrix_is_diagonal(m)) return 0;

    if (m->rows == 0) return 1;

    long diagonal_value = get_value(m, 0, 0);

    for (size_t i = 1; i < m->rows; i++) {
        if (get_value(m, i, i) != diagonal_value) return 0;
    }

    return 1;
}

int matrix_is_symmetric(const Matrix *m) {
    if (!matrix_is_square(m)) return 0;

    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = i + 1; j < m->cols; j++) {
            if (get_value(m, i, j) != get_value(m, j, i)) {
                return 0;
            }
        }
    }

    return 1;
}

int matrix_is_upper_triangular(const Matrix *m) {
    if (!matrix_is_square(m)) return 0;

    for (size_t i = 1; i < m->rows; i++) {
        for (size_t j = 0; j < i; j++) {
            if (get_value(m, i, j) != 0) return 0;
        }
    }

    return 1;
}

int matrix_is_lower_triangular(const Matrix *m) {
    if (!matrix_is_square(m)) return 0;

    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = i + 1; j < m->cols; j++) {
            if (get_value(m, i, j) != 0) return 0;
        }
    }

    return 1;
}

void matrix_print_types(const Matrix *m) {
    if (m == NULL) {
        printf("Cannot classify an uninitialized matrix.\n");
        return;
    }

    int found = 0;

    printf("Matrix classifications:\n");

    if (matrix_is_square(m)) {
        printf("- Square matrix\n");
        found = 1;
    }
    if (matrix_is_zero(m)) {
        printf("- Zero matrix\n");
        found = 1;
    }
    if (matrix_is_diagonal(m)) {
        printf("- Diagonal matrix\n");
        found = 1;
    }
    if (matrix_is_identity(m)) {
        printf("- Identity matrix\n");
        found = 1;
    }
    if (matrix_is_scalar(m)) {
        printf("- Scalar matrix\n");
        found = 1;
    }
    if (matrix_is_symmetric(m)) {
        printf("- Symmetric matrix\n");
        found = 1;
    }
    if (matrix_is_upper_triangular(m)) {
        printf("- Upper triangular matrix\n");
        found = 1;
    }
    if (matrix_is_lower_triangular(m)) {
        printf("- Lower triangular matrix\n");
        found = 1;
    }

    if (!found) {
        printf("- No listed classifications apply\n");
    }
}