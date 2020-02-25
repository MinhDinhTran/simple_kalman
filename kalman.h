#ifndef __KALMAN_H__
#define __KALMAN_H__

#include "matrix.h"


struct kalman_parameters_t {
    struct matrix_t state_transition;
    struct matrix_t control_model;
    struct matrix_t observation_model;
    struct matrix_t process_covariance;
    struct matrix_t observation_covariance;
};

struct kalman_state_t {
    struct matrix_t predicted_state;
    struct matrix_t predicted_estimate_covariance;
};


int predict(struct kalman_parameters_t *parameters, struct kalman_state_t *state,
            struct matrix_t *control, struct matrix_t *new_state);

int update(struct kalman_parameters_t *parameters, struct matrix_t measurement,
           struct kalman_state_t *state, struct matrix_t *new_state);

#endif