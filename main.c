#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "env_tests.h"
#include "environment.h"

struct environment_status *history;


void environment_update_print(struct environment_status* es) {
    printf("ES:\tMovement: %i\tTemperature: %i\n", es->movement, es->temperature);
}


void insert_es(struct environment_status* es){
    struct environment_status *new = (struct environment_status*)malloc(sizeof(struct environment_status));
    new->movement = es->movement;
    new->temperature = es->temperature;
    new->sig = NULL;

    if(history == NULL){
        history = new;
    } else{
        new->sig = history;
        history = new;
    }
}

void print_history(struct environment_status* es){
    while(es != NULL){
        printf("ES:\tMovement: %i\tTemperature: %i\n", es->movement, es->temperature);
        es= es->sig;
    }
}

void reset_list(){
    free(history);
    history=NULL;
}

int main() {
    // Inicialización de 'time' necesaria para generar números pseudo-aleatorios.
    srand(time(NULL));

    for (int i = 0; i < 100; ++i) {
        struct environment_status *tmp = environment_update();
        insert_es(tmp);

        //environment_update_print(tmp);
    }

    print_history(history);

    return 0;
}