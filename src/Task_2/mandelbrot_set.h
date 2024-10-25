#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <complex.h>
#include <math.h>
#include "timer.h"
#include "../my_rand.h"

int is_a_mandelbrot_number(double complex c);
void* mandelbrot_set_routine(void* args);
int main(int argc, char** argv);