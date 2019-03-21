#ifndef PL_P1_ENVIRONMENT_H
#define PL_P1_ENVIRONMENT_H

#define ENV_TEMPERATURE_MIN 17
#define ENV_TEMPERATURE_MAX 34

#define ENV_MOVEMENT_MIN    0
#define ENV_MOVEMENT_MAX    5

struct environment_status {
    int movement;
    int temperature;
    struct environment_status *next;
};

//typedef struct environment_status environment_status;
struct environment_status* environment_update();

#endif //PL_P1_ENVIRONMENT_H

