//Dan-Dominic Staicu 311CA 2023
#include "matrix_op.h"

//alloc memory for a new matrix
int **alloc_matrix(int n, int m)
{
	int **tmp_mat = (int **)malloc(n * sizeof(int *));
	//check if the alloc was succesfull
	//if failed, free all the memory
	if (!tmp_mat) {
		fprintf(stderr, "malloc failed in alloc_mat\n");
		return NULL;
	}
	//alloc memory for every line inside the mat
	for (int i = 0; i < n; ++i) {
		tmp_mat[i] = (int *)malloc(m * sizeof(int));
		if (!tmp_mat[i]) {
			fprintf(stderr, "malloc failed in alloc_mat\n");
			free_mat(tmp_mat, i);
			return NULL;
		}
	}
	return tmp_mat;
}


//free memory of a mat
void free_mat(int **mat, int n)
{
	//every single line
	for (int i = 0; i < n; ++i)
		free(mat[i]);
	//and initial pointer
	free(mat);
}
