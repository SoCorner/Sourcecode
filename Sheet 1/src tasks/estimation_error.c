#include "../modules/sampling_methods.h"

int main () {
	FILE *fp;
	gsl_rng* rng;
	array_1d_t* normal_samples[3];
	const double mean = 1.5;
	const double standard_deviation[3] = {0.1, 1.0, 10.0};
	const size_t max_num_samples = 10e6;
	const unsigned seed = 42;

	rng = gsl_rng_alloc (gsl_rng_mt19937);
	gsl_rng_set (rng, seed);

	/* generate the samples */
	for (size_t  i = 0; i < 3; ++i) {
		normal_samples[i] = generate_normal_rv_samples (mean, standard_deviation[i], rng, max_num_samples);
		if (normal_samples[i] == NULL) return 0;
	}
	printf ("Samples were generated\n");

	for (size_t i = 0; i < 3; ++i) {
		switch (i) {
			case 0: fp = fopen ("estimate_sigma_convergence_plot_sigma_1.txt", "w"); printf("Start sigma_1\n"); break;
			case 1: fp = fopen ("estimate_sigma_convergence_plot_sigma_2.txt", "w"); printf("Start sigma_2\n"); break;
			case 2: fp = fopen ("estimate_sigma_convergence_plot_sigma_3.txt", "w"); printf("Start sigma_3\n"); break;
		}
		for (size_t n = 10; n <= max_num_samples; n *= 10) {
			fprintf (fp, "%lu %lf\n", n / 2, estimation_error (standard_deviation[i], normal_samples[i], n / 2));
			fprintf (fp, "%lu %lf\n", n, estimation_error (standard_deviation[i], normal_samples[i], n));
			if (n < max_num_samples) fprintf (fp, "%lu %lf\n", 2 * n, estimation_error (standard_deviation[i], normal_samples[i], 2 * n));
		}
		fclose (fp);
	}
	for (size_t i = 0; i < 3; ++i) {
		free_array_1d_t (normal_samples[i]);
	}
	gsl_rng_free (rng);
	return 0;
}
