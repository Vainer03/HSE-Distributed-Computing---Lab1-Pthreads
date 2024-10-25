#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <complex.h>
#include <math.h>
#include "timer.h"
#include "../my_rand.h"
#include "mandelbrot_set.h"

uint64_t n_threads;   //number of threads
uint64_t n_points;    //number of points
double_t const x_min = -2.0, y_min = -1.0, x_max = 1.0, y_max = 1.0;
uint64_t points_per_thread;
double start, finish;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#define MAX_ITER 1000
FILE *output;

int is_a_mandelbrot_number(double complex c) {
    double complex z = 0;
    for (uint16_t i = 0; i < MAX_ITER; i++) {
        z = z * z + c;
        if (cabs(z) >= 2.0) {
            return 0;
        }
    }
    return 1;
}

void* mandelbrot_set_routine(void* args) {
    uint32_t seed = time(NULL);
    for (uint64_t i = 0; i < points_per_thread; i++) {
        double_t real = my_drand(&seed) * 3.0;
        double_t imag = my_drand(&seed) * 2.0;
        double complex c = real + imag * I;
        if (is_a_mandelbrot_number(c)) {
            pthread_mutex_lock(&mutex);
            fprintf(output, "%lf,%lf\n", real, imag);
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Use the following format:\n %s n_threads n_points\n", argv[0]);
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    if ((argv[1][0] == '-') || (argv[2][0] == '-') || (argv[1][0] == '0') || (argv[2][0] == '0')) {
        fprintf(stderr, "both n_threads and n_points need to be > 0");
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    n_threads = strtoll(argv[1], NULL, 10);
    n_points = strtoll(argv[2], NULL, 10);

    if (n_threads > n_points) {
        n_threads = n_points;
    }

    pthread_t* thread_handler = malloc(n_threads * sizeof(pthread_t));
    if (!thread_handler) {
        fprintf(stderr, "Couldn't allocate memory for the thread_handler");
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    points_per_thread = n_points/n_threads;

    time_t now;
    time(&now);
    struct tm *tm_info = localtime(&now);
    char filename[32];
    strftime(filename, sizeof(filename), "mandelbrot_%Y%m%d_%H%M%S.csv", tm_info);

    output = fopen(filename, "w");
    if (output == NULL) {
        perror("Failed to open the output file");
        free(thread_handler);
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    fprintf(output, "real,imaginary\n");

    GET_TIME(start);
    for (uint64_t i=0; i < n_threads-1; i++) {
        int err = pthread_create(&thread_handler[i], NULL, mandelbrot_set_routine, (void*)&points_per_thread);
        if (err != 0) {
            perror("Failed to create thread");
            free(thread_handler);
            pthread_mutex_destroy(&mutex);
            return EXIT_FAILURE;
        }
    }
    uint64_t points_in_the_last_thread = points_per_thread + (n_points % n_threads);
    int err = pthread_create(&thread_handler[n_threads-1], NULL, mandelbrot_set_routine, (void*)&points_in_the_last_thread);
    if (err != 0) {
        perror("Failed to create thread");
        free(thread_handler);
        pthread_mutex_destroy(&mutex);
        return EXIT_FAILURE;
    }

    for (uint64_t i = 0; i < n_threads; i++) {
        pthread_join(thread_handler[i], NULL);
    }
    GET_TIME(finish);

    printf("Time taken to calculate: %lf\n", finish - start);
    free(thread_handler);
    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}