//
// Created by Miguel on 20/03/2019.
//

#ifndef PL_P1_ENVIRONMENT_H
#define PL_P1_ENVIRONMENT_H


struct environment_status {
    double movement;
    double temperature;
};

//typedef struct environment_status environment_status;
struct environment_status* environment_update();

#endif //PL_P1_ENVIRONMENT_H

