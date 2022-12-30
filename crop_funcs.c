#include "crop_funcs.h"

void crop(photo_t *ph)
{
	if (ph->photo_mat == NULL) {
		error_no_load();
		return;
	}

	int new_col = 0, new_lin = 0;

	if (ph->type == P2 || ph->type == P5) {
		new_lin = ph->bot_x - ph->top_x;
		new_col = ph->bot_y - ph->top_y;
	} else {
		new_lin = ph->bot_x - ph->top_x;
		new_col = ph->bot_y - ph->top_y - 1;
	}

	//alloc memory for a new cropped photo
	int **cropped = alloc_matrix(new_lin, new_col);

	int new_i = 0;
	int new_j = 0;
	for (int i = ph->top_x; i < ph->bot_x; ++i)
		for (int j = ph->top_y; j < ph->bot_y; ++j) {
			cropped[new_i][new_j] = ph->photo_mat[i][j];
			++new_j;
			if (new_j >= new_col) {
				++new_i;
				new_j = 0;
			}
		}

	//free the old mat and point to the new one
	free_mat(ph->photo_mat, ph->lin);
	ph->photo_mat = cropped;

	//save new dimensions
	ph->lin = new_lin;
	ph->col = new_col;

	//init coords as if the whole picture is selected
	select_all(ph);

	succes_crop();
}
