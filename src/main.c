
#include <stdio.h>
#include <stdint.h>
#include "matrix.h"
#include "matrix_types.h"
#include "field.h"

int main(void) {
    size_t rows, cols;
    long p;

    printf("Enter a prime number for the field: ");
    if (scanf("%ld", &p) != 1 || !field_is_prime(p)) {
        printf("Error: please enter a valid prime number.\n");
        return 1;
    }

    printf("Enter number of rows and columns: ");
    if (scanf("%zu %zu", &rows, &cols) != 2 ||
        rows == 0 || cols == 0 ||
        rows > SIZE_MAX / cols ||
        rows * cols > SIZE_MAX / sizeof(FieldElement)) {
        printf("Error: invalid matrix dimensions.\n");
        return 1;
    }

    Matrix m;

    if (!matrix_init(&m, rows, cols, p)) {
        printf("Error: could not initialize matrix.\n");
        return 1;
    }

    printf("Enter %zu matrix elements:\n", rows * cols);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            long value;

            if (scanf("%ld", &value) != 1 ||
                !field_init(&m.data[i * cols + j], value, p)) {
                printf("Error: invalid matrix element.\n");
                matrix_free(&m);
                return 1;
            }
        }
    }

    printf("\nYour matrix:\n");

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            printf("%ld ", m.data[i * cols + j].value);
        }
        printf("\n");
    }

    printf("\nMATRIX CLASSIFICATION \n");
    matrix_print_types(&m);

    matrix_free(&m);
    return 0;
}
