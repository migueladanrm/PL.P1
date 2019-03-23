/*
 * Lenguajes de Programación | I Semestre - 2019
 * Proyecto 1:  Paradigma imperativa
 * Autores:     Miguel Rivas    <migueladanrm@estudiantec.cr>
 *              Jafet Suárez    <jsuarez@estudiantec.cr>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "common.h"
#include "environment.h"

/* CONSTANTES
 * Notas:
 * - Si se desea aumentar/disminuir la cantidad de muestras y tiempo, se pueden
 *   ajustar las constantes 'HISTORY_SIZE' y 'ENV_UPDATE_INTERVAL' respectivamente.
 */
/**
 * Tamaño máximo de muestra que se utilizará para evaluación de datos.
 */
#define HISTORY_SIZE                        25

/**
 * Intervalo de actualización del entorno (segundos).
 */
#define ENV_UPDATE_INTERVAL                 1

/**
 * Valor medio de movimiento para ejecutar acciones.
 */
#define ENV_MOVEMENT_MIN_TO_LIGHTS_OFF      2.5

/**
 * Valor medio de temperatura para ejecutar acciones.
 */
#define ENV_TEMPERATURE_MIN_TO_LIGHTS_OFF   25

/**
 * Historial de actualizaciones del entorno.
 */
struct environment_status *history;

/**
 * "Acción" para el apagado de luces.
 * En este procedimiento se deberían realizar acciones para apagar las luces.
 */
void turn_off_lights(bool off) {
    print_datetime();
    if (off == true)
        printf("The lights have been turned off!\n");
    else
        printf("There is someone in the room. The lights have not been turned off.\n");
}

/**
 * Obtiene el orden (cantidad de elementos) de una lista de actualizaciones de entorno.
 * @param es Cabeza de la lista.
 * @return Número de elementos en la lista.
 */
unsigned int es_order(struct environment_status* es) {
    unsigned int order = 0;

    do {
        order++;
        es = es->next;
    } while (es != NULL);

    return order;
}

/**
 * Imprime una actualización de estado de entorno.
 * @param es Actualización estado de entorno.
 */
void es_print(struct environment_status *es) {
    print_datetime();
    printf("ES ->\tMovement: %i m/s\tTemperature: %i C\n", es->movement, es->temperature);
}

/**
 * Inserta una actualización al historial de estados de entorno.
 * @param es Actualización de estado de entorno
 */
void es_history_push(struct environment_status *es) {
    struct environment_status *new = (struct environment_status *) malloc(sizeof(struct environment_status));
    new->movement = es->movement;
    new->temperature = es->temperature;
    new->next = NULL;

    if (history == NULL)
        history = new;
    else {
        new->next = history;
        history = new;
    }
}

/**
 * Restablece el historial de actualizaciones del entorno.
 */
void es_history_reset() {
    struct environment_status *es = history;
    struct environment_status *tmp;

    while (es != NULL) {
        tmp = es->next;
        free(es);
        es = tmp;
    }

    free(history);
    history = NULL;

    print_datetime();
    printf("The history has been cleaned.\n");
}

/**
 * Comprobación de entorno.
 * @param es Arreglo de actualizaciones del entorno a evaluar.
 * @return Evaluación booleana.
 */
bool environment_check(struct environment_status *es) {
    float eval_movement = 0.0;
    float eval_temperature = 0.0;

    while (es != NULL) {
        eval_movement = eval_movement + es->movement;
        eval_temperature = eval_temperature + es->temperature;
        es = es->next;
    }

    // Ponderación de resultados de sesión.
    eval_movement = eval_movement / HISTORY_SIZE;
    eval_temperature = eval_temperature / HISTORY_SIZE;

    print_datetime();
    printf("Session check result (average):\tM: %f m/s\tT: %f C\n",eval_movement,eval_temperature);

    // Se verifican las condiciones necesarias para el apagado de las luces.
    if (eval_movement <= ENV_MOVEMENT_MIN_TO_LIGHTS_OFF && eval_temperature < ENV_TEMPERATURE_MIN_TO_LIGHTS_OFF)
        return true;

    return false;
}

/**
 * Rutina de comprobaciones.
 */
void program() {
    print_datetime();
    printf("Initializing check routine session (%i samples every %i seconds)...\n", HISTORY_SIZE,
           ENV_UPDATE_INTERVAL * HISTORY_SIZE);

    bool MUST_TURN_OFF_LIGHTS;

    while (1) {
        struct environment_status *tmp_update = environment_update();
        es_history_push(tmp_update);

        es_print(tmp_update);

        // Se verifica si el historial tiene la cantidad de muestras necesarias para la comprobación.
        if (es_order(history) == HISTORY_SIZE) {
            MUST_TURN_OFF_LIGHTS = environment_check(history);
            es_history_reset();
            break;
        }

        delay(ENV_UPDATE_INTERVAL);
    }

    turn_off_lights(MUST_TURN_OFF_LIGHTS);

    printf("\n");

    program();
}

/**
 * Punto de entrada del programa.
 * @return Código de salida.
 */
int main() {
    print_datetime();
    printf("Initializing environment...\n\n");

    // Inicialización de 'time' necesaria para generar números pseudo-aleatorios.
    srand(time(NULL));

    // Ejecuta el programa.
    program();

    return 0;
}