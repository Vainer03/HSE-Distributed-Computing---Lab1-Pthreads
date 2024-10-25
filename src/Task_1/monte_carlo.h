#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include "timer.h"
#include "../my_rand.h"

void* monte_carlo_routine(void* args);
int main(int argc, char** argv);
