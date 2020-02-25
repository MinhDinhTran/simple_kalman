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

    struct matrix_t result;

    printf("adding matrices\n");
    matrix_add(&matrix, &matrix, &result);

    printf("Comparing matrices");
    bool success = true; 
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(!nearly_equal(get_el(&result, i, j), test_result[i * 3 + j])) {
                success = false;
            }
        }
    }
    printf("Result of add is: %d\n", success);

    // Multiplication test
    struct matrix_t result2;
    printf("Multiplying matrices\n");
    matrix_multiply(&matrix, &matrix, &result2);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%f ", get_el(&result2, i, j));
        }
        printf("\n");
    }

    // Transpose test
    struct matrix_t result3;
    printf("Tranposing matrix\n");
    matrix_transpose(&matrix, &result3);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%f ", get_el(&result3, i, j));
        }
        printf("\n");
    }
}

void test_kalman(void) {
    printf("Beginning kalman filter test\n");
    struct kalman_parameters_t parameters;
    struct kalman_state_t state;

    //parameters.state_transition = 
}