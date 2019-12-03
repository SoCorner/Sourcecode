#ifndef TASK_H
#define TASK_H

#include "integration.h"
#include "quadrature.h"
#include<gsl/gsl_rng.h>
#include<gsl/gsl_randist.h>


array_1d_t* sheet2_task_1_2_helper(double sigma, double delta_t, int seed);


void sheet2_task1(int seed);
void sheet2_task2(int seed);
void sheet2_task4(int seed);
void sheet2_task8(int l);
void sheet2_task9();

void sheet3_task6();
void sheet3_task7();
void sheet3_task8();
void sheet3_task9();

#endif // !TASK_H
