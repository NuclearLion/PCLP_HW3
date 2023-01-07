// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "crop_funcs.h"

//main call of crop command
void crop(photo_t *ph)
{
	//check if any photo is loaded
	if (check_load(ph)) {
		error_no_load();
		return;
	}

	//save the new smaller photo's nr of columns and lines
	int new_lin = ph->bot.x - ph->top.x + 1;
	int new_col = ph->bot.y - ph->top.y + 1;

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

//alloc a new memory area and fill it with values inside
//the selection from the old matrix
int **crop_mat(int **mat, photo_t *ph, int new_lin, int new_col)
{
	// alloc a new memory area
	int **cropped = alloc_matrix(new_lin, new_col);

	// init the new coordinates
	int new_i = 0;
	int new_j = 0;

	// write values from the old photo
	for (int i = ph->top.x; i <= ph->bot.x; ++i) {
		for (int j = ph->top.y; j <= ph->bot.y; ++j) {
			cropped[new_i][new_j] = mat[i][j];

			//step to the next matrix
			++new_j;
			if (new_j >= new_col) {
				new_j = 0;
				++new_i;
			}
		}
	}
	return cropped;
}
