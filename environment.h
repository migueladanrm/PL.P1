#ifndef PL_P1_ENVIRONMENT_H
#define PL_P1_ENVIRONMENT_H

// Constantes de valores mínimos y máximos.

#define ENV_TEMPERATURE_MIN 17
#define ENV_TEMPERATURE_MAX 34

#define ENV_MOTION_MIN    0
#define ENV_MOTION_MAX    5

/**
 * Instancia de entorno "físico".
 */
struct environment_status {
    int motion;
    int temperature;
    struct environment_status *next;
};

struct environment_status* environment_update();

#endif //PL_P1_ENVIRONMENT_H
