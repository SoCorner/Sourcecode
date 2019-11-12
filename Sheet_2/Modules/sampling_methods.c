#include "sampling_methods.h"
 
/* We assume a < b without any test. */
double draw_uniform_rv_a_b (double a, double b, gsl_rng* random_number_generator) {
	double unif;

	unif = gsl_rng_uniform (random_number_generator);
	unif *= (b - a);
	unif += a;

	return unif;
}

/* density function as a parameter? We assume a < b*/
double rejection_sampling_standard_normal (double a, double b, gsl_rng* random_number_generator) {
	double unif_a_b, unif_0_max;
	const double max_of_gaussian_density = gsl_ran_gaussian_pdf (0.0, 1.0);

	do {
		/* We use a 3*\sigma interval: [-3,3]. Then the integral over the density is approximatly 0.9973. */
		/* Draw a uniformly distributed random variable in [-3,3]. */
		unif_a_b = draw_uniform_rv_a_b (a, b, random_number_generator);

		/* Draw a uniformly distributed random variable in $[0, max_{x\in[a,b]]p(x)$ 
		 * with $p(x) = \frac{1}{\sqrt{2\pi}}$ \exp{-\frac{x^2}{2}}.
		 */
		unif_0_max = draw_uniform_rv_a_b (0.0, max_of_gaussian_density, random_number_generator);
	} while (unif_0_max > gsl_ran_gaussian_pdf (unif_a_b, 1.0));
	
	return unif_a_b;	
}


double NormalCDF(double x) {
	double x2;
	if (x < 0.0) return 1.0 - NormalCDF(-x);
	if (x <= 1.87) {
		x2=x*x;
		return 0.5+x*(A0+(A1+A2*x2)*x2)/(1.0+(B1+(B2+B3*x2)*x2)*x2);
	} else if (x < 6.0) {
		return 1.0-pow((C0+(C1+C2*x)*x)/(D0+(D1+(D2+D3*x)*x)*x), 16.0);
	}
	return 1.0;
}

double NormalInverseCDF(double x) {
	double p = x - 0.5;
	double r;
	if ( fabs(p) < 0.42 ) {
		r = pow(p, 2.);
		return p*(((E3*r+E2)*r+E1)*r+E0)/((((F3*r+F2)*r+F1)*r+F0)*r+1.0);
	} else {
		if (p < 0) r = x;
		else r = 1 - x;
		r = log(-log(r));
		r = G0+r*(G1+r*(G2+r*(G3+r*(G4+r*(G5+r*(G6+r*(G7+r*G8)))))));
		
		if (p < 0) return -r;
		else return r;
	}
}

double draw_standard_normal_rv (gsl_rng* random_number_generator) {
	double uniform_0_1;

	uniform_0_1 = draw_uniform_rv_a_b (0.0, 1.0, random_number_generator);
	
	return NormalInverseCDF (uniform_0_1);
}

array_2d_t* draw_standard_normal_box_muller (gsl_rng* rng, size_t num_samples) {
	array_2d_t* samples;
	double abs, phi;

	samples = create_array_2d_t (num_samples, 2);
	if (samples == NULL) return NULL;

	for (size_t i = 0; i < num_samples; ++i) {
		/* just appy the transformation from the sheet */
		abs = sqrt (-2.0 * log (gsl_rng_uniform(rng)));
		phi = 2.0 * M_PI * gsl_rng_uniform(rng);		

		samples->data[i][0] = abs * cos (phi);
		samples->data[i][1] = abs * sin (phi);
	}
	return samples;
}

/* Mit welcher Methode soll die Realisierung der standardnormalverteilten ZV berechnet werden? (gsl_rng_gaussian, rejection_sampling, inverseCDF) */
double draw_normal_rv (double mean, double standard_deviation, gsl_rng* rng) {
	return mean + standard_deviation * gsl_ran_ugaussian (rng);
}

