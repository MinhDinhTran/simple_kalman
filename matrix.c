#include "matrix.h"
#include <stdlib.h>

struct matrix_t create_matrix(int rows, int cols) {
    struct matrix_t matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.vals = malloc(sizeof(float)*rows*cols);

    return matrix;
}

int destroy_matrix(struct matrix_t matrix) {
    free(matrix.vals);
    return 0;
}

int destroy_matrix_ptr(struct matrix_t *matrix) {
    free(matrix->vals);
    free(matrix);
    return 0;
}

float get_el(struct matrix_t *matrix, int row, int col) {
    return matrix->vals[row * matrix->cols + col];
}

void set_el(struct matrix_t *matrix, int row, int col, float val) {
    matrix->vals[row * matrix->cols + col] = val;
}

int matrix_add(struct matrix_t *mat1, struct matrix_t *mat2, struct matrix_t *result) {
    if (mat1->cols != mat2->cols || mat1->rows != mat2->rows) {
        return -1;
    }
    if(result == NULL)
        *result = create_matrix(mat1->rows, mat1->cols);

    for(int row = 0; row < mat1->rows; row++) {
        for(int col = 0; col < mat2->cols; col++) {
            float sum = get_el(mat1, row, col) + get_el(mat2, row, col);
            set_el(result, row, col, sum);
        }
    }
    return 0;
}

int matrix_multiply(struct matrix_t *mat1, struct matrix_t *mat2, struct matrix_t *result) {
    if (mat1->cols != mat2->rows) {
        return -1;
    }
    if(result == NULL)
        *result = create_matrix(mat1->rows, mat2->cols);

    for(int col = 0; col < mat2->cols; col++) {
        for(int row = 0; row < mat1->rows; row++) {
            float sum = 0;
            for(int i = 0; i < mat1->cols; i++) {
                sum += get_el(mat1, row, i) * get_el(mat2, i, col);
            }
            set_el(result, row, col, sum);
        }
    }
    return 0;
}

int matrix_transpose(struct matrix_t *mat, struct matrix_t *result) {
    if(result == NULL)
        *result = create_matrix(mat->cols, mat->rows);
    
    for(int i = 0; i < mat->rows; i++) {
        for(int j = 0; j < mat->cols; j++) {
            set_el(result, j, i, get_el(mat, i, j));    
        }
    }
    return 0;
}