#include <stdio.h>
#include "../modules/sampling_methods.h"

#define NUM_SAMPLES 1000000

int main () {
	gsl_rng* rng;
	FILE *fp;
	const unsigned seed = 42;

	rng = gsl_rng_alloc (gsl_rng_mt19937);
	gsl_rng_set (rng, seed);
	
	fp = fopen ("draw_standard_normal_rv_moro.txt", "w");
	for (size_t i = 0; i < NUM_SAMPLES; ++i) {
		fprintf (fp, "%lf\n", draw_standard_normal_rv (rng));
	}
	fclose (fp);
	gsl_rng_free (rng);
	return 0;
}