array_1d_t* generate_normal_rv_samples (double mean, double standard_deviation, gsl_rng* rng, size_t num_samples) {
	array_1d_t* samples;

	samples = create_array_1d_t (num_samples);
	if (samples == NULL) return NULL;

	for (size_t i = 0; i < num_samples; ++i) {
		samples->data[i] = draw_normal_rv (mean, standard_deviation, rng);
	}
	return samples;
}

double estimate_sigma_naively (array_1d_t* samples, double mean) {
	double sum = 0.0;

	for (size_t i = 0; i < samples->length; ++i) {
		sum += (samples->data[i] - mean) * (samples->data[i] - mean);
	}
	sum *= 1.0 / (double)(samples->length - 1);
	
	return sqrt (sum);
}

double estimate_sigma (array_1d_t* samples, size_t num_samples) {
	double alpha = samples->data[0];
	double beta = 0;
	double gamma;

	for (size_t i = 0; i < num_samples; ++i) {
		gamma = samples->data[i] - alpha;
		alpha += gamma / (i + 1);
		beta += gamma * gamma * i / (i + 1);
	}
	return sqrt (beta / ((double)(num_samples) - 1.0));
}

double estimation_error (double given_standard_deviation, array_1d_t* samples, size_t num_samples) {
	double estimated_sigma;

	/* estimate the standard deviation */
	estimated_sigma = estimate_sigma (samples, num_samples);

	return fabs (given_standard_deviation - estimated_sigma);
}

// I just find out we need't to use sigma and my
array_1d_t* draw_wiener_process(double delta_t, double T, gsl_rng* rng) {
	array_1d_t* wiener;
	const size_t num_points = (size_t)(T / delta_t) + 1;
	const double root_delta = sqrt(delta_t);

	wiener = create_array_1d_t(num_points);
	if (wiener == NULL) return NULL;

	wiener->data[0] = 0.0;
	for (size_t i = 1; i < num_points+1; ++i) {
		/* we use that the Wiener increment is distributed with N(0,delt_t) */
		wiener->data[i] = wiener->data[i - 1] + root_delta * gsl_ran_ugaussian(rng);
	}
	return wiener;
}

array_1d_t* draw_gbm (double s_0, double my, double sigma, double delta_t, double T, array_1d_t* wiener) {
	array_1d_t* gbm_discr;
	const size_t num_points = (size_t)(T / delta_t) + 1;
	const double sigma_sq = sigma * sigma;

	gbm_discr = create_array_1d_t (num_points);
	if (gbm_discr == NULL) return NULL;

	gbm_discr->data[0] = s_0;
	for (size_t i = 1; i < num_points; ++i) {
		gbm_discr->data[i] = s_0 * exp (((my - 0.5 * sigma_sq) * delta_t * i) + sigma * wiener->data[i]);
	}
	return gbm_discr;
}

double estimate_sigma_gbm (array_1d_t* gbm, double timestep) {
	double estimated_sigma;
	array_1d_t* log_gbm;

	log_gbm = create_array_1d_t (gbm->length);
	if (log_gbm == NULL) return -1.0;

	for (size_t i = 0; i < gbm->length; ++i) {
		/* Get normally distributed daily return */
		log_gbm->data[i] = log (gbm->data[i + 1] / gbm->data[i]);
	}
	
	estimated_sigma = estimate_sigma (log_gbm, gbm->length);

	free_array_1d_t (log_gbm);
	return estimated_sigma / sqrt (timestep);
}

double estimate_mu_gbm (array_1d_t* gbm, double timestep, double sigma) {
	double estimated_mu = 0.0;
	
	for (size_t i = 0; i < gbm->length; ++i) {
		estimated_mu += log (gbm->data[i + 1] / gbm->data[i]);
	}
	estimated_mu *= 1.0 / (double)(gbm->length);

	return estimated_mu / timestep + 0.5 * sigma * sigma;
}
