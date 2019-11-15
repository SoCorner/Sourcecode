#include "quadrature.h"

quadrature_t* create_quadrature(size_t length)
{
	quadrature_t* quadrature;
	quadrature = malloc(sizeof(quadrature_t));
	quadrature->length = length;
	quadrature->nodes = malloc(sizeof(double) * length);
	quadrature->weights = malloc(sizeof(double) * length);

	if (quadrature == NULL) {
		printf("Error: Not enough memory\n");
		return NULL;
	}
	return quadrature;
}

void free_quadrature(quadrature_t* quadrature)
{
	free(quadrature->nodes);
	free(quadrature->weights);
	free(quadrature);
}

void output_quadrature(quadrature_t* quadrature, char* fileName)
{
	printf("outputing...\n");
	FILE* data;
	data = fopen(fileName, "a");

	if (data == NULL) {
		printf("Error during opening the document!\n");
	}
	for (size_t i = 0; i < quadrature->length; i++) {
		fprintf(data, "%lf %lf\n", quadrature->weights[i], quadrature->nodes[i]);
	}
	fprintf(data, "\n");
	fclose(data);
	printf("Output completed, now you can check your %s.\n", fileName);
}

double trapezoidal(int l, double (*f)(double))
{
	double N_l = pow(2, l) - 1;
	double sum = 0;
	
	for (int i = 2; i <= N_l - 1; i++) {
		sum = sum + f((double)(i / (N_l + 1)));
	}
	sum = 1.5 * f(1 / (N_l + 1)) + 1.5 * f(N_l / (N_l + 1)) + sum;
	return sum;
}
quadrature_t* clenshaw_curtis(int l)
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
		for (int j = 1; j <= nr; j++) {
			temp_sum = temp_sum + ((double)1 / (2 * j - 1)) * sin((double)(2 * j - 1) * temp);
		}
		quadrature->weights[i] = temp_mult * temp_sum;

	}
	return quadrature;
}