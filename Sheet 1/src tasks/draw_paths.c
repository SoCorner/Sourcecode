#include "../modules/sampling_methods.h"

int main () {
	FILE *fp;
	gsl_rng* rng;
	array_1d_t* wiener[6];
	array_1d_t* gbm[6];
	const double delta_t[2] = {0.5, 0.01};
	const double mean = 0.1;
	const double standard_deviation = 0.1;
	const double T = 2.0;
	const double s_0 = 10.0;
	const unsigned seed = 42;

	rng = gsl_rng_alloc (gsl_rng_mt19937);
	gsl_rng_set (rng, seed);

	/* generate paths for different delta_t's */
	for (size_t i = 0; i < 3; ++i) {
		wiener[i] = draw_wiener_process (mean, standard_deviation, delta_t[0], T, rng);
		gbm[i] = draw_gbm (s_0, mean, standard_deviation, delta_t[0], T, wiener[i]);
	}
	/* for different time steps we have different realiztion since number of functions calls (of single random var simulation) varies */
	gsl_rng_set (rng, seed);
	for (size_t i = 3; i < 6; ++i) {
		wiener[i] = draw_wiener_process (mean, standard_deviation, delta_t[1], T, rng);
		gbm[i] = draw_gbm (s_0, mean, standard_deviation, delta_t[1], T, wiener[i]);
	}

	/* write to file */
	/* large steps (0.5) */
	fp = fopen ("wiener_process_large_steps.txt", "w");
	for (size_t i = 0; i < (size_t)(T / delta_t[0]) + 1; ++i) {
		fprintf (fp, "%lf ", i * delta_t[0]);
		for (size_t j = 0; j < 3; ++j) {
			fprintf (fp, "%lf ", wiener[j]->data[i]);
		}
		fprintf (fp, "\n");
	}
	fclose (fp);

	fp = fopen ("gbm_large_steps.txt", "w");
	for (size_t i = 0; i < (size_t)(T / delta_t[0]) + 1; ++i) {
		fprintf (fp, "%lf ", i * delta_t[0]);
		for (size_t j = 0; j < 3; ++j) {
			fprintf (fp, "%lf ", gbm[j]->data[i]);
		}
		fprintf (fp, "\n");
	}
	fclose (fp);

	/* smaller steps (0.01) */
	fp = fopen ("wiener_process_smaller_steps.txt", "w");
	for (size_t i = 0; i < (size_t)(T / delta_t[1]) + 1; ++i) {
		fprintf (fp, "%lf ", i * delta_t[1]);
		for (size_t j = 3; j < 6; ++j) {
			fprintf (fp, "%lf ", wiener[j]->data[i]);
		}
		fprintf (fp, "\n");
	}
	fclose (fp);

	fp = fopen ("gbm_smaller_steps.txt", "w");
	for (size_t i = 0; i < (size_t)(T / delta_t[1]) + 1; ++i) {
		fprintf (fp, "%lf ", i * delta_t[1]);
		for (size_t j = 3; j < 6; ++j) {
			fprintf (fp, "%lf ", gbm[j]->data[i]);
		}
		fprintf (fp, "\n");
	}
	fclose (fp);

	for (size_t i = 0; i < 6; ++i) {
		free_array_1d_t (wiener[i]);
		free_array_1d_t (gbm[i]);
	}
	gsl_rng_free (rng);
	return 0;
}
