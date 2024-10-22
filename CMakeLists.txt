cmake_minimum_required(VERSION 3.27)
project(HSE_DC_Lab1_CLion C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(HSE_DC_Lab1_CLion
        src/main.c
        src/main.h
        src/timer.h
        src/my_rand.c

        src/Task_1/monte_carlo.c
        src/Task_1/monte_carlo.h

        src/Task_2/mandelbrot_set.c
        src/Task_2/mandelbrot_set.h

        src/Task_3/rwlock.c
        src/Task_3/rwlock.h
        src/Task_3/pth_ll_rwl.c)
