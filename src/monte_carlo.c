#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include "monte_carlo.h"

uint64_t n_threads;   //number of threads
uint64_t n_cats;    //number of trials where cats have a choice to lie down in a circled area of a square
uint64_t total_cats_in_circle = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//double start, finish;

void* monte_carlo_routine(void* args) {
    uint64_t cats_per_thread = *((uint64_t*)args);
    uint64_t cats_in_circle = 0;

    for (uint64_t cat = 0; cat < cats_per_thread; cat++) {
        double_t x = (double_t)rand() / (double_t)RAND_MAX;
        double_t y = (double_t)rand() / (double_t)RAND_MAX;
        if (x*x + y*y <= 1) {
            cats_in_circle++;
        }
    }

    pthread_mutex_lock(&mutex);
    total_cats_in_circle += cats_in_circle;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Use the following format:\n %s n_threads n_cats\n", argv[0]);
        return EXIT_FAILURE;
    }

    if ((argv[1][0] == '-') || (argv[2][0] == '-') || (argv[1][0] == '0') || (argv[2][0] == '0')) {
        fprintf(stderr, "both n_threads and n_cats need to be > 0");
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    n_threads = strtoll(argv[1], NULL, 10);
    n_cats = strtoll(argv[2], NULL, 10);
    pthread_t* thread_handler = malloc(n_threads * sizeof(pthread_t));
    uint64_t cats_per_thread = n_cats/n_threads;

    for (uint64_t i=0; i < n_threads; i++) {
        int err = pthread_create(&thread_handler[i], NULL, monte_carlo_routine, (void*)&cats_per_thread);
        if (err != 0) {
            perror("Failed to create thread");
            return EXIT_FAILURE;
        }
    }

    for (uint64_t i = 0; i < n_threads; i++) {
        pthread_join(thread_handler[i], NULL);
    }

    double pi = 4.0 * total_cats_in_circle/n_cats;
    printf("Estimated value of pi: %lf\n", pi);

    free(thread_handler);
    pthread_mutex_destroy(&mutex);
    return EXIT_SUCCESS;
}