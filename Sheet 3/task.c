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
		gsl_rng_set(rng, seed+i);
		bm_discr = draw_wiener_process(delta_t, T, rng);
		gbm_discr = draw_gbm(s_0, my, sigma, delta_t, T, bm_discr);
		payoff->data[i] = draw_payoff(K,gbm_discr);
	}
	//free_array_1d_t(gbm_discr);
	//free_array_1d_t(bm_discr);
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
/*
void sheet2_task8(int l)
{
	
	char* fileName = malloc(sizeof(char*) * 255);
	sprintf(fileName, "test8_%i.txt", l);
	quadrature_t* output = clenshaw_curtis(l);
	output_quadrature(output, fileName);


}
*/
void sheet2_task4(int seed)
{

}


void sheet2_task9()
{
	gsl_rng* rng;
	rng = gsl_rng_alloc(gsl_rng_mt19937);
	gsl_rng_set(rng, 42);
	double result = Monte_Carlo_Simu(test_function, 0, 1, 5000, rng);
	//printf("%lf\n", result);
	result = clenshaw_curtis(test_function,10);
	printf("%lf\n", result);
	result = quasi_monte_carlo(test_function, 5000);
	printf("\%lf\n", result);
}

void sheet3_task6()
{
	int num = 10, d = 3;
	double var;
	char* fileName = malloc(sizeof(char*)*255);
	for (int i = 2; i <= d; i++) {
		sprintf(fileName, "Halton_Sequence_dimension%i.txt",i);
		array_2d_t* Halton = Halton_Sequnce(num, i);
		output_array_2d_t(Halton, fileName);
		free_array_2d_t(Halton);
	}
	printf("output finished.\n");
}

void sheet3_task7()
{
	int num = 1000, d = 2, seed = 42;
	char* fileName = malloc(sizeof(char*) * 255);
	gsl_rng* rng;
	rng = gsl_rng_alloc(gsl_rng_mt19937);

	array_2d_t* Halton = Halton_Sequnce(num, d);
	sprintf(fileName, "Halton_Sequence.txt");
	output_array_2d_t(Halton, fileName);

	sprintf(fileName, "uniform.txt");

	array_2d_t* uniform = create_array_2d_t(num, d);
	for (int i = 0; i < num; i++) {
		gsl_rng_set(rng, seed + i);
		uniform->data[i][0] = gsl_ran_flat(rng, 0, 1);
		uniform->data[i][1] = gsl_ran_flat(rng, 0, 1);
	}
	output_array_2d_t(uniform, fileName);
	double sum = 0;
	for (int i = 0; i < num; i++) {
		sum += pow(uniform->data[i][0] - Halton->data[i][0], 2) + pow(uniform->data[i][1] - Halton->data[i][1], 2);
	}
	printf("the distance is %lf\n", (double)(sum / num));
	free_array_2d_t(uniform);
	free_array_2d_t(Halton);
}

void sheet3_task9() {
	char* fileName = malloc(sizeof(char*) * 255);
	int l = 5, d = 2;
	mult_quadrature_t* mult_quadrature = d_fold_tensor(trap_generator, l, d);
	sprintf(fileName, "trapezoida.txt");
	output_mult_quadrature(mult_quadrature, fileName);
	mult_quadrature = d_fold_tensor(gauss_legendre_generator, l, d);
	sprintf(fileName, "gauss_legendre.txt");
	output_mult_quadrature(mult_quadrature, fileName);
	mult_quadrature = d_fold_tensor(clenshaw_curtis_generator, l, d);
	sprintf(fileName, "clenshaw_curtis.txt");
	output_mult_quadrature(mult_quadrature, fileName);
	free_mult_quadrature(mult_quadrature);
}