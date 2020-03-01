#ifndef __MATRIX_H__
#define __MATRIX_H__

struct matrix_t {
    int rows;
    int cols;
    float *vals;
};

struct matrix_t create_matrix(int rows, int cols);
int set_matrix(struct matrix_t *mat, int rows, int cols, float *vals);
struct matrix_t *create_matrix_ptr(int rows, int cols);
int copy_matrix(struct matrix_t *from, struct matrix_t *to);
int destroy_matrix(struct matrix_t matrix);
int destroy_matrix_ptr(struct matrix_t *matrix);

void print_matrix(struct matrix_t *matrix);

float get_el(struct matrix_t *matrix, int row, int col);
void set_el(struct matrix_t *matrix, int row, int col, float val);

struct matrix_t *matrix_add(struct matrix_t *mat1, struct matrix_t *mat2);
struct matrix_t *matrix_subtract(struct matrix_t *mat1, struct matrix_t *mat2);
struct matrix_t *matrix_multiply(struct matrix_t *mat1, struct matrix_t *mat2);
struct matrix_t *matrix_transpose(struct matrix_t *mat);
float matrix_determinant(struct matrix_t *mat);
struct matrix_t *matrix_inverse(struct matrix_t *mat);
struct matrix_t *identity(int size);

#endif