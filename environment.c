#include "environment.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int env_current_temperature = 17;

int env_update_movement() {
    int val = rand() % (ENV_MOVEMENT_MAX + 1 - ENV_MOVEMENT_MIN) + ENV_MOVEMENT_MIN;
    return val;
}

int env_update_temperature() {
    int val = rand() % (ENV_TEMPERATURE_MAX + 1 - ENV_TEMPERATURE_MIN) + ENV_TEMPERATURE_MIN;

    if (abs(env_current_temperature - val) <= 2) {
        env_current_temperature = val;
        return val;
    }

    return env_current_temperature;
}

struct environment_status* environment_update() {
    struct environment_status *update = malloc(sizeof(struct environment_status));
    update->movement = env_update_movement();
    update->temperature = env_update_temperature();

    return update;
}