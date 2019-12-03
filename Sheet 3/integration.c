#include "integration.h"

//2.29744
double test_function(double x)
{
	double temp = 1 + exp(x / 2);
	return temp;
}

//2.68336 
double mult_test_function(double x, double y)
{
	double temp = 1 + exp((x + y) / 2);
	return temp;
}

double Monte_Carlo_Simu(functype f, int start, int end, int num, gsl_rng* rng)
{
	array_1d_t* contains = create_array_1d_t(num);
	double temp, result;
	for (int i = 0; i < num; i++) {
		temp = draw_uniform_rv_a_b(start,end,rng);
		contains->data[i] = f(temp);
	}
	result = compute_mean(contains);
	free_array_1d_t(contains);
	return result;
}
quadrature_t* trap_generator(int l)
{
	size_t N_l = pow(2, l) - 1;
	quadrature_t* quadrature = create_quadrature(N_l);
	int N_l_plus_1 = N_l + 1;
	quadrature->nodes[0] = 1 /(double)( N_l_plus_1);
	quadrature->weights[0] = 1.5 * (1 / (double)(N_l_plus_1));
	for (int i = 1; i < N_l - 1; i++) {
		quadrature->nodes[i] = (double)(i) / (double)(N_l_plus_1);
		quadrature->weights[i] = 1 / (double)(N_l_plus_1);
	}
	quadrature->nodes[N_l - 1] = (double)(N_l) / (double)(N_l_plus_1);
	quadrature->weights[N_l-1] = 1.5 * (1 / (double)(N_l_plus_1));
	return quadrature;
}
double trapezoidal(int l, functype f)
{
	double N_l = pow(2, l) - 1;
	double sum = 0;

	for (int i = 2; i <= N_l - 1; i++) {
		sum = sum + f((double)(i / (N_l + 1)));
	}
	sum = 1.5 * f(1 / (N_l + 1)) + 1.5 * f(N_l / (N_l + 1)) + sum;
	return sum;
}
quadrature_t* clenshaw_curtis_generator(int l)
{
	size_t N_l = pow(2, l) - 1;
	quadrature_t* quadrature = create_quadrature(N_l);
	int N_l_plus_1 = N_l + 1;
	int nr = N_l_plus_1 / 2;
	double temp_mult, temp_sum = 0;
	double temp;
	for (size_t i = 0; i < N_l; i++) {
		temp = (i + 1) * M_PI / N_l_plus_1;
		quadrature->nodes[i] = 0.5 * (1 - cos(temp));
		temp_mult = (double)2 / N_l_plus_1 * sin(temp);
		temp_sum = 0;
		for (int j = 1; j <= nr; j++) {
			temp_sum = temp_sum + ((double)1 / (2 * j - 1)) * sin((double)(2 * j - 1) * temp);
		}
		quadrature->weights[i] = temp_mult * temp_sum;

	}
	return quadrature;
}

double clenshaw_curtis(functype f, int l)
{
	quadrature_t* generator = clenshaw_curtis_generator(l);
	double result = 0;
	size_t num = pow(2, l) - 1;
	for (size_t i = 0; i < num; i++) {
		result += f(generator->nodes[i]) * generator->weights[i];
	}
	return result;
}

quadrature_t* gauss_legendre_generator(int l)
{
	const size_t N_l = pow(2, l) - 1;
	const double start = 0;
	const double end = 1;

	// setting for gsl_integration_fixed_alloc function,
	//alpha and beta will be ignored, if we apply legendre(accroding to gsl reference)
	const double alpah = 0;
	const double beta = 0;
	quadrature_t* quadrature = create_quadrature(N_l);
	gsl_integration_fixed_workspace* workspace =
		gsl_integration_fixed_alloc(gsl_integration_fixed_legendre, N_l, start, end, alpah, beta);
	quadrature->nodes = workspace->x;
	quadrature->weights = workspace->weights;

	//gsl_integration_fixed_free(workspace);
	return quadrature;
}
array_1d_t* van_der_corput(int num, int p)
{
	double eps = 1e-12;
	double z, v;
	array_1d_t* corput = create_array_1d_t(num);
	corput->data[0] = 0;
	for (int i = 1; i < num; i++) {
		z = 1 - corput->data[i - 1];
		v = (double)1 / p;
		while (z < v + eps) {
			v = (double)v / p;
		}
		corput->data[i] = corput->data[i - 1] + (double)(p + 1) * v - 1;
	}
	return corput;
}

