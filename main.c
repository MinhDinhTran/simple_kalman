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
    print_matrix(result);

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
    float R[16] = {
        5, 0, 0, 0,
        0, 5, 0, 0,
        0, 0, 5, 0,
        0, 0, 0, 5
    };

    struct matrix_t A_mat;
    struct matrix_t B_mat;
    struct matrix_t Q_mat;
    struct matrix_t R_mat;
    printf("setting matrices\n");
    set_matrix(&A_mat, 4, 4, A);
    set_matrix(&B_mat, 4, 4, B);
    set_matrix(&Q_mat, 4, 4, Q);
    set_matrix(&R_mat, 4, 4, R);

    parameters.state_transition = A_mat;
    parameters.control_model = B_mat;
    parameters.process_covariance = Q_mat;

    float X[4] = {
        0,
        0,
        1,
        1
    };
    set_matrix(&state.predicted_state, 4, 1, X);

    float P[16] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
    set_matrix(&state.predicted_estimate_covariance, 4, 4, P);
    printf("Beginning prediction\n");
    float cntrl[4] = {0, 0, 0, 0};
    struct matrix_t control_input;
    set_matrix(&control_input, 4, 1, cntrl);   
    for(int i = 0; i < 5; i++) {
        predict(&parameters, &state, &control_input, NULL);
        printf("Iteration %d\n", i);
        print_matrix(&state.predicted_state);
        print_matrix(&state.predicted_estimate_covariance);
    }
}