#include <stdio.h>
#include "../modules/sampling_methods.h"

int main () {
	array_2d_t* samples;
	const size_t num_samples = 1000;
	const unsigned seed = 42;
	gsl_rng* rng;
	FILE *fp;

	rng = gsl_rng_alloc (gsl_rng_mt19937);
	gsl_rng_set (rng, seed);

	samples = draw_standard_normal_box_muller (rng, num_samples);
	if (samples == NULL) return 0;

	fp = fopen ("samples_box_muller.txt", "w");
	for (size_t i = 0; i < num_samples; ++i) {
		fprintf (fp, "%lf %lf\n", samples->data[i][0], samples->data[i][1]);
	}
	fclose (fp);

	free_array_2d_t (samples);
	gsl_rng_free (rng);
	return 0;
}