array_1d_t* Halton_helper(int num, int p)
{
	array_1d_t* temp_corput = van_der_corput(num + 1, p);
	array_1d_t* temp = create_array_1d_t(num);
	for (int i = 0; i < num; i++) {
		temp->data[i] = temp_corput->data[i + 1];;
	}
	free_array_1d_t(temp_corput);
	return temp;
}

array_2d_t* Halton_Sequnce(int num, int d)
{
	array_2d_t* temp = create_array_2d_t(d, num);
	array_1d_t* prim = prim_generator(d);
	for (int i = 0; i < d; i++) {
		temp->data[i] = Halton_helper(num, prim->data[i])->data;
	}
	array_2d_t* Halton = trans(temp);
	free_array_2d_t(temp);
	free_array_1d_t(prim);
	return Halton;
}

double quasi_monte_carlo(functype f, int num)
{
	double result = 0;
	array_1d_t* corput = van_der_corput(num, 7);
	for (int i = 0; i < num; i++) {
		result = result + f(corput->data[i]);
	}
	return (double)(result / num);
}

mult_quadrature_t* d_fold_tensor(univariate method, int l, int d)
{
	int N_l = pow(2, l) - 1;
	int length = pow(N_l, d);
	mult_quadrature_t* tensor = create_mult_quadrature(length, d);
	quadrature_t* quadrature = method(l);
	array_1d_t* k = create_array_1d_t(d);
	for (int i = 0; i < d; i++) {
		k->data[i] = 0;
	}
	int count = 0;
	while (1 == 1) {
		tensor->weights[count] = 1;
		for (int dim = 0; dim < d; dim++) {
			tensor->nodes[count][dim] = quadrature->nodes[(int)(k->data[dim])];
			tensor->weights[count] *= quadrature->weights[(int)(k->data[dim])];
		}
		count++;
		for (int j = 0; j < d; j++) {
			k->data[j] += 1;
			if (k->data[j] >= N_l) {
				if (j == d-1) {
					free_quadrature(quadrature);
					return tensor;
				}
				k->data[j] = 0;
			}
			else {
				break;
			}
		}
	}
}

double integral_of_mult(mult_func mult_test, univariate method, int l)
{
	double sum = 0;
	mult_quadrature_t* tensor = d_fold_tensor(method, l, 2);
	for (int i = 0; i < tensor->length; i++) {
		sum += tensor->weights[i] * mult_test(tensor->nodes[i][0], tensor->nodes[i][1]);
	}
	free_mult_quadrature(tensor);
	return sum;
}

double integral_of_univ(functype test_func, univariate method, int l)
{
	double sum = 0;
	quadrature_t* quadrature = method(l);
	for (int i = 0; i < quadrature->length; i++) {
		sum += quadrature->weights[i] * test_func(quadrature->nodes[i]);
	}
	free_quadrature(quadrature);
	return sum;
}

void test_for_univ()
{
	int l = 10;
	double intgr = 0;
	printf("the integral should be 2.29744.\n");
	intgr = integral_of_univ(test_function, trap_generator, l);
	printf("integral based on trapezoidal is %f with level %i.\n", intgr, l);
	intgr = integral_of_univ(test_function, clenshaw_curtis_generator, l);
	printf("integral based on clenshaw curtis is %f with level %i.\n", intgr, l);
	intgr = integral_of_univ(test_function, gauss_legendre_generator, l);
	printf("integral based on gauss legendre is %f with level %i.\n", intgr, l);

}

void test_for_mult()
{
	int l = 10;

	printf("the integral should be 2.68336.\n");
	double intgr = integral_of_mult(mult_test_function, trap_generator, l);
	printf("integral based on trapezoidal is %f with level %i.\n", intgr, l);
	intgr = integral_of_mult(mult_test_function, clenshaw_curtis_generator, l);
	printf("integral based on clenshaw curtis is %f with level %i.\n", intgr, l);
	intgr = integral_of_mult(mult_test_function, gauss_legendre_generator, l);
	printf("integral based on gauss legendre is %f with level %i.\n", intgr, l);

}