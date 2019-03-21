#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "env_tests.h"
#include "environment.h"

#define HISTORY_SIZE    20
#define ENV_UPDT_DELAY  2

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

bool check_environment(){
    // pendiente.
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
            MUST_TURN_OFF_LIGHTS = check_environment();
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