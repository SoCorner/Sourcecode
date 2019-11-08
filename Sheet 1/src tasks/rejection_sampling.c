#include <stdio.h>
#include "../modules/sampling_methods.h"

void print_eval_of_standard_normal (size_t number_of_eval) {
	gsl_rng* random_number_generator;
	FILE *fp;
	const unsigned seed = 42;

	random_number_generator = gsl_rng_alloc (gsl_rng_mt19937);
	gsl_rng_set (random_number_generator, seed);

	fp = fopen("Task2_rejection_sampling_standard_normal.txt", "w");

	for (size_t i = 0; i < number_of_eval; ++i) { 
		fprintf(fp, "%lf\n", rejection_sampling_standard_normal (-3.0, 3.0, random_number_generator));
	}	
	fclose (fp);


	fp = fopen ("Task_2_rejection_sampling_too_small interval.txt", "w");
	for (size_t i = 0; i < number_of_eval; ++i) { 
		fprintf(fp, "%lf\n", rejection_sampling_standard_normal (-2.0, 2.0, random_number_generator));
	}
	fclose (fp);
	gsl_rng_free (random_number_generator);
}

int main (int argc, char* argv[]) {
	if (argc > 1) {
		print_eval_of_standard_normal (strtoul (argv[1], NULL, 0));
	}
	else {
		print_eval_of_standard_normal (1000000);
	}
	return 0;
}
