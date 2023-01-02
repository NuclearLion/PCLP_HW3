#include "crop_funcs.h"

void crop(photo_t *ph)
{
	if (ph->photo_mat == NULL) {
		error_no_load();
		return;
	 }

	int new_col = 0;
	int new_lin = 0;

	printf("x1:%d y1:%d x2:%d y2:%d\n", ph->top_x, ph->top_y, ph->bot_x, ph->bot_y);

	int col_coef = 1;

	if (ph->type == P2 || ph->type == P5) {
		// if (ph->top_x == 0)
		// 	new_lin = ph->bot_x - 1;
		// else
		new_lin = ph->bot_x - ph->top_x;

		// if (ph->top_y == 0)
		// 	new_col = ph->bot_y - 1;
		// else
		new_col = ph->bot_y - ph->top_y;
	} else {
		col_coef = 3;
		new_lin = ph->bot_x - ph->top_x;
		new_col = ph->bot_y - ph->top_y;
	}

	//alloc memory for a new cropped photo
	int **cropped;

	printf("newlin: %d, newcol: %d\n", new_lin, new_col);

	int new_i = 0;
	int new_j = 0;
	if (new_col != 0 && new_lin != 0) {
		printf("crashes in first\n");
		cropped = alloc_matrix(new_lin, new_col);
		for (int i = ph->top_x; i < ph->bot_x; ++i)
			for (int j = ph->top_y; j < ph->bot_y; ++j) {
				cropped[new_i][new_j] = ph->photo_mat[i][j];
				++new_j;
				if (new_j >= new_col) {
					++new_i;
					new_j = 0;
				}
			}
	} else if (new_col == 0 && new_lin != 0) {
		new_col = 1;
		printf("crashes in this func col = 0\n");
		cropped = alloc_matrix(new_lin, new_col);
		for (int i = ph->top_x; i < ph->bot_x; ++i) {
			cropped[new_i][0] = ph->photo_mat[i][0];
			++new_i;
		}
	} else if (new_col != 0 && new_lin == 0) {
		new_lin = 1;
		printf("crashes in this func lin = 0\n");
		cropped = alloc_matrix(new_lin, new_col);
		for (int j = ph->top_y; j < ph->bot_y; ++j) {
			cropped[0][new_j] = ph->photo_mat[0][j];
			++new_j;
		}
	} else {
		printf("crashes in this func col = 0 lin = 0\n");
		new_col = 1;
		new_lin = 1;
		cropped = alloc_matrix(new_lin, new_col);
		cropped[0][0] = ph->photo_mat[ph->top_x][ph->top_y];
	}
	//new_i--, new_j--;

	//free the old mat and point to the new one
	free_mat(ph->photo_mat, ph->lin);
	ph->photo_mat = cropped;

	//save new dimensions
	printf("newcol at end: %d\n", new_col);
	ph->lin = new_lin;
	ph->col = new_col;

	//init coords as if the whole picture is selected
	select_all(ph);

	succes_crop();
}
