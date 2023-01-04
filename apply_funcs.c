#include "apply_funcs.h"

void apply(photo_t *ph)
{
	char kernel_type[KERNEL_LENGTH];
	scanf("%s", kernel_type);

	if (ph->photo_mat == NULL && ph->rgb_mat.red == NULL) {
		error_no_load();
		return;
	}

	if (!is_color(ph->type)) {
		error_charlie();
		return;
	}

	switch (hash_apply(kernel_type)) {
	case 0:
		edge(ph);
		printf("in edge\n");
		break;
	case 1:
		sharpen(ph);
		printf("in sharpen\n");
		break;
	case 2:
		box_blur(ph);
		printf("in blur\n");
		break;
	case 3:
		gaussian_blur(ph);
		printf("in gaussian blur\n");
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

	//overwrite with ph
	int old_i = ph->top_x;
	int old_j = ph->top_y;
	for (int i = 0; i < sel_lin; ++i)
		for (int j = 0; j < sel_col; ++j) {
			color_ch[old_i][old_j] = effect[i][j];
			++old_j;
			if (old_j > ph->bot_y) {
				old_j = ph->top_y;
				++old_i;
			}
		}

	//free the new mat
	free_mat(effect, sel_lin);
}

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
				pix_sum += clamp_i(ch[i - 1][j - 1] * ker[0][0] / coef);
				pix_sum += clamp_i(ch[i - 1][j] * ker[0][1] / coef);
				pix_sum += clamp_i(ch[i - 1][j + 1] * ker[0][2] / coef);
				pix_sum += clamp_i(ch[i][j - 1] * ker[1][0] / coef);
				pix_sum += clamp_i(ch[i][j] * ker[1][1] / coef);
				pix_sum += clamp_i(ch[i][j + 1] * ker[1][2] / coef);
				pix_sum += clamp_i(ch[i + 1][j - 1] * ker[2][0] / coef);
				pix_sum += clamp_i(ch[i + 1][j] * ker[2][1] / coef);
				pix_sum += clamp_i(ch[i + 1][j + 1] * ker[2][2] / coef);

				result[res_i][res_j] = clamp_i(pix_sum);
			} else {
				result[res_i][res_j] = ch[i][j];
			}

			++res_j;
			if (res_j > col) {
				res_j = 0;
				++res_i;
			}
		}
	}

	return result;
}
