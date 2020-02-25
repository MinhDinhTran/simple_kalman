#ifndef __MATRIX_H__
#define __MATRIX_H__

struct matrix_t {
    int rows;
    int cols;
    float *vals;
};

struct matrix_t create_matrix(int rows, int cols);
int destroy_matrix(struct matrix_t matrix);
int destroy_matrix_ptr(struct matrix_t *matrix);

float get_el(struct matrix_t *matrix, int row, int col);
void set_el(struct matrix_t *matrix, int row, int col, float val);

int matrix_add(struct matrix_t *mat1, struct matrix_t *mat2, struct matrix_t *result);
int matrix_multiply(struct matrix_t *mat1, struct matrix_t *mat2, struct matrix_t *result);
int matrix_transpose(struct matrix_t *mat, struct matrix_t *result);

#endif