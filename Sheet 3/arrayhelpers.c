#include "arrayhelpers.h"

array_1d_t* create_array_1d_t(size_t length) {
	array_1d_t* array;

	array = malloc(sizeof(array_1d_t));
	array->length = length;
	array->data = malloc(sizeof(double) * length);
	if (array == NULL) {
		printf("Error: Not enough memory\n");
		return NULL;
	}
	return array;
}

void free_array_1d_t(array_1d_t* array) {
	free(array->data);
	free(array);
}

array_2d_t* create_array_2d_t(size_t num_rows, size_t num_cols) {
	array_2d_t* array;

	array = malloc(sizeof(array_2d_t));
	array->num_rows = num_rows;
	array->num_cols = num_cols;
	array->data = malloc(sizeof(double*) * num_rows);
	if (array->data != NULL) {
		for (size_t i = 0; i < num_rows; ++i) {
			array->data[i] = malloc(sizeof(double) * num_cols);
			if (array->data[i] == NULL) {
				for (--i; i != 0; --i) {
					free(array->data[i]);
				}
				free(array->data);
				free(array);
				printf("Error: Not enough memory\n");
				return NULL;
			}
		}
		return array;
	}
	else {
		printf("Error: Not enough memory\n");
		return NULL;
	}
}

void free_array_2d_t(array_2d_t* array) {
	for (size_t i = 0; i < array->num_rows; ++i) {
		free(array->data[i]);
	}
	free(array->data);
	free(array);
}

void output_array_1d_t(array_1d_t* array, char* fileName)
{
	printf("outputing...\n");
	FILE* data;
	data = fopen(fileName, "a");
	if (data == NULL) {
		printf("Error during opening the document!\n");
	}

	for (size_t i = 0; i < array->length; i++) {
		fprintf(data, "%lf\n ", array->data[i]);
	}
	fclose(data);

	printf("Output completed, now you can check your %s.\n", fileName);
}
void output_array_2d_t(array_2d_t* array, char* fileName)
{
	//printf("outputing...\n");
	FILE* data;
	data = fopen(fileName, "a");

	if (data == NULL) {
		printf("Error during opening the document!\n");
	}

	for (size_t i = 0; i < array->num_rows; i++) {
		for (size_t j = 0; j < array->num_cols; j++) {
			fprintf(data, "%lf ", array->data[i][j]);
		}
		fprintf(data, "\n");
	}
	fclose(data);

	//printf("Output completed, now you can check your %s.\n", fileName);
}

double compute_mean(array_1d_t* array)
{
	double sum = 0, mean;
	for (size_t i = 0; i < array->length; i++) {
		sum = sum + array->data[i];
	}
	mean = sum / array->length;
	return mean;
}

double compute_variance(array_1d_t* array)
{	
	double temp = 0, sum = 0;
	double mean = compute_mean(array); 
	for (size_t i = 0; i < array->length; i++) {
		temp = pow(array->data[i] - mean, 2);
		sum = sum + temp;
	}
	return sum / array->length;
}

double compute_sum(array_1d_t* array)
{
	double sum = 0;
	for (size_t i = 0; i < array->length; i++) {
		sum = sum + array->data[i];
	}
	return sum;
}
array_2d_t* trans(array_2d_t* input)
{
	int num_cols = input->num_cols, num_rows = input->num_rows;
	array_2d_t* trans = create_array_2d_t(num_cols, num_rows);
	for (int i = 0; i < num_cols; i++) {
		for (int j = 0; j < num_rows; j++) {
			trans->data[i][j] = input->data[j][i];
		}
	}
	return trans;
}


array_1d_t* prim_generator(int num) {
	array_1d_t* prim = create_array_1d_t(num);
	int  i, p, count, flag;
	p = 2;
	i = 0;
	while (i < num)
	{
		flag = 1;
		for (count = 2; count <= p - 1; count++)
		{
			if (p % count == 0)  //Will be true if p is not prime
			{
				flag = 0;
				break;      //Loop will terminate if p is not prime
			}
		}
		if (flag == 1)
		{
			prim->data[i] = p;
			i++;
		}
		p++;
	}
	return prim;
}
