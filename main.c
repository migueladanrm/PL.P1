/*
 * Lenguajes de Programación | I Semestre - 2019
 * Proyecto 1:  Paradigma imperativa
 * Autores:     Miguel Rivas
 *              Jafet Suárez
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "environment.h"

// CONSTANTES

/**
 * Tamaño máximo de muestra que se utilizará para evaluación de datos.
 */
#define HISTORY_SIZE                        10

/**
 * Intervalo de actualización del entorno.
 */
#define ENV_UPDATE_INTERVAL                      1

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
 * Dummie para el apagado de luces.
 * En este procedimiento se deberían realizar acciones para apagar las luces.
 */
void turn_off_lights() {
    printf("Lights off!");
}

/**
 * Retrasa la ejecución del programa durante una cantidad especificada de segundos.
 * @param s Segundos.
 */
void delay(unsigned int s) {
    int milli_seconds = 1000 * s;
    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}

void print_datetime() {
    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("%s\t",buffer);
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

void es_print(struct environment_status *es) {
    printf("ES:\tMovement: %i\tTemperature: %i\n", es->movement, es->temperature);
}

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

void print_history(struct environment_status* es) {
    while (es != NULL) {
        printf("ES:\tMovement: %i\tTemperature: %i\n", es->movement, es->temperature);
        es = es->next;
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

    eval_movement = eval_movement / HISTORY_SIZE;
    eval_temperature = eval_temperature / HISTORY_SIZE;

    if (eval_movement <= ENV_MOVEMENT_MIN_TO_LIGHTS_OFF && eval_temperature < ENV_TEMPERATURE_MIN_TO_LIGHTS_OFF)
        return true;

    return false;
}

/**
 * Rutina de comprobaciones.
 */
void program() {
    bool MUST_TURN_OFF_LIGHTS;

    while (1) {
        struct environment_status *tmp_update = environment_update();
        es_history_push(tmp_update);

        if (es_order(history) == HISTORY_SIZE) {
            MUST_TURN_OFF_LIGHTS = environment_check(history);
            es_history_reset();
            break;
        }
        delay(ENV_UPDATE_INTERVAL);
    }

    if (MUST_TURN_OFF_LIGHTS == true)
        turn_off_lights();
    else {
        printf("No se deben apagar las luces.\n");
    }

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