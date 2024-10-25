#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#include "rwlock.h"
#include "../timer.h"
#include "../my_rand.h"
#include "pth_ll_rwl.c"

typedef struct {
    pthread_mutex_t mutex;      // mutex
    pthread_cond_t read_cond;   // conditional variable for reading threads
    pthread_cond_t write_cond;  // conditional variable for writing threads
    uint64_t read_count;        // the amount of threads reading at the moment
    uint64_t read_waiters;      // the amount of threads waiting for a read block
    uint64_t write_waiters;     // the amount of threads waiting for a write block
    int8_t write_lock;          // flag, that shows if there's a writer
} my_pthread_rwlock_t;

int my_pthread_rwlock_init(my_pthread_rwlock_t *my_rwlock) {
    my_rwlock->read_count = 0;
    my_rwlock->read_waiters = 0;
    my_rwlock->write_waiters = 0;
    my_rwlock->write_lock = 0;

    int error_code = 0;

    error_code = pthread_mutex_init(&my_rwlock->mutex, NULL);
    if (error_code != 0) {
        return error_code;
    }

    error_code = pthread_cond_init(&my_rwlock->read_cond, NULL);
    if (error_code != 0) {
        pthread_mutex_destroy(&my_rwlock->mutex);
        return error_code;
    }

    error_code = pthread_cond_init(&my_rwlock->write_cond, NULL);
    if (error_code != 0) {
        pthread_cond_destroy(&my_rwlock->read_cond);
        pthread_mutex_destroy(&my_rwlock->mutex);
        return error_code;
    }

    return error_code;
}

int my_pthread_rwlock_destroy(my_pthread_rwlock_t *my_rwlock) {
    int error_code = 0;

    error_code = pthread_mutex_destroy(&my_rwlock->mutex);
    if (error_code != 0) {
        return error_code;
    }

    error_code = pthread_cond_destroy(&my_rwlock->read_cond);
    if (error_code != 0) {
        return error_code;
    }

    error_code = pthread_cond_destroy(&my_rwlock->write_cond);
    if (error_code != 0) {
        return error_code;
    }

    return error_code;
}

int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *my_rwlock) {
    pthread_mutex_lock(&my_rwlock->mutex);
    while (my_rwlock->write_waiters > 0 || my_rwlock->write_lock ) {
        my_rwlock->read_waiters++;
        pthread_cond_wait(&my_rwlock->read_cond, &my_rwlock->mutex);
        my_rwlock->read_waiters--;
    }
    my_rwlock->read_count++;
    pthread_mutex_unlock(&my_rwlock->mutex);
    return 0;
}

int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *my_rwlock) {
    pthread_mutex_lock(&my_rwlock->mutex);
    while (my_rwlock->read_count > 0 || my_rwlock->write_lock) {
        my_rwlock->write_waiters++;
        pthread_cond_wait(&my_rwlock->write_cond, &my_rwlock->mutex);
        my_rwlock->write_waiters--;
    }
    my_rwlock->write_lock = 1;
    pthread_mutex_unlock(&my_rwlock->mutex);
    return 0;
}

int my_pthread_rwlock_unlock(my_pthread_rwlock_t *my_rwlock) {
    pthread_mutex_lock(&my_rwlock->mutex);
    my_rwlock->read_count--;
    if (my_rwlock->read_count == 0 && my_rwlock->write_waiters > 0) {
        pthread_cond_signal(&my_rwlock->write_cond);
    }
    pthread_mutex_unlock(&my_rwlock->mutex);
    return 0;
}
