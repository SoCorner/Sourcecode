
#include "arrayhelpers.h"
#include "quadrature.h"
#include "sampling_methods.h"
#include <gsl/gsl_integration.h>
#ifndef INTEGRATION_H
#define INTEGRATION_H

typedef double (*functype)(double);
typedef double (*mult_func)(double, double);
typedef quadrature_t* (*univariate)(int);
//test functions
double test_function(double x);
double mult_test_function(double x, double y);
// monte carlo simulation
double Monte_Carlo_Simu(functype f, int start, int end, int num, gsl_rng* rng);
double quasi_monte_carlo(functype f, int num);
//quadrature generator
quadrature_t* trap_generator(int l);
quadrature_t* clenshaw_curtis_generator(int l);
quadrature_t* gauss_legendre_generator(int l);
//multivariate quadrature generator
mult_quadrature_t* d_fold_tensor(univariate method, int l, int d);
//Halton sequence generator
array_1d_t* van_der_corput(int num, int p);
array_1d_t* Halton_helper(int num, int p);
array_2d_t* Halton_Sequnce(int num, int d);
//computation of integral
double integral_of_univ(functype f,univariate method, int l);
double integral_of_mult(mult_func f,univariate method, int l);
//test for integral
void test_for_univ();
void test_for_mult();

#endif // !INTEGRATION_H
