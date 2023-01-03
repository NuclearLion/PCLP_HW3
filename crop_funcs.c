#include "crop_funcs.h"

void crop(photo_t *ph)
{
	if (ph->photo_mat == NULL) {
		error_no_load();
		return;
	 }

	int new_col = 0;
	int new_lin = 0;

	//printf("x1:%d y1:%d x2:%d y2:%d\n", ph->top_x, ph->top_y, ph->bot_x, ph->bot_y);

	// int col_coef = 1;

	// if (ph->type == P2 || ph->type == P5) {
	// 	// if (ph->top_x == 0)
	// 	// 	new_lin = ph->bot_x - 1;
	// 	// else
	// 	new_lin = ph->bot_x - ph->top_x;

	// 	// if (ph->top_y == 0)
	// 	// 	new_col = ph->bot_y - 1;
	// 	// else
	// 	new_col = ph->bot_y - ph->top_y;
	// } else {
	// 	new_lin = ph->bot_x - ph->top_x;
	// 	new_col = ph->bot_y - ph->top_y;
	// }


	new_lin = ph->bot_x - ph->top_x + 1;
	if (ph->type == P2 || ph->type == P5) {
		new_col = ph->bot_y - ph->top_y + 1;
	} else {
		new_col = ph->bot_y - ph->top_y + 3; //+G+B+1; //if it's P3 or P6, we save the coord of the
		//first channel of pixel's RGB
	}

	//alloc memory for a new cropped photo
	int **cropped = alloc_matrix(new_lin, new_col);

	int new_i = 0;
	int new_j = 0;
	if (ph->type == P2 || ph->type == P5)
		for (int i = ph->top_x; i <= ph->bot_x; ++i) {
			for (int j = ph->top_y; j <= ph->bot_y; ++j) {
				cropped[new_i][new_j] = ph->photo_mat[i][j];
				++new_j;
				if (new_j >= new_col) {
					new_j = 0;
					++new_i;
				}
			}
		}
	else //P3 oor P6
	{
		printf("colour : new_lin: %d, new_col: %d\n", new_lin, new_col);
		for (int i = ph->top_x; i <= ph->bot_x; ++i) {
			for (int j = ph->top_y; j <= ph->bot_y + 2; ++j) {
				cropped[new_i][new_j] = ph->photo_mat[i][j];
				++new_j;
				if (new_j >= new_col) {
					new_j = 0;
					++new_i;
				}
			}
		}
	}
	// printf("newlin: %d, newcol: %d\n", new_lin, new_col);

	// int new_i = 0;
	// int new_j = 0;

	// cropped = alloc_matrix(new_lin, new_col);
	// for (int i = ph->top_x; i <= ph->bot_x; ++i)
	// 	for (int j = ph->top_y; j <= ph->bot_y; ++j) {
	// 		cropped[new_i][new_j] = ph->photo_mat[i][j];
	// 		++new_j;
	// 		if (new_j >= new_col) {
	// 			++new_i;
	// 			new_j = 0;
	// 		}
	// 	}

	//free the old mat and point to the new one
	free_mat(ph->photo_mat, ph->lin);
	ph->photo_mat = cropped;

	//save new dimensions
	//printf("newcol at end: %d\n", new_col);
	ph->lin = new_lin;
	ph->col = new_col;

	//init coords as if the whole picture is selected
	select_all(ph);

	succes_crop();
}