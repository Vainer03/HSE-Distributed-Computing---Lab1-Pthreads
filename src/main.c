#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "main.h"
#include "./Task_1/monte_carlo.h"
#include "./Task_2/mandelbrot_set.h"
#include "./Task_3/rwlock.h"

int main_test(int argc, char** argv) {
    uint64_t thread_counts[] = {1, 2, 4, 8, 16};
    uint64_t cat_counts[] = {100, 1000, 10000, 100000, 1000000};
    size_t thread_count_len = sizeof(thread_counts) / sizeof(thread_counts[0]);
    size_t cat_count_len = sizeof(cat_counts) / sizeof(cat_counts[0]);

    for (size_t i = 0; i < thread_count_len; i++) {
        for (size_t j = 0; j < cat_count_len; j++) {
            char command[100];
            snprintf(command, sizeof(command), "./Task_1/monte_carlo %llu %llu", thread_counts[i], cat_counts[j]);
            printf("Running with %llu threads and %llu cats: \n", thread_counts[i], cat_counts[j]);
            system(command);
        }
    }
    return 0;
}
