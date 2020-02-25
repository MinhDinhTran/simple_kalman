#include "kalman.h"

/*
 * TODO:
 *      - drop the intermittent storage values and add them to the kalman parameters
 *      - add initialization function for parameters and state
 */

int predict(struct kalman_parameters_t *parameters, struct kalman_state_t *state,
            struct matrix_t *control, struct matrix_t *new_state) {
    struct matrix_t *state_forward = NULL;
    matrix_multiply(&parameters->observation_model, &state->predicted_state, state_forward);
    struct matrix_t *control_forward = NULL;
    matrix_multiply(&parameters->control_model, control, control_forward);
    matrix_add(state_forward, control_forward, &state->predicted_state);

    struct matrix_t *F_t = NULL;
    matrix_transpose(&parameters->observation_model, F_t);
    struct matrix_t *first_m = NULL;
    matrix_multiply(&parameters->observation_model, &state->predicted_estimate_covariance, first_m);
    struct matrix_t *process_noise = NULL;
    matrix_multiply(first_m, F_t, process_noise);
    matrix_add(process_noise, &parameters->process_covariance, &state->predicted_estimate_covariance);

    return 0;
}

int update(struct kalman_parameters_t *parameters, struct matrix_t measurement,
           struct kalman_state_t *state, struct matrix_t *new_state) {
    
    return 0;
}
