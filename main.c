#include "matrix.h"
#include "kalman.h"
#include "util.h"
#include "stdio.h"
#include "stdbool.h"

void test_kalman(void);
void test_matrices(void);

int main(int argc, char *argv[]) {
    test_kalman();
    test_matrices();
    return 0;
}

void test_matrices(void) {
    printf("Testing matrix library\n");
    float test_values[9] = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    }; 
    float test_result[9] = {
        2, 4, 6,
        8, 10, 12,
        14, 16, 18
    }; 
    struct matrix_t matrix;
    matrix.cols = 3;
    matrix.rows = 3;
    matrix.vals = test_values;

    struct matrix_t *result = NULL;

    printf("adding matrices\n");
    result = matrix_add(&matrix, &matrix);

    printf("Comparing matrices\n");
    bool success = true; 
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(!nearly_equal(get_el(result, i, j), test_result[i * 3 + j])) {
                success = false;
            }
        }
    }
    destroy_matrix_ptr(result);

    printf("Result of add is: %d\n", success);

    // Multiplication test
    struct matrix_t *result2;
    printf("Multiplying matrices\n");
    result2 = matrix_multiply(&matrix, &matrix);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%f ", get_el(result2, i, j));
        }
        printf("\n");
    }
    destroy_matrix_ptr(result2);

    // Transpose test
    struct matrix_t *result3;
    printf("Tranposing matrix\n");
    result3 = matrix_transpose(&matrix);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%f ", get_el(result3, i, j));
        }
        printf("\n");
    }
    destroy_matrix_ptr(result3);

    float test_values2[9] = {
        13, 22, 31,
        42, 51, 6,
        73, 84, 91
    }; 
    float test_result2[9] = {
        2, 4, 6,
        8, 10, 12,
        14, 16, 18
    }; 
    struct matrix_t matrix2;
    matrix2.cols = 3;
    matrix2.rows = 3;
    matrix2.vals = test_values2;


    // Calculate determinant
    float det = matrix_determinant(&matrix2);
    printf("Final det: %f\n", det);

    //Calculate inverse
    struct matrix_t *result4;
    result4 = matrix_inverse(&matrix2);
    printf("Matrix inverse\n");
    print_matrix(result4);
    destroy_matrix_ptr(result4);
}

void test_kalman(void) {
    printf("Beginning kalman filter test\n");
    struct kalman_parameters_t parameters;
    struct kalman_state_t state;

    float dt = 0.1;

    float A[16] = {
        1, 0, dt, 0,
        0, 1, 0, dt,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    float B[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    float Q[16] = {
        10, 0, 0, 0,
        0, 10, 0, 0,
        0, 0, 10, 0,
        0, 0, 0, 10
    };

    //parameters.state_transition = 
}