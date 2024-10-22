cmake_minimum_required(VERSION 3.27)
project(HSE_DC_Lab1_CLion C)

set(CMAKE_C_STANDARD 11)

#include_directories(src)

add_executable(HSE_DC_Lab1_CLion
        src/monte_carlo.c
        src/monte_carlo.h)
#        src/mandelbrot_set.c
#        src/mandelbrot_set.h)
