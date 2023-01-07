// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "apply_funcs.h"

//main call for apply command in order to validate input and call the right
//effect fucntion
void apply(photo_t *ph)
{
	//try to read the effect name
	char kernel_type[KERNEL_LENGTH];
	fgets(kernel_type, KERNEL_LENGTH, stdin);

	//check if any image was loaded
	if (check_load(ph)) {
		error_no_load();
		return;
	}

	//check if any parameter can be read
	if (strcmp(kernel_type, "\n") == 0) {
		error_invalid();
		return;
	}

	//remove the space from before the effect and \n at the end of the effect
	for (int i = 1; kernel_type[i]; ++i)
		kernel_type[i - 1] = kernel_type[i];
	kernel_type[strlen(kernel_type) - 2] = '\0';

	//check if loaded photo is color
	if (!is_color(ph->type)) {
		error_charlie();
		return;
	}

	//check which APPLY effect was loaded
	switch (hash_apply(kernel_type)) {
	case 0:
		edge(ph);
		break;
	case 1:
		sharpen(ph);
		break;
	case 2:
		box_blur(ph);
		break;
	case 3:
		gaussian_blur(ph);
		break;
	default:
		//in case the parameter is incorect
		error_apply_parameter();
		return;
	}

	succes_apply(kernel_type);
}

void edge(photo_t *ph)
{
	int divide_coef = 1;

	int edge_k[KER_MAT_DIM][KER_MAT_DIM] = {
	{-1, -1, -1},
	{-1, 8, -1},
	{-1, -1, -1}
	};

	//apply kernel matrix on every chanel
	kern(edge_k, ph->rgb_mat.red, ph, divide_coef);
	kern(edge_k, ph->rgb_mat.green, ph, divide_coef);
	kern(edge_k, ph->rgb_mat.blue, ph, divide_coef);
}

void sharpen(photo_t *ph)
{
	int divide_coef = 1;

	int sharpen_k[KER_MAT_DIM][KER_MAT_DIM] = {
	{0, -1, 0},
	{-1, 5, -1},
	{0, -1, 0}
	};

	//apply kernel matrix on every chanel
	kern(sharpen_k, ph->rgb_mat.red, ph, divide_coef);
	kern(sharpen_k, ph->rgb_mat.green, ph, divide_coef);
	kern(sharpen_k, ph->rgb_mat.blue, ph, divide_coef);
}

void box_blur(photo_t *ph)
{
	int divide_coef = 9;

	int box_blur_k[KER_MAT_DIM][KER_MAT_DIM] = {
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1}
	};

	//apply kernel matrix on every chanel
	kern(box_blur_k, ph->rgb_mat.red, ph, divide_coef);
	kern(box_blur_k, ph->rgb_mat.green, ph, divide_coef);
	kern(box_blur_k, ph->rgb_mat.blue, ph, divide_coef);
}

void gaussian_blur(photo_t *ph)
{
	int divide_coef = 16;

	int gaussian_blur_k[KER_MAT_DIM][KER_MAT_DIM] = {
	{1, 2, 1},
	{2, 4, 2},
	{1, 2, 1}
	};

	//apply kernel matrix on every chanel
	kern(gaussian_blur_k, ph->rgb_mat.red, ph, divide_coef);
	kern(gaussian_blur_k, ph->rgb_mat.green, ph, divide_coef);
	kern(gaussian_blur_k, ph->rgb_mat.blue, ph, divide_coef);
}

//overwrites the main photo with the result of appling kernel
//over every color channel
void kern(int kernel[][3], int **color_ch, photo_t *ph, int coef)
{
	//calculate nr of lines and cols inside the selection
	int sel_lin = ph->bot.x - ph->top.x + 1;
	int sel_col = ph->bot.y - ph->top.y + 1;

	//alloc new mat
	//call func to create new mat by maths
	int **effect = apply_kern(ph, color_ch, kernel, sel_lin, sel_col, coef);

	//overwrite ph
	int ef_i = 0;
	int ef_j = 0;
	for (int i = ph->top.x; i <= ph->bot.x; ++i)
		for (int j = ph->top.y; j <= ph->bot.y; ++j) {
			color_ch[i][j] = effect[ef_i][ef_j];

			//step to the next cell
			++ef_j;
			if (ef_j >= sel_col) {
				ef_j = 0;
				++ef_i;
			}
		}

	//free the new mat
	free_mat(effect, sel_lin);
}

//alloc new memory and apply the kernel over the selected zone
//in order to return as a matrix
int **apply_kern(photo_t *ph, int **ch, int ker[][3],
				 int lin, int col, int coef)
{
	int **result = alloc_matrix(lin, col);

	int res_i = 0;
	int res_j = 0;
	for (int i = ph->top.x; i <= ph->bot.x; ++i) {
		for (int j = ph->top.y; j <= ph->bot.y; ++j) {
			int pix_sum = 0;

			//if the current pixel has neighbors
			if (i != 0 && i != ph->lin - 1 && j != 0 && j != ph->col - 1) {
				pix_sum += ch[i - 1][j - 1] * ker[0][0];
				pix_sum += ch[i - 1][j] * ker[0][1];
				pix_sum += ch[i - 1][j + 1] * ker[0][2];
				pix_sum += ch[i][j - 1] * ker[1][0];
				pix_sum += ch[i][j] * ker[1][1];
				pix_sum += ch[i][j + 1] * ker[1][2];
				pix_sum += ch[i + 1][j - 1] * ker[2][0];
				pix_sum += ch[i + 1][j] * ker[2][1];
				pix_sum += ch[i + 1][j + 1] * ker[2][2];

				//divide the sum, not every single term seperately for accuracy
				pix_sum /= coef;

				result[res_i][res_j] = clamp_i(pix_sum);
			} else {
				//if the pixel doesn't have all the necesary neighbors
				result[res_i][res_j] = ch[i][j];
			}

			//step to the next cell
			++res_j;
			if (res_j >= col) {
				res_j = 0;
				++res_i;
			}
		}
	}
	return result;
}
