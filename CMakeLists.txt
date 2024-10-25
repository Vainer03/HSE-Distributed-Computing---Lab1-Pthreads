cmake_minimum_required(VERSION 3.27)
project(HSE_DC_Lab1_CLion C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(main
        src/main.c
        src/timer.h
        src/my_rand.c
        src/my_rand.h)

add_executable(monte_carlo
        src/my_rand.c
        src/my_rand.h
        src/Task_1/monte_carlo.c
        src/Task_1/monte_carlo.h)

add_executable(mandelbrot_set
        src/my_rand.c
        src/my_rand.h
        src/Task_2/mandelbrot_set.c
        src/Task_2/mandelbrot_set.h)

#add_executable(my_rwlock
#        src/Task_3/rwlock.c
#        src/Task_3/rwlock.h)
#
#add_executable(rwlock
#        src/my_rand.c
#        src/my_rand.h
#        src/Task_3/pth_ll_rwl.c)
