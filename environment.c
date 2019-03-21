#include "environment.h"
#include <stdio.h>
#include <stdlib.h>

#define ENV_TEMPERATURE_MIN 17
#define ENV_TEMPERATURE_MAX 34

#define ENV_MOVEMENT_MIN    0
#define ENV_MOVEMENT_MAX    5

/**
 * Actualización del entorno.
 */
struct environment_status {
    double movement;
    double temperature;
};

double env_update_movement() {
    return 0.0;
}

double env_update_temperature() {
    return 0.0;
}

struct environment_status* environment_update() {
    struct environment_status *update = malloc(sizeof(struct environment_status));
    update->movement = env_update_movement();
    update->temperature = env_update_temperature();

    return update;
}