#include "arrayhelpers.h"

array_1d_t* create_array_1d_t (size_t length) {
	array_1d_t* array;

	array = malloc (sizeof (array_1d_t));
	array->length = length;
	array->data = malloc (sizeof (double) * length);
	if (array == NULL) {
		printf ("Error: Not enough memory\n");
		return NULL;
	}
	return array;
}

void free_array_1d_t (array_1d_t* array) {
	free (array->data);
	free (array);
}

array_2d_t* create_array_2d_t (size_t num_rows, size_t num_cols) {
	array_2d_t* array;

	array = malloc (sizeof (array_2d_t));
	array->num_rows = num_rows;
	array->num_cols = num_cols;
	array->data = malloc (sizeof (double*) * num_rows);
	if (array->data != NULL) {
		for (size_t i = 0; i < num_rows; ++i) {
			array->data[i] = malloc (sizeof (double) * num_cols);
			if (array->data[i] == NULL) {
				for (--i; i != 0; --i) {
					free (array->data[i]);
				}
				free (array->data);
				free (array);
				printf ("Error: Not enough memory\n");
				return NULL;
			}
		}
		return array;
	}
	else {
		printf ("Error: Not enough memory\n");
		return NULL;
	}
}

void free_array_2d_t (array_2d_t* array) {
	for (size_t i = 0; i < array->num_rows; ++i) {
		free (array->data[i]);
	}
	free (array->data);
	free (array);
}
