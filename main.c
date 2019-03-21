#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "env_tests.h"
#include "environment.h"

#define HISTORY_SIZE    10
#define ENV_UPDT_DELAY  1
#define ENV_MOVEMENT_MIN_TO_LIGHTS_OFF    2.5
#define ENV_TEMPERATURE_MIN_TO_LIGHTS_OFF 25

struct environment_status *history;

void delay(int s) {
    int milli_seconds = 1000 * s;
    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}

void environment_update_print(struct environment_status* es) {
    printf("ES:\tMovement: %i\tTemperature: %i\n", es->movement, es->temperature);
}


void insert_es(struct environment_status* es){
    struct environment_status *new = (struct environment_status*)malloc(sizeof(struct environment_status));
    new->movement = es->movement;
    new->temperature = es->temperature;
    new->next = NULL;

    if(history == NULL){
        history = new;
    } else{
        new->next = history;
        history = new;
    }
}

void print_history(struct environment_status* es){
    while(es != NULL){
        printf("ES:\tMovement: %i\tTemperature: %i\n", es->movement, es->temperature);
        es= es->next;
    }
}

void es_reset() {
    struct environment_status* es = history;
    struct environment_status* tmp;

    while(es != NULL){
        tmp = es->next;
        free(es);
        es = tmp;
    }
    free(history);
    history = NULL;

}

int es_order(struct environment_status* es) {
    int order = 0;
    do {
        order++;
        es = es->next;
    } while (es != NULL);

    return order;
}

bool check_environment(struct environment_status *es) {

    float eval_movement = 0.0;
    float eval_temperature = 0.0;

    while (es != NULL) {
        eval_movement = eval_movement + es->movement;
        eval_temperature = eval_temperature + es->temperature;
        es = es->next;
    }

    eval_movement = (float)(eval_movement / HISTORY_SIZE);
    eval_temperature = (float)(eval_temperature / HISTORY_SIZE);

    printf("\nMOVEMENT: %f\tTEMPERATURE: %f\n", eval_movement, eval_temperature);


    if (eval_movement <= ENV_MOVEMENT_MIN_TO_LIGHTS_OFF && eval_temperature < ENV_TEMPERATURE_MIN_TO_LIGHTS_OFF)
        return true;

    return false;
}

void turn_off_lights() {
    printf("Lights off!");
}

void program() {
    bool MUST_TURN_OFF_LIGHTS;

    while (1) {
        struct environment_status *tmp_update = environment_update();
        insert_es(tmp_update);

        if (es_order(history) == HISTORY_SIZE) {
            MUST_TURN_OFF_LIGHTS = check_environment(history);
            es_reset();
            break;
        }
        delay(ENV_UPDT_DELAY);
    }

    if (MUST_TURN_OFF_LIGHTS == true)
        turn_off_lights();
    else {
        printf("No se deben apagar las luces.\n");
    }

    program();
}

int main() {
    // Inicialización de 'time' necesaria para generar números pseudo-aleatorios.
    srand(time(NULL));

    // Ejecuta el programa.
    program();

    return 0;
}