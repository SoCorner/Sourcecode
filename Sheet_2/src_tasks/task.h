#ifndef TASK_H
#define TASK_H

#include "arrayhelpers.h"
#include "sampling_methods.h"
#include<gsl/gsl_rng.h>
#include<gsl/gsl_randist.h>


array_1d_t* sheet2_task_1_2_helper(double sigma, double delta_t, int seed);
void sheet2_task1(int seed);
void sheet2_task2(int seed);

#endif // !TASK_H
