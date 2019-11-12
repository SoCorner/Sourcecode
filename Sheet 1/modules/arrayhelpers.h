#ifndef ARRAYHELPERS_H
#define ARRAYHELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct array_1d {
	size_t length;
	double* data;
} array_1d_t;

typedef struct array_2d {
	size_t num_rows;
	size_t num_cols;
	double** data;
} array_2d_t;


array_1d_t* create_array_1d_t (size_t length);

void free_array_1d_t (array_1d_t* array);

array_2d_t* create_array_2d_t (size_t num_rows, size_t num_cols);

void free_array_2d_t (array_2d_t* array);

void output_array_2d_t(array_2d_t* array, char* fileName);
void output_array_1d_t(array_1d_t* array, char* fileName);

double compute_mean(array_1d_t* array);
double compute_variance(array_1d_t* array);

#endif
