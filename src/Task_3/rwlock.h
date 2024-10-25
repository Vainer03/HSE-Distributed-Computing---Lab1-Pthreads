#ifndef MY_RWLOCK_H
#define MY_RWLOCK_H
#include <stdint.h>
#include <pthread.h>

typedef struct {
    pthread_mutex_t mutex;      // mutex
    pthread_cond_t read_cond;   // conditional variable for reading threads
    pthread_cond_t write_cond;  // conditional variable for writing threads
    uint64_t read_count;        // the amount of threads reading at the moment
    uint64_t read_waiters;      // the amount of threads waiting for a read block
    uint64_t write_waiters;     // the amount of threads waiting for a write block
    int8_t write_lock;          // flag, that shows if there's a writer
} my_pthread_rwlock_t;

int my_pthread_rwlock_init(my_pthread_rwlock_t *my_rwlock);
int my_pthread_rwlock_destroy(my_pthread_rwlock_t *my_rwlock);
int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *my_rwlock);
int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *my_rwlock);
int my_pthread_rwlock_unlock(my_pthread_rwlock_t *my_rwlock);
#endif