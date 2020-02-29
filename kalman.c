#include "kalman.h"
#include <stdlib.h>

/*
 * TODO:
 *      - drop the intermittent storage values and add them to the kalman parameters
 *      - add initialization function for parameters and state
 */

int predict(struct kalman_parameters_t *parameters, struct kalman_state_t *state,
            struct matrix_t *control, struct matrix_t *new_state) {
    struct matrix_t *state_forward = NULL;
    state_forward = matrix_multiply(&parameters->state_transition, &state->predicted_state);
    struct matrix_t *control_forward = NULL;
    control_forward = matrix_multiply(&parameters->control_model, control);
    struct matrix_t *predicted_state = NULL;
    predicted_state = matrix_add(state_forward, control_forward);
    copy_matrix(predicted_state, &state->predicted_state);

    struct matrix_t *F_t = NULL;
    F_t = matrix_transpose(&parameters->state_transition);

    struct matrix_t *first_m = NULL;
    first_m = matrix_multiply(&parameters->state_transition, &state->predicted_estimate_covariance);
    struct matrix_t *process_noise = NULL;
    process_noise = matrix_multiply(first_m, F_t);
    struct matrix_t *estimate_covariance = NULL;
    estimate_covariance = matrix_add(process_noise, &parameters->process_covariance);
    copy_matrix(estimate_covariance, &state->predicted_estimate_covariance);

    destroy_matrix_ptr(state_forward);
    destroy_matrix_ptr(control_forward);
    destroy_matrix_ptr(predicted_state);
    destroy_matrix_ptr(F_t);
    destroy_matrix_ptr(first_m);
    destroy_matrix_ptr(process_noise);
    destroy_matrix_ptr(estimate_covariance);

    return 0;
}

int update(struct kalman_parameters_t *parameters, struct matrix_t measurement,
           struct kalman_state_t *state, struct matrix_t *new_state) {
    
    struct matrix_t *measurement_residual = NULL;
    
    return 0;
}
