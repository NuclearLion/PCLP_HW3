//Dan-Dominic Staicu 311CA 2023
#include "apply_funcs.h"

void apply(photo_t *ph)
{
	char kernel_type[KERNEL_LENGTH];
	fgets(kernel_type, KERNEL_LENGTH, stdin);

	//check if any image was loaded
	if (!ph->photo_mat && !ph->rgb_mat.red) {
		error_no_load();
		return;
	}

	if (strcmp(kernel_type, "\n") == 0)
	{
		error_invalid();
		return;
	}

	//remove the space from before and \n at the end
	for (int i = 1; kernel_type[i]; ++i)
		kernel_type[i - 1] = kernel_type[i];
	
	kernel_type[strlen(kernel_type) - 2] = '\0';

	//check if loaded photo is color
	if (!is_color(ph->type)) {
		error_charlie();
		return;
	}
	//printf("kernel type: %s\n", kernel_type);

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
		error_apply_parameter();
		return;
	}

	succes_apply(kernel_type);
}

void edge(photo_t *ph)
{
	int divide_coef = 1;

	int **edge_k = alloc_matrix(KER_MAT_DIM, KER_MAT_DIM);
	edge_k[0][0] = -1;
	edge_k[0][1] = -1;
	edge_k[0][2] = -1;
	edge_k[1][0] = -1;
	edge_k[1][1] = 8;
	edge_k[1][2] = -1;
	edge_k[2][0] = -1;
	edge_k[2][1] = -1;
	edge_k[2][2] = -1;

	kern(edge_k, ph->rgb_mat.red, ph, divide_coef);
	kern(edge_k, ph->rgb_mat.green, ph, divide_coef);
	kern(edge_k, ph->rgb_mat.blue, ph, divide_coef);

	free_mat(edge_k, KER_MAT_DIM);
}

void sharpen(photo_t *ph)
{
	int divide_coef = 1;

	int **sharpen_k = alloc_matrix(KER_MAT_DIM, KER_MAT_DIM);
	sharpen_k[0][0] = 0;
	sharpen_k[0][1] = -1;
	sharpen_k[0][2] = 0;
	sharpen_k[1][0] = -1;
	sharpen_k[1][1] = 5;
	sharpen_k[1][2] = -1;
	sharpen_k[2][0] = 0;
	sharpen_k[2][1] = -1;
	sharpen_k[2][2] = 0;

	kern(sharpen_k, ph->rgb_mat.red, ph, divide_coef);
	kern(sharpen_k, ph->rgb_mat.green, ph, divide_coef);
	kern(sharpen_k, ph->rgb_mat.blue, ph, divide_coef);

	free_mat(sharpen_k, KER_MAT_DIM);
}

void box_blur(photo_t *ph)
{
	int divide_coef = 9;

	int **box_blur_k = alloc_matrix(KER_MAT_DIM, KER_MAT_DIM);
	box_blur_k[0][0] = 1;
	box_blur_k[0][1] = 1;
	box_blur_k[0][2] = 1;
	box_blur_k[1][0] = 1;
	box_blur_k[1][1] = 1;
	box_blur_k[1][2] = 1;
	box_blur_k[2][0] = 1;
	box_blur_k[2][1] = 1;
	box_blur_k[2][2] = 1;

	kern(box_blur_k, ph->rgb_mat.red, ph, divide_coef);
	kern(box_blur_k, ph->rgb_mat.green, ph, divide_coef);
	kern(box_blur_k, ph->rgb_mat.blue, ph, divide_coef);

	free_mat(box_blur_k, KER_MAT_DIM);
}

void gaussian_blur(photo_t *ph)
{
	int divide_coef = 16;

	int **gaussian_blur_k = alloc_matrix(KER_MAT_DIM, KER_MAT_DIM);
	gaussian_blur_k[0][0] = 1;
	gaussian_blur_k[0][1] = 2;
	gaussian_blur_k[0][2] = 1;
	gaussian_blur_k[1][0] = 2;
	gaussian_blur_k[1][1] = 4;
	gaussian_blur_k[1][2] = 2;
	gaussian_blur_k[2][0] = 1;
	gaussian_blur_k[2][1] = 2;
	gaussian_blur_k[2][2] = 1;

	kern(gaussian_blur_k, ph->rgb_mat.red, ph, divide_coef);
	kern(gaussian_blur_k, ph->rgb_mat.green, ph, divide_coef);
	kern(gaussian_blur_k, ph->rgb_mat.blue, ph, divide_coef);

	free_mat(gaussian_blur_k, KER_MAT_DIM);
}

//overwrites the main photo with the result of appling kernel 
//over every color channel
void kern(int **kernel, int **color_ch, photo_t *ph, int coef)
{
	//calculate nr of lines and cols inside the selection
	int sel_lin = ph->bot_x - ph->top_x + 1;
	int sel_col = ph->bot_y - ph->top_y + 1;

	//alloc new mat
	//call func to create new mat by maths
	int **effect = apply_kern(ph, color_ch, kernel, sel_lin, sel_col, coef);

	//overwrite ph
	int ef_i = 0;
	int ef_j = 0;
	for (int i = ph->top_x; i <= ph->bot_x; ++i)
		for (int j = ph->top_y; j <= ph->bot_y; ++j) {
			color_ch[i][j] = effect[ef_i][ef_j];
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
int **apply_kern(photo_t *ph, int **ch, int **ker, int lin, int col, int coef)
{
	int **result = alloc_matrix(lin, col);

	int res_i = 0;
	int res_j = 0;
	for (int i = ph->top_x; i <= ph->bot_x; ++i) {
		for (int j = ph->top_y; j <= ph->bot_y; ++j) {
			int pix_sum = 0;

			//if the current pixel has neibourghs
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

				pix_sum /= coef;

				result[res_i][res_j] = clamp_i(pix_sum);
			} else {
				result[res_i][res_j] = ch[i][j];
			}

			++res_j;
			if (res_j >= col) {
				res_j = 0;
				++res_i;
			}
		}
	}

	return result;
}
