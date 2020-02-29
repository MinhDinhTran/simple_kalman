#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * TODO a better way to handle this is to accept an optional pointer
 * if the optional pointer is NULL return a new pointer, otherwise
 * use the existing pointer and return the existing pointer
 */


struct matrix_t create_matrix(int rows, int cols) {
    struct matrix_t matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.vals = malloc(sizeof(float)*rows*cols);

    return matrix;
}


int set_matrix(struct matrix_t *mat, int rows, int cols, float *vals) {
    mat->rows = rows;
    mat->cols = cols;
    mat->vals = vals;
}

struct matrix_t *create_matrix_ptr(int rows, int cols) {
    struct matrix_t *mat = NULL;
    mat = malloc(sizeof(struct matrix_t));
    mat->rows = rows;
    mat->cols = cols;
    mat->vals = malloc(sizeof(float)*rows*cols);
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

void print_matrix(struct matrix_t *matrix) {
    for(int i = 0; i < matrix->rows; i++) {
        for(int j = 0; j < matrix->cols; j++) {
            printf("%f ", get_el(matrix, i, j));
        }
        printf("\n");
    }
}

float get_el(struct matrix_t *matrix, int row, int col) {
    return matrix->vals[row * matrix->cols + col];
}

void set_el(struct matrix_t *matrix, int row, int col, float val) {
    matrix->vals[row * matrix->cols + col] = val;
}

struct matrix_t *matrix_add(struct matrix_t *mat1, struct matrix_t *mat2) {
    if (mat1->cols != mat2->cols || mat1->rows != mat2->rows) {
        perror("These matrices are not the same size!\n");
        return NULL;
    }
       
    struct matrix_t *result = create_matrix_ptr(mat1->rows, mat1->cols);

    for(int row = 0; row < mat1->rows; row++) {
        for(int col = 0; col < mat2->cols; col++) {
            float sum = get_el(mat1, row, col) + get_el(mat2, row, col);
            set_el(result, row, col, sum);
        }
    }
    return result;
}

struct matrix_t *matrix_multiply(struct matrix_t *mat1, struct matrix_t *mat2) {
    if (mat1->cols != mat2->rows) {
        return NULL;
    }
    
    struct matrix_t *result = create_matrix_ptr(mat1->rows, mat2->cols);

    for(int col = 0; col < mat2->cols; col++) {
        for(int row = 0; row < mat1->rows; row++) {
            float sum = 0;
            for(int i = 0; i < mat1->cols; i++) {
                sum += get_el(mat1, row, i) * get_el(mat2, i, col);
            }
            set_el(result, row, col, sum);
        }
    }
    return result;
}

struct matrix_t *matrix_transpose(struct matrix_t *mat) {
    struct matrix_t *result = create_matrix_ptr(mat->cols, mat->rows);
    
    for(int i = 0; i < mat->rows; i++) {
        for(int j = 0; j < mat->cols; j++) {
            set_el(result, j, i, get_el(mat, i, j));    
        }
    }
    return result;
}

int fill_cofactor(struct matrix_t *matrix, struct matrix_t *sub_matrix, int col) {
    for(int i = 1; i < matrix->rows; i++) {
        for(int j = 0; j < matrix->cols; j++) {
            if(j == col) continue;
            int col_index = j;
            if(j > col) {
                col_index -= 1;
            }
            set_el(sub_matrix, i - 1, col_index, get_el(matrix, i, j));
        }
    }
}

float matrix_determinant(struct matrix_t *mat) {
    if(mat->rows != mat->cols) {
        perror("Matrix is not a square matrix!!!");
        return 0;
    }

    if(mat->rows == 2) {
        float liebniz_det = get_el(mat, 0, 0)*get_el(mat, 1, 1) - get_el(mat, 1, 0)*get_el(mat, 0, 1);
        return liebniz_det;
    }

    float total = 0;
    struct matrix_t *sub_mat = create_matrix_ptr(mat->rows - 1, mat->cols - 1);
    float sign = 1;
    for(int i = 0; i < mat->cols; i++) {
        fill_cofactor(mat, sub_mat, i);
        float det = matrix_determinant(sub_mat);
        total += sign * get_el(mat, 0, i)*det;
        sign *= -1;
    } 
    destroy_matrix_ptr(sub_mat);
    return total;    
}

int fill_ignore_row_col(struct matrix_t *mat, struct matrix_t *sub_matrix, int row, int col) {
    if(mat->rows - 1 != sub_matrix->rows || mat->cols - 1  != sub_matrix->cols) {
        perror("This matrix is the wrong size for an ignore fill!\n");
        return -1;
    }

    for(int i = 0; i < mat->rows; i++) {
        for(int j = 0; j < mat->cols; j++) {
            if(i == row || j == col) {
                continue;
            }
            int row_index = i > row ? i - 1 : i;
            int col_index = j > col ? j - 1 : j;
            set_el(sub_matrix, row_index, col_index, get_el(mat, i, j));
        }
    }
}

struct matrix_t *matrix_of_minors(struct matrix_t *mat) {
    struct matrix_t *sub_mat = create_matrix_ptr(mat->rows - 1, mat->cols - 1);
    struct matrix_t *mat_of_minors = create_matrix_ptr(mat->rows, mat->cols);

    for(int i = 0; i < mat->rows; i++) {
        for(int j = 0; j < mat->cols; j++) {
            fill_ignore_row_col(mat, sub_mat, i, j);
            float det = matrix_determinant(sub_mat);
            set_el(mat_of_minors, i, j, det);
        }
    }
    destroy_matrix_ptr(sub_mat);
    return mat_of_minors;
}

struct matrix_t *matrix_cofactor(struct matrix_t *mat) {
    float sign = 1;
    struct matrix_t *mat_cofactor = matrix_of_minors(mat);
    for(int i = 0; i < mat->cols*mat->rows; i++) {
        mat_cofactor->vals[i] *= sign;
        sign *= -1;
    }
    return mat_cofactor;
}

struct matrix_t *matrix_inverse(struct matrix_t *mat) {
    float determinant = matrix_determinant(mat);
    struct matrix_t *cofactor = matrix_cofactor(mat);
    struct matrix_t *transpose = matrix_transpose(cofactor);

    for(int i = 0; i < mat->rows; i++) {
        for(int j = 0; j < mat->cols; j++) {
            float new_value = get_el(transpose, i, j) / determinant;
            set_el(transpose, i, j, new_value);
        }
    }
    destroy_matrix_ptr(cofactor);
    return transpose;
}