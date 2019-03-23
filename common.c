#include <stdio.h>
#include <time.h>
#include "common.h"

/**
 * Retrasa la ejecución del programa durante una cantidad especificada de segundos.
 * @param s Segundos.
 */
void delay(unsigned int s) {
    int milli_seconds = 1000 * s;
    clock_t start_time = clock();

    while (clock() < start_time + milli_seconds);
}

/**
 * Imprime la fecha y hora seguido de una tabulación.
 */
void print_datetime() {
    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("%s\t",buffer);
}
