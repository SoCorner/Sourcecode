#include "../modules/sampling_methods.h"

int main ()  {
	gsl_rng* rng;
	FILE *fp;
	const double s_0 = 10.0;
	const double mean = 0.1;
	const double sigma = 0.1;
	const double T = 1.0;
	const double delta_t = 1e-3;	
	array_1d_t* gbm, *wiener;
	double estimated_sigma, estimated_mu;
	const unsigned seed = 42;

	rng = gsl_rng_alloc (gsl_rng_mt19937);
	gsl_rng_set (rng, seed);

	wiener = draw_wiener_process (mean, sigma, delta_t, T, rng);
	if (wiener == NULL) return 0;
	gbm = draw_gbm (s_0, mean, sigma, delta_t, T, wiener);
	if (gbm == NULL) return 0;

	fp = fopen ("gbm_estimate.txt", "w");
	for (size_t i = 0; i < gbm->length; ++i) {
		fprintf (fp, "%lf %lf\n", i * delta_t, gbm->data[i]);
	}
	fclose (fp);

	estimated_sigma = estimate_sigma_gbm (gbm, delta_t);
	printf ("estimated_sigma = %lf\n", estimated_sigma);

	estimated_mu = estimate_mu_gbm (gbm, delta_t, estimated_sigma);
	printf ("estimated_mu = %lf\n", estimated_mu);

	gsl_rng_free (rng);
	free_array_1d_t (gbm);
	free_array_1d_t (wiener);
	return 0;
}
