
#include <stdlib.h>
#include <stdint.h>
#include "matrix.h"
#include "field.h"


bool matrix_init(Matrix *m, size_t rows, size_t cols, long p)
{
    if (m == NULL || rows == 0 || cols == 0 ||
        !field_is_prime(p) || rows > SIZE_MAX / cols ||
        rows * cols > SIZE_MAX / sizeof(FieldElement))
        return false;

    m->rows = rows;
    m->cols = cols;
    m->p = p;
    m->data = calloc(rows * cols, sizeof(FieldElement));

    if (m->data == NULL)
    {
        m->rows = 0;
        m->cols = 0;
        return false;
    }

    for (size_t i = 0; i < rows * cols; i++)
        m->data[i].p = p;

    return true;
}

void matrix_free(Matrix *m)
{
    if (m != NULL)
    {
        free(m->data);
        m->data = NULL;
        m->rows = 0;
        m->cols = 0;
        m->p = 0;
    }
}

bool matrix_get(const Matrix *m, size_t row, size_t col, FieldElement *result)
{
    if (m == NULL || m->data == NULL || result == NULL ||
        row >= m->rows || col >= m->cols)
        return false;

    *result = m->data[row * m->cols + col];
    return true;
}

bool matrix_add(const Matrix *a, const Matrix *b, Matrix *result)
{
    if (a == NULL || b == NULL || result == NULL ||
        a->data == NULL || b->data == NULL ||
        a->rows != b->rows || a->cols != b->cols || a->p != b->p)
        return false;

    if (!matrix_init(result, a->rows, a->cols, a->p))
        return false;

    for (size_t i = 0; i < a->rows * a->cols; i++)
    {
        if (!field_add(a->data[i], b->data[i], &result->data[i]))
        {
            matrix_free(result);
            return false;
        }
    }

    return true;
}

bool matrix_scale(const Matrix *m, FieldElement scalar, Matrix *result)
{
    if (m == NULL || result == NULL || m->data == NULL ||
        m->p != scalar.p)
        return false;

    if (!matrix_init(result, m->rows, m->cols, m->p))
        return false;

    for (size_t i = 0; i < m->rows * m->cols; i++)
    {
        if (!field_mul(m->data[i], scalar, &result->data[i]))
        {
            matrix_free(result);
            return false;
        }
    }

    return true;
}

bool matrix_transpose(const Matrix *m, Matrix *result)
{
    if (m == NULL || result == NULL || m->data == NULL)
        return false;

    if (!matrix_init(result, m->cols, m->rows, m->p))
        return false;

    for (size_t i = 0; i < m->rows; i++)
        for (size_t j = 0; j < m->cols; j++)
            result->data[j * result->cols + i] =
                m->data[i * m->cols + j];

    return true;
}

bool matrix_multiply(const Matrix *a, const Matrix *b, Matrix *result)
{
    if (a == NULL || b == NULL || result == NULL ||
        a->data == NULL || b->data == NULL ||
        a->cols != b->rows || a->p != b->p)
        return false;

    if (!matrix_init(result, a->rows, b->cols, a->p))
        return false;

    for (size_t i = 0; i < a->rows; i++)
    {
        for (size_t j = 0; j < b->cols; j++)
        {
            FieldElement sum = {0, a->p};

            for (size_t k = 0; k < a->cols; k++)
            {
                FieldElement product;
                FieldElement next;

                if (!field_mul(a->data[i * a->cols + k],
                               b->data[k * b->cols + j], &product) ||
                    !field_add(sum, product, &next))
                {
                    matrix_free(result);
                    return false;
                }

                sum = next;
            }

            result->data[i * result->cols + j] = sum;
        }
    }

    return true;
}

bool matrix_equal(const Matrix *a, const Matrix *b)
{
    if (a == NULL || b == NULL || a->data == NULL ||
        b->data == NULL || a->rows != b->rows ||
        a->cols != b->cols || a->p != b->p)
        return false;

    for (size_t i = 0; i < a->rows * a->cols; i++)
    {
        if (!field_equal(a->data[i], b->data[i]))
            return false;
    }

    return true;
}
