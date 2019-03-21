#ifndef PL_P1_ENVIRONMENT_H
#define PL_P1_ENVIRONMENT_H


struct environment_status {
    int movement;
    int temperature;
    struct environment_status *sig;
};

//typedef struct environment_status environment_status;
struct environment_status* environment_update();

#endif //PL_P1_ENVIRONMENT_H

