#ifndef QUADRATURE_H
#define QUADRATURE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265359

typedef struct quadrature {
	size_t length;
	double* nodes;
	double* weights;
} quadrature_t;

//construction
quadrature_t* create_quadrature(size_t length);
void free_quadrature(quadrature_t* quadrature);

//implementation 

quadrature_t* clenshaw_curtis(int l);
double trapezoidal(int l, double (*f)(double));






#endif // !QUADRATURE_H
