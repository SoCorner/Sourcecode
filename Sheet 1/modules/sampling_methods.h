#ifndef SAMPLING_METHODS_H
#define SAMPLING_METHODS_H

#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "arrayhelpers.h"

/* Start: preprocessor macros for Moro's algorithm NormalCDF */
#define A0 0.398942270991
#define A1 0.020133760596
#define A2 0.002946756074
#define B1 0.217134277847
#define B2 0.018576112465
#define B3 0.000643163695
#define C0 1.398247031184
#define C1 -0.360040248231
#define C2 0.022719786588
#define D0 1.460954518699
#define D1 -0.305459640162
#define D2 0.038611796258
#define D3 -0.003787400686
/* End: preprocessor macros for Moro's algorithm NormalCDF */

/* Start: preprocessor macros for Moro's algorithm NormalInverseCDF */
#define E0 2.50662823884
#define E1 -18.61500062529
#define E2 41.39119773534
#define E3 -25.44106049637
#define F0 -8.47351093090
#define F1 23.08336743743
#define F2 -21.06224101826
#define F3 3.13082909833
#define G0 0.3374754822726147
#define G1 0.9761690190917186
#define G2 0.1607979714918209
#define G3 0.0276438810333863
#define G4 0.0038405729373609
#define G5 0.0003951896511919
#define G6 0.0000321767881768
#define G7 0.0000002888167364
#define G8 0.0000003960315187
/* End: preprocessor macros for Moro's algorithm NormalInverseCDF */

double draw_uniform_rv_a_b (double a, double b, gsl_rng* random_number_generator);

double rejection_sampling_standard_normal (double a, double b, gsl_rng* random_number_generator);

double NormalCDF (double x);

double NormalInverseCDF (double x);

double draw_standard_normal_rv (gsl_rng* random_number_generator);

array_2d_t* draw_standard_normal_box_muller (gsl_rng* rng, size_t num_samples);

double draw_normal_rv (double mean, double standard_deviation, gsl_rng* rng);

array_1d_t* generate_normal_rv_samples (double mean, double standard_deviation, gsl_rng* rng, size_t num_samples);

double estimate_sigma_naively (array_1d_t* samples, double mean);

double estimate_sigma (array_1d_t* samples, size_t num_samples);

double estimation_error (double given_standard_deviation, array_1d_t* samples, size_t num_samples);

array_1d_t* draw_wiener_process (double my, double sigma, double delta_t, double T, gsl_rng* rng);

array_1d_t* draw_gbm (double s_0, double my, double sigma, double delta_t, double T, array_1d_t* wiener);

double estimate_sigma_gbm (array_1d_t* gbm, double timestep);

double estimate_mu_gbm (array_1d_t* gbm, double timestep, double sigma);

#endif
