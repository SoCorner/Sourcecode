#include "../modules/sampling_methods.h"

int main () {
	const size_t num_samples = 1000;
	const unsigned seed = 42;
	gsl_rng* rng;
	array_1d_t* samples;
	double estimated_sigma, estimated_sigma_nav, estimated_mean;

	rng = gsl_rng_alloc (gsl_rng_mt19937);
	gsl_rng_set (rng, seed);

	samples = generate_normal_rv_samples (0.5, 0.1, rng, num_samples);
	if (samples == NULL) return 0;

	/* estimate the mean */
	estimated_mean = 0.0;
	for (size_t i = 0; i < samples->length; ++i) {
		estimated_mean += samples->data[i];
	}
	estimated_mean *= 1.0 / (double)(samples->length);

	estimated_sigma_nav = estimate_sigma_naively (samples, estimated_mean);
	estimated_sigma = estimate_sigma (samples, samples->length);

	printf ("estimated_sigma_nav = %lf\n", estimated_sigma_nav);
	printf ("estimated_sigma = %lf\n", estimated_sigma);

	gsl_rng_free (rng);
	free_array_1d_t (samples);
	return 0;
}
