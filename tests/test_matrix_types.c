#include <assert.h>
#include <stdio.h>
#include "field.h"
#include "matrix.h"
#include "matrix_types.h"

static void set_matrix(Matrix *m, const long *values) {
    for (size_t i = 0; i < m->rows * m->cols; i++) {
        assert(field_init(&m->data[i], values[i], m->p));
    }
}

static void test_identity_matrix(void) {
    Matrix m;
    const long values[] = {1, 0, 0, 1};

    assert(matrix_init(&m, 2, 2, 7));
    set_matrix(&m, values);

    assert(matrix_is_square(&m));
    assert(matrix_is_diagonal(&m));
    assert(matrix_is_identity(&m));
    assert(matrix_is_scalar(&m));
    assert(matrix_is_symmetric(&m));
    assert(matrix_is_upper_triangular(&m));
    assert(matrix_is_lower_triangular(&m));
    assert(!matrix_is_zero(&m));

    matrix_free(&m);
}

static void test_zero_matrix(void) {
    Matrix m;

    assert(matrix_init(&m, 2, 2, 7));

    assert(matrix_is_square(&m));
    assert(matrix_is_zero(&m));
    assert(matrix_is_diagonal(&m));
    assert(!matrix_is_identity(&m));
    assert(matrix_is_scalar(&m));
    assert(matrix_is_symmetric(&m));
    assert(matrix_is_upper_triangular(&m));
    assert(matrix_is_lower_triangular(&m));

    matrix_free(&m);
}

static void test_diagonal_non_scalar_matrix(void) {
    Matrix m;
    const long values[] = {2, 0, 0, 3};

    assert(matrix_init(&m, 2, 2, 7));
    set_matrix(&m, values);

    assert(matrix_is_square(&m));
    assert(!matrix_is_zero(&m));
    assert(matrix_is_diagonal(&m));
    assert(!matrix_is_identity(&m));
    assert(!matrix_is_scalar(&m));
    assert(matrix_is_symmetric(&m));
    assert(matrix_is_upper_triangular(&m));
    assert(matrix_is_lower_triangular(&m));

    matrix_free(&m);
}

static void test_symmetric_non_diagonal_matrix(void) {
    Matrix m;
    const long values[] = {1, 2, 2, 3};

    assert(matrix_init(&m, 2, 2, 7));
    set_matrix(&m, values);

    assert(matrix_is_square(&m));
    assert(!matrix_is_zero(&m));
    assert(!matrix_is_diagonal(&m));
    assert(!matrix_is_identity(&m));
    assert(!matrix_is_scalar(&m));
    assert(matrix_is_symmetric(&m));
    assert(!matrix_is_upper_triangular(&m));
    assert(!matrix_is_lower_triangular(&m));

    matrix_free(&m);
}

static void test_upper_triangular_matrix(void) {
    Matrix m;
    const long values[] = {1, 2, 0, 3};

    assert(matrix_init(&m, 2, 2, 7));
    set_matrix(&m, values);

    assert(matrix_is_square(&m));
    assert(!matrix_is_zero(&m));
    assert(!matrix_is_diagonal(&m));
    assert(!matrix_is_identity(&m));
    assert(!matrix_is_scalar(&m));
    assert(!matrix_is_symmetric(&m));
    assert(matrix_is_upper_triangular(&m));
    assert(!matrix_is_lower_triangular(&m));

    matrix_free(&m);
}

static void test_lower_triangular_matrix(void) {
    Matrix m;
    const long values[] = {1, 0, 2, 3};

    assert(matrix_init(&m, 2, 2, 7));
    set_matrix(&m, values);

    assert(matrix_is_square(&m));
    assert(!matrix_is_zero(&m));
    assert(!matrix_is_diagonal(&m));
    assert(!matrix_is_identity(&m));
    assert(!matrix_is_scalar(&m));
    assert(!matrix_is_symmetric(&m));
    assert(!matrix_is_upper_triangular(&m));
    assert(matrix_is_lower_triangular(&m));

    matrix_free(&m);
}

static void test_general_square_matrix(void) {
    Matrix m;
    const long values[] = {1, 2, 3, 4};

    assert(matrix_init(&m, 2, 2, 7));
    set_matrix(&m, values);

    assert(matrix_is_square(&m));
    assert(!matrix_is_zero(&m));
    assert(!matrix_is_diagonal(&m));
    assert(!matrix_is_identity(&m));
    assert(!matrix_is_scalar(&m));
    assert(!matrix_is_symmetric(&m));
    assert(!matrix_is_upper_triangular(&m));
    assert(!matrix_is_lower_triangular(&m));

    matrix_free(&m);
}

static void test_rectangular_matrix(void) {
    Matrix m;
    const long values[] = {1, 2, 3, 4, 5, 6};

    assert(matrix_init(&m, 2, 3, 7));
    set_matrix(&m, values);

    assert(!matrix_is_square(&m));
    assert(!matrix_is_zero(&m));
    assert(!matrix_is_diagonal(&m));
    assert(!matrix_is_identity(&m));
    assert(!matrix_is_scalar(&m));
    assert(!matrix_is_symmetric(&m));
    assert(!matrix_is_upper_triangular(&m));
    assert(!matrix_is_lower_triangular(&m));

    matrix_free(&m);
}

static void test_one_by_one_matrix(void) {
    Matrix m;
    const long values[] = {1};

    assert(matrix_init(&m, 1, 1, 7));
    set_matrix(&m, values);

    assert(matrix_is_square(&m));
    assert(!matrix_is_zero(&m));
    assert(matrix_is_diagonal(&m));
    assert(matrix_is_identity(&m));
    assert(matrix_is_scalar(&m));
    assert(matrix_is_symmetric(&m));
    assert(matrix_is_upper_triangular(&m));
    assert(matrix_is_lower_triangular(&m));

    matrix_free(&m);
}

static void test_modular_values(void) {
    Matrix m;
    const long values[] = {8, 9, -1, 10};

    assert(matrix_init(&m, 2, 2, 7));
    set_matrix(&m, values);

    assert(m.data[0].value == 1);
    assert(m.data[1].value == 2);
    assert(m.data[2].value == 6);
    assert(m.data[3].value == 3);

    assert(matrix_is_square(&m));
    assert(!matrix_is_zero(&m));
    assert(!matrix_is_diagonal(&m));
    assert(!matrix_is_identity(&m));
    assert(!matrix_is_scalar(&m));
    assert(!matrix_is_symmetric(&m));
    assert(!matrix_is_upper_triangular(&m));
    assert(!matrix_is_lower_triangular(&m));

    matrix_free(&m);
}

int main(void) {
    test_identity_matrix();
    test_zero_matrix();
    test_diagonal_non_scalar_matrix();
    test_symmetric_non_diagonal_matrix();
    test_upper_triangular_matrix();
    test_lower_triangular_matrix();
    test_general_square_matrix();
    test_rectangular_matrix();
    test_one_by_one_matrix();
    test_modular_values();

    printf("All matrix classification tests passed.\n");
    return 0;
}