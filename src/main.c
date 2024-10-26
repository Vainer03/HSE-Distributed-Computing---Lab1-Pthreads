#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>

#include "./Task_1/monte_carlo.h"
#include "./Task_2/mandelbrot_set.h"
#include "./Task_3/rwlock.h"

void run_task_1_more_text() {
    uint64_t number_of_threads[] = {1, 2, 4, 8, 16, 32, 64};
    uint64_t number_of_cats[] = {100, 1000, 10000, 100000, 1000000, 10000000};
    size_t thread_count_len = sizeof(number_of_threads) / sizeof(number_of_threads[0]);
    size_t cat_count_len = sizeof(number_of_cats) / sizeof(number_of_cats[0]);
    for (size_t i = 0; i < thread_count_len; i++) {
        for (size_t j = 0; j < cat_count_len; j++) {
            char command[100];
            snprintf(command, sizeof(command), "monte_carlo.exe %llu %llu", number_of_threads[i], number_of_cats[j]);
            printf("\nRunning with %llu threads and %llu cats: \n", number_of_threads[i], number_of_cats[j]);
            system(command);
        }
    }
}

void run_task_1_short() {
    uint64_t number_of_threads[] = {1, 2, 4, 8, 16, 32, 64};
    uint64_t number_of_cats[] = {100, 1000, 10000, 100000, 1000000, 10000000};
    size_t thread_count_len = sizeof(number_of_threads) / sizeof(number_of_threads[0]);
    size_t cat_count_len = sizeof(number_of_cats) / sizeof(number_of_cats[0]);
    for (size_t i = 0; i < thread_count_len; i++) {
        for (size_t j = 0; j < cat_count_len; j++) {
            char command[100];
            snprintf(command, sizeof(command), "monte_carlo.exe %llu %llu", number_of_threads[i], number_of_cats[j]);
            printf("\n");
            system(command);
        }
    }
}

void run_task_2_more_text() {
    uint64_t number_of_threads[] = {1, 2, 4, 8, 16, 32, 64};
    uint64_t number_of_points[] = {100, 1000, 10000, 100000, 1000000, 10000000};
    size_t thread_count_len = sizeof(number_of_threads) / sizeof(number_of_threads[0]);
    size_t point_count_len = sizeof(number_of_points) / sizeof(number_of_points[0]);
    for (size_t i = 0; i < thread_count_len; i++) {
        for (size_t j = 0; j < point_count_len; j++) {
            char command[100];
            snprintf(command, sizeof(command), "mandelbrot_set.exe %llu %llu", number_of_threads[i], number_of_points[j]);
            printf("\nRunning with %llu threads and %llu points: \n", number_of_threads[i], number_of_points[j]);
            system(command);
        }
    }
}

void run_task_2_short() {
    uint64_t number_of_threads[] = {1, 2, 4, 8, 16, 32, 64};
    uint64_t number_of_points[] = {100, 1000, 10000, 100000, 1000000, 10000000};
    size_t thread_count_len = sizeof(number_of_threads) / sizeof(number_of_threads[0]);
    size_t point_count_len = sizeof(number_of_points) / sizeof(number_of_points[0]);
    for (size_t i = 0; i < thread_count_len; i++) {
        for (size_t j = 0; j < point_count_len; j++) {
            char command[100];
            snprintf(command, sizeof(command), "mandelbrot_set.exe %llu %llu", number_of_threads[i], number_of_points[j]);
            printf("\n");
            system(command);
        }
    }
}

void run_task_3_more_text() {
    uint64_t number_of_threads[] = {1, 2, 4, 8, 16, 32};
    uint64_t number_of_inserts[] = {10, 100, 1000, 10000};
    uint64_t number_of_ops[] = {100, 1000, 10000, 100000};
    size_t thread_count_len = sizeof(number_of_threads) / sizeof(number_of_threads[0]);
    size_t inserts_count_len = sizeof(number_of_inserts) / sizeof(number_of_inserts[0]);
    for (size_t i = 0; i < thread_count_len; i++) {
        for (size_t j = 0; j < inserts_count_len; j++) {
            char command[100];
            snprintf(command, sizeof(command), "rwlock.exe %llu %llu %llu %lf %lf", number_of_threads[i], number_of_inserts[j], number_of_ops[j], 0.34, 0.34);
            printf("\nRunning with %llu threads, %llu inserts and %llu ops: \n", number_of_threads[i], number_of_inserts[j], number_of_ops[j]);
            system(command);
        }
    }
}

void run_task_3_short() {
    uint64_t number_of_threads[] = {1, 2, 4, 8, 16, 32};
    uint64_t number_of_inserts[] = {10, 100, 1000, 10000};
    uint64_t number_of_ops[] = {100, 1000, 10000, 100000};
    size_t thread_count_len = sizeof(number_of_threads) / sizeof(number_of_threads[0]);
    size_t inserts_count_len = sizeof(number_of_inserts) / sizeof(number_of_inserts[0]);
    for (size_t i = 0; i < thread_count_len; i++) {
        for (size_t j = 0; j < inserts_count_len; j++) {
            char command[100];
            snprintf(command, sizeof(command), "rwlock.exe %llu %llu %llu %lf %lf", number_of_threads[i], number_of_inserts[j], number_of_ops[j], 0.34, 0.34);
            printf("\n");
            system(command);
        }
    }
}

int main(int argc, char** argv) {
    char output_format[10];
    if (argc != 2) {
        fprintf(stderr, "Use the following format:\n %s short/long output\n", argv[0]);
        return EXIT_FAILURE;
    }

    strcpy(output_format, argv[1]);
    if (strcmp(output_format, "short") == 0) {
        run_task_1_short();
        run_task_2_short();
        run_task_3_short();
    }
    else {
        run_task_1_more_text();
        run_task_2_more_text();
        run_task_3_more_text();
    }
    return 0;
}
