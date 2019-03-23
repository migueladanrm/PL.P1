#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "environment.h"

#define ENV_TEMPERATURE_MAX_DIFF 2

// Temperatura actual.
int env_current_temperature = ENV_TEMPERATURE_MIN;

/**
 * Genera un valor de movimiento.
 * @return Movimiento (m/s).
 */
int env_update_movement() {
    int val = rand() % (ENV_MOVEMENT_MAX + 1 - ENV_MOVEMENT_MIN) + ENV_MOVEMENT_MIN;
    return val;
}

/**
 * Genera un valor de temperatura.
 * @return Temperatura (C°).
 */
int env_update_temperature() {
    int val = rand() % (ENV_TEMPERATURE_MAX + 1 - ENV_TEMPERATURE_MIN) + ENV_TEMPERATURE_MIN;

    if (abs(env_current_temperature - val) <= ENV_TEMPERATURE_MAX_DIFF)
        env_current_temperature = val;

    return env_current_temperature;
}

/**
 * Genera una actualización del entorno "físico".
 * @return Actualización del entorno.
 */
struct environment_status* environment_update() {
    struct environment_status *update = malloc(sizeof(struct environment_status));
    update->movement = env_update_movement();
    update->temperature = env_update_temperature();

    return update;
}