#include "quadrature.h"

quadrature_t* create_quadrature(size_t length)
{
	quadrature_t* quadrature = malloc(sizeof(quadrature_t));
	quadrature->length = length;
	quadrature->nodes = malloc(sizeof(double) * length);
	quadrature->weights = malloc(sizeof(double) * length);

	if (quadrature == NULL) {
		printf("Error: Not enough memory\n");
		return NULL;
	}
	return quadrature;
}

mult_quadrature_t* create_mult_quadrature(size_t length, size_t nodes_d)
{
	mult_quadrature_t* mult_quadrature = malloc(sizeof(mult_quadrature_t));
	mult_quadrature->length = length;
	mult_quadrature->nodes_d = nodes_d;
	mult_quadrature->nodes = create_array_2d_t(length, nodes_d)->data;
	mult_quadrature->weights = create_array_1d_t(length)->data;

	if (mult_quadrature == NULL) {
		printf("Error: Not enough memory\n");
		return NULL;
	}
	return mult_quadrature;
}

void free_mult_quadrature(mult_quadrature_t* quadrature)
{
	free(quadrature->nodes);
	free(quadrature->weights);
	free(quadrature);
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
		fprintf(data, "%lf %lf\n", quadrature->nodes[i], quadrature->weights[i]);
	}
	fprintf(data, "\n");
	fclose(data);
	printf("Output completed, now you can check your %s.\n", fileName);
}

void output_mult_quadrature(mult_quadrature_t* quadrature, char* fileName)
{
	FILE* data;
	data = fopen(fileName, "a");

	if (data == NULL) {
		printf("Error during opening the document!\n");
	}
	for (size_t i = 0; i < quadrature->length; i++) {
		fprintf(data, "%f ", quadrature->weights[i]);
		for (size_t j = 0; j < quadrature->nodes_d; j++) {
			fprintf(data, "%f ", quadrature->nodes[i][j]);
		}
		fprintf(data, "\n");
	}
	fprintf(data, "\n");
	fclose(data);
	printf("Output completed, now you can check your %s.\n", fileName);
}

