#ifndef QUADRATURE_H
#define QUADRATURE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arrayhelpers.h"
#define M_PI 3.1515926

typedef struct quadrature {
	size_t length;
	double* nodes;
	double* weights;
} quadrature_t;

typedef struct mult_quadrature {
	size_t length;
	size_t nodes_d;
	double** nodes;
	double* weights;
} mult_quadrature_t;

//construction
quadrature_t* create_quadrature(size_t length);
mult_quadrature_t* create_mult_quadrature(size_t length, size_t nodes_d);

void free_quadrature(quadrature_t* quadrature);
void free_mult_quadrature(mult_quadrature_t* quadrature);

void output_quadrature(quadrature_t* quadrature, char* fileName);
void output_mult_quadrature(mult_quadrature_t* quadrature, char* fileName);

//implementation 








#endif // !QUADRATURE_H
