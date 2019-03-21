#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "env_tests.h"
#include "environment.h"

time_t now;

int random_test() {
    srand(time(now));

    for (int i = 0; i < 1; ++i) {
        double tmp = log2(rand());
        int dec = (int) ((tmp - (int) tmp) * 100);
        int pair = dec % 2;

        return pair;
    }
}


void delay(int number_of_seconds) {
    // Converting time into milli_seconds
    int milli_seconds = 1000 * sqrt(number_of_seconds) * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds);
}

int main() {
    for (int i = 0; i < 10; i++) {
        printf("%i\n", random_test());
        delay(1);
    }

    return 0;
}