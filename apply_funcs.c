#include "apply_funcs.h"

void apply(photo_t *ph)
{
	char kernel_type[KERNEL_LENGTH];
	scanf("%s", kernel_type);

	if (ph->photo_mat == NULL) {
		error_no_load();
		return;
	}

	if (ph->type == P2 || ph->type == P5) {
		error_charlie();
		return;
	}


	switch (hash_apply(kernel_type)) {
	case 0:
		edge(ph);
		printf("in edge\n");
		break;
	case 1:
		printf("in sharpen\n");
		break;
	case 2:
		printf("in blur\n");
		break;
	case 3:
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
	int lin_sel = ph->bot_x - ph->top_x + 1;
	int col_sel = ph->bot_y + 2 - ph->top_y + 1;
	int **ker_zone = alloc_matrix(lin_sel, col_sel);

	int **edge_k = alloc_matrix(3, 3);
	edge_k[0][0] = -1;
	edge_k[0][1] = -1;
	edge_k[0][2] = -1;
	edge_k[1][0] = -1;
	edge_k[1][1] = 8;
	edge_k[1][2] = -1;
	edge_k[2][0] = -1;
	edge_k[2][1] = -1;
	edge_k[2][2] = -1;

	
	//BIG TODO FUNCTIONS FOR THIS SHIT LOOKING THING
	//make a func to aplly any filter
	//pass the photo and matrix of filter to it


	//R channel
	int ker_i = 0;
	int ker_j = 0;
	for (int i = ph->top_x; i <= ph->bot_x; ++i) {
		for (int j = ph->top_y; j <= ph->bot_y + 2; j += 3) {
			int pix_sum = 0;

			//if it has enough nebourghs (vecini)
			if (i != 0 && i != ph->lin - 1 && j != 0 && j != ph->col - 3) {
				pix_sum += clamp_i(ph->photo_mat[i - 1][j - 3] * edge_k[0][0]);
				pix_sum += clamp_i(ph->photo_mat[i - 1][j] * edge_k[0][1]);
				pix_sum += clamp_i(ph->photo_mat[i - 1][j + 3] * edge_k[0][2]);
				pix_sum += clamp_i(ph->photo_mat[i][j - 3] * edge_k[1][0]);
				pix_sum += clamp_i(ph->photo_mat[i][j] * edge_k[1][1]);
				pix_sum += clamp_i(ph->photo_mat[i][j + 3] * edge_k[1][2]);
				pix_sum += clamp_i(ph->photo_mat[i + 1][j - 3] * edge_k[2][0]);
				pix_sum += clamp_i(ph->photo_mat[i + 1][j] * edge_k[2][1]);
				pix_sum += clamp_i(ph->photo_mat[i + 1][j + 3] * edge_k[2][2]);

				ker_zone[ker_i][ker_j] = clamp_i(pix_sum);
			} else {
				ker_zone[ker_i][ker_j] = ph->photo_mat[i][j];
			}

			ker_j += 3;
			if (ker_j > col_sel) {
				ker_j = 0;
				++ker_i;
			}
		}
	}

	//G channel
	ker_i = 0;
	ker_j = 1;
	for (int i = ph->top_x; i <= ph->bot_x; ++i) {
		for (int j = ph->top_y + 1; j <= ph->bot_y + 2; j += 3) {
			int pix_sum = 0;

			//if it has enough nebourghs (vecini)
			if (i != 0 && i != ph->lin - 1 && j != 0 && j != ph->col - 2) {
				pix_sum += clamp_i(ph->photo_mat[i - 1][j - 3] * edge_k[0][0]);
				pix_sum += clamp_i(ph->photo_mat[i - 1][j] * edge_k[0][1]);
				pix_sum += clamp_i(ph->photo_mat[i - 1][j + 3] * edge_k[0][2]);
				pix_sum += clamp_i(ph->photo_mat[i][j - 3] * edge_k[1][0]);
				pix_sum += clamp_i(ph->photo_mat[i][j] * edge_k[1][1]);
				pix_sum += clamp_i(ph->photo_mat[i][j + 3] * edge_k[1][2]);
				pix_sum += clamp_i(ph->photo_mat[i + 1][j - 3] * edge_k[2][0]);
				pix_sum += clamp_i(ph->photo_mat[i + 1][j] * edge_k[2][1]);
				pix_sum += clamp_i(ph->photo_mat[i + 1][j + 3] * edge_k[2][2]);

				ker_zone[ker_i][ker_j] = clamp_i(pix_sum);
			} else {
				ker_zone[ker_i][ker_j] = ph->photo_mat[i][j];
			}

			ker_j += 3;
			if (ker_j > col_sel) {
				ker_j = 0;
				++ker_i;
			}
		}
	}

	//B channel
	ker_i = 0;
	ker_j = 2;
	for (int i = ph->top_x; i <= ph->bot_x; ++i) {
		for (int j = ph->top_y + 2; j <= ph->bot_y + 2; j += 3) {
			int pix_sum = 0;

			//if it has enough nebourghs (vecini)
			if (i != 0 && i != ph->lin - 1 && j != 0 && j != ph->col - 1) {
				pix_sum += clamp_i(ph->photo_mat[i - 1][j - 3] * edge_k[0][0]);
				pix_sum += clamp_i(ph->photo_mat[i - 1][j] * edge_k[0][1]);
				pix_sum += clamp_i(ph->photo_mat[i - 1][j + 3] * edge_k[0][2]);
				pix_sum += clamp_i(ph->photo_mat[i][j - 3] * edge_k[1][0]);
				pix_sum += clamp_i(ph->photo_mat[i][j] * edge_k[1][1]);
				pix_sum += clamp_i(ph->photo_mat[i][j + 3] * edge_k[1][2]);
				pix_sum += clamp_i(ph->photo_mat[i + 1][j - 3] * edge_k[2][0]);
				pix_sum += clamp_i(ph->photo_mat[i + 1][j] * edge_k[2][1]);
				pix_sum += clamp_i(ph->photo_mat[i + 1][j + 3] * edge_k[2][2]);

				ker_zone[ker_i][ker_j] = clamp_i(pix_sum);
			} else {
				ker_zone[ker_i][ker_j] = ph->photo_mat[i][j];
			}

			ker_j += 3;
			if (ker_j > col_sel) {
				ker_j = 0;
				++ker_i;
			}
		}
	}

	ker_i = 0;
	ker_j = 0;
	for (int i = ph->top_x; i <= ph->bot_x; ++i) {
		for (int j = ph->top_y; j <= ph->bot_y; ++j) {
			ph->photo_mat[i][j] = ker_zone[ker_i][ker_j];

			ker_j++;
			if (ker_j > col_sel) {
				ker_j = 0;
				ker_i++;
			}
		}
	}


	free_mat(edge_k, 3);
	free_mat(ker_zone, lin_sel);
}
