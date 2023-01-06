#include "crop_funcs.h"

void crop(photo_t *ph)
{
	if (ph->photo_mat == NULL && ph->rgb_mat.red == NULL) {
		error_no_load();
		return;
	}

	int new_lin = ph->bot_x - ph->top_x + 1;
	int new_col = ph->bot_y - ph->top_y + 1;

	//free the old mat(s) and point to the new one(s)
	if (!is_color(ph->type)) {
		int **aux_mat = crop_mat(ph->photo_mat, ph, new_lin, new_col);
		free_mat(ph->photo_mat, ph->lin);
		ph->photo_mat = aux_mat;
	} else {
		int **aux_r = crop_mat(ph->rgb_mat.red, ph, new_lin, new_col);
		int **aux_g = crop_mat(ph->rgb_mat.green, ph, new_lin, new_col);
		int **aux_b = crop_mat(ph->rgb_mat.blue, ph, new_lin, new_col);
		free_mat(ph->rgb_mat.red, ph->lin);
		free_mat(ph->rgb_mat.green, ph->lin);
		free_mat(ph->rgb_mat.blue, ph->lin);
		ph->rgb_mat.red = aux_r;
		ph->rgb_mat.green = aux_g;
		ph->rgb_mat.blue = aux_b;
	}

	//save the new number of lines and columns
	ph->lin = new_lin;
	ph->col = new_col;

	//init coords as if the whole picture is selected
	select_all(ph);
	succes_crop();
}

int **crop_mat(int **mat, photo_t *ph, int new_lin, int new_col)
{
	int **cropped = alloc_matrix(new_lin, new_col);
	int new_i = 0;
	int new_j = 0;

	for (int i = ph->top_x; i <= ph->bot_x; ++i) {
		for (int j = ph->top_y; j <= ph->bot_y; ++j) {
			cropped[new_i][new_j] = mat[i][j];
			++new_j;
			if (new_j >= new_col) {
				new_j = 0;
				++new_i;
			}
		}
	}
	return cropped;
}
