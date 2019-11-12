#include "task.h"


array_1d_t* sheet2_task_1_2_helper(double sigma, double delta_t, int seed)
{
	gsl_rng* rng;
	rng = gsl_rng_alloc(gsl_rng_mt19937);

	double K = 10, T = 2;
	double s_0 = 10, my = 0.1;

	const size_t num_points = 1000;
	array_1d_t* payoff = create_array_1d_t(num_points);
	array_1d_t* gbm_discr, * bm_discr;

	for (size_t i = 0; i < num_points; i++) {
		gsl_rng_set(rng, seed + i);
		bm_discr = draw_wiener_process(delta_t, T, rng);
		gbm_discr = draw_gbm(s_0, my, sigma, delta_t, T, bm_discr);
		payoff->data[i] = draw_payoff(K, T, delta_t, gbm_discr);
	}
	free_array_1d_t(gbm_discr);
	free_array_1d_t(bm_discr);
	return payoff;
}

void sheet2_task1(int seed) {
	char* file_task1 = "task1.txt";
	double sigma[5] = { 0,0.2,0.4,0.6,0.8 };
	double delta_t = 0.2;

	array_1d_t* payoff;
	array_2d_t* output_task1 = create_array_2d_t(5, 2);

	for (size_t i = 0; i < 5; i++) {
		output_task1->data[i][0] = sigma[i];
		payoff = sheet2_task_1_2_helper(sigma[i], delta_t, seed);
		output_task1->data[i][1] = compute_mean(payoff);
	}
	free_array_1d_t(payoff);
	output_array_2d_t(output_task1, file_task1);
}

void sheet2_task2(int seed) {
	char* file_task2 = "task2.txt";
	array_2d_t* output_task2 = create_array_2d_t(4, 3);
	double sigma= 0.2;
	double delta_t[4] = { 0.2,0.4,1.0,2.0 };
	array_1d_t* payoff;
	for (size_t i = 0; i < 4; i++) {
		output_task2->data[i][0] = delta_t[i];
		payoff = sheet2_task_1_2_helper(sigma, delta_t[i], seed);
		output_task2->data[i][1] = compute_mean(payoff);
		output_task2->data[i][2] = compute_variance(payoff);
	}
	free_array_1d_t(payoff);
	output_array_2d_t(output_task2, file_task2);
}