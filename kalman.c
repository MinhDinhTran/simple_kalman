#include "kalman.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * TODO:
 *      - drop the intermittent storage values and add them to the kalman parameters
 *      - add initialization function for parameters and state
 */

int predict(struct kalman_parameters_t *parameters, struct kalman_state_t *state,
            struct matrix_t *control) {
    struct matrix_t *state_forward = NULL;
    struct matrix_t *control_forward = NULL;
    struct matrix_t *predicted_state = NULL;
    struct matrix_t *F_t = NULL;
    struct matrix_t *first_m = NULL;
    struct matrix_t *process_noise = NULL;
    struct matrix_t *estimate_covariance = NULL;
    
    state_forward = matrix_multiply(&parameters->state_transition, &state->predicted_state);
    control_forward = matrix_multiply(&parameters->control_model, control);
    predicted_state = matrix_add(state_forward, control_forward);
    F_t = matrix_transpose(&parameters->state_transition);
    first_m = matrix_multiply(&parameters->state_transition, &state->predicted_estimate_covariance);
    process_noise = matrix_multiply(first_m, F_t);
    estimate_covariance = matrix_add(process_noise, &parameters->process_covariance);
    
    copy_matrix(predicted_state, &state->predicted_state);
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

int update(struct kalman_parameters_t *parameters, struct matrix_t *measurement,
           struct kalman_state_t *state) {
    
    struct matrix_t *y = NULL;
    struct matrix_t *obs_in_measurement = NULL;
    struct matrix_t *H_t = NULL;
    struct matrix_t *cov_intermediate = NULL;
    struct matrix_t *cov = NULL;
    struct matrix_t *S = NULL;
    struct matrix_t *S_inv = NULL;
    struct matrix_t *K_int = NULL;
    struct matrix_t *K = NULL;
    struct matrix_t *scaled_measurement = NULL;
    struct matrix_t *new_state = NULL;
    struct matrix_t *I = NULL;
    struct matrix_t *KtimesH = NULL;
    struct matrix_t *IminusKH = NULL;
    struct matrix_t *new_cov = NULL;

    obs_in_measurement = matrix_multiply(&parameters->observation_model, &state->predicted_state);
    y = matrix_subtract(measurement, obs_in_measurement);
    H_t = matrix_transpose(&parameters->observation_model);
    cov_intermediate = matrix_multiply(&parameters->observation_model, &state->predicted_estimate_covariance);
    cov = matrix_multiply(cov_intermediate, H_t);
    S = matrix_add(cov, &parameters->observation_covariance);
    K_int = matrix_multiply(&state->predicted_estimate_covariance, H_t);
    S_inv = matrix_inverse(S);
    K = matrix_multiply(K_int, S_inv);
    scaled_measurement = matrix_multiply(K, y);
    new_state = matrix_add(&state->predicted_state, scaled_measurement);
    KtimesH = matrix_multiply(K, &parameters->observation_model);
    I = identity(KtimesH->rows);
    IminusKH = matrix_subtract(I, KtimesH);
    new_cov = matrix_multiply(IminusKH, &state->predicted_estimate_covariance);

    copy_matrix(new_cov, &state->predicted_estimate_covariance);
    copy_matrix(new_state, &state->predicted_state);

    destroy_matrix_ptr(y);
    destroy_matrix_ptr(obs_in_measurement);
    destroy_matrix_ptr(H_t);
    destroy_matrix_ptr(cov_intermediate);
    destroy_matrix_ptr(cov);
    destroy_matrix_ptr(S);
    destroy_matrix_ptr(S_inv);
    destroy_matrix_ptr(K_int);
    destroy_matrix_ptr(K);
    destroy_matrix_ptr(scaled_measurement);
    destroy_matrix_ptr(KtimesH);
    destroy_matrix_ptr(IminusKH);
    destroy_matrix_ptr(new_state);
    destroy_matrix_ptr(new_cov);

    return 0;
}
