// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "matrix_op.h"

//alloc memory for a new matrix
int **alloc_matrix(int n, int m)
{
	int **tmp_mat = (int **)calloc(n, sizeof(int *));
	//check if the alloc was succesfull
	//if failed, free all the memory
	if (!tmp_mat) {
		fprintf(stderr, "calloc failed in alloc_mat\n");
		return NULL;
	}
	//alloc memory for every line inside the mat
	for (int i = 0; i < n; ++i) {
		tmp_mat[i] = (int *)calloc(m, sizeof(int));
		if (!tmp_mat[i]) {
			fprintf(stderr, "calloc failed in alloc_mat\n");
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

//check if memory could be allocated in load funcs
void check_load_alloc(photo_t *ph)
{
	if (is_color(ph->type)) {
		if (!ph->rgb_mat.red) {
			fprintf(stderr, "couldn't load P3 photo\n");
			free_mat(ph->rgb_mat.green, ph->lin);
			free_mat(ph->rgb_mat.blue, ph->lin);
			exit(1);
		}

		if (!ph->rgb_mat.green) {
			fprintf(stderr, "couldn't load P3 photo\n");
			free_mat(ph->rgb_mat.red, ph->lin);
			free_mat(ph->rgb_mat.blue, ph->lin);
			exit(1);
		}

		if (!ph->rgb_mat.blue) {
			fprintf(stderr, "couldn't load P3 photo\n");
			free_mat(ph->rgb_mat.red, ph->lin);
			free_mat(ph->rgb_mat.green, ph->lin);
			exit(1);
		}
	} else {
		if (!ph->photo_mat) {
			fprintf(stderr, "couldn't load P5 photo\n");
			exit(1);
		}
	}
}

void free_photo(photo_t *ph)
{
	if (ph->photo_mat)
		free_mat(ph->photo_mat, ph->lin);
	if (ph->rgb_mat.red) {
		free_mat(ph->rgb_mat.red, ph->lin);
		free_mat(ph->rgb_mat.green, ph->lin);
		free_mat(ph->rgb_mat.blue, ph->lin);
	}
}
