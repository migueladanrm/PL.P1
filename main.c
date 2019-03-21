#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "env_tests.h"
#include "environment.h"


void environment_update_print(struct environment_status* es) {
    printf("ES:\tMovement: %i\tTemperature: %i\n", es->movement, es->temperature);
}

int main() {
    // Inicialización de 'time' necesaria para generar números pseudo-aleatorios.
    srand(time(NULL));

    for (int i = 0; i < 100; ++i) {
        struct environment_status *tmp = environment_update();
        environment_update_print(tmp);
    }

    return 0;
}