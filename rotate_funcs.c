#include "rotate_funcs.h"

void rotate(photo_t *ph)
{
	//check if any photo was loaded
	if (!ph->photo_mat && !ph->rgb_mat.red) {
		error_no_load();
		return;
	}

	//init and read the angle of rotation
	int angle;
	scanf("%d", &angle);

	//check if the rotation angle is permited
	if (angle < -360 || angle > 360 || angle % 90 != 0) {
		error_rotation_angle();
		return;
	}

	//count of rotations of 90 degrees
	int rot_cnt = angle / 90;

	// printf("before first for\n");
	// printf("lines: %d, cols: %d\n", ph->lin, ph->col);
	// printf("x bot: %d, y bot: %d\n", ph->bot_x, ph->bot_y);

	//if its selected the whole photo
	if (ph->top_x == 0 && ph->top_y == 0 && 
		ph->bot_x + 1 == ph->lin && ph->bot_y + 1 == ph->col) {
		//rotate it even if it's not square
		if (angle > 0) {
			for (int i = 0; i < rot_cnt; ++i) 
				if (is_color(ph->type)) {
					rotate_all(ph, &ph->rgb_mat.red, POS, FALSE);
					rotate_all(ph, &ph->rgb_mat.green, POS, FALSE);
					rotate_all(ph, &ph->rgb_mat.blue, POS, TRUE);//ch1
				} else {
					rotate_all(ph, &ph->photo_mat, POS, TRUE);//ch1
				}
		} else {
			rot_cnt *= -1;
			for (int i = 0; i < rot_cnt; ++i)
				if (is_color(ph->type)) {
					rotate_all(ph, &ph->rgb_mat.red, NEG, FALSE);
					rotate_all(ph, &ph->rgb_mat.green, NEG, FALSE);
					rotate_all(ph, &ph->rgb_mat.blue, NEG, TRUE);
				} else {
					rotate_all(ph, &ph->photo_mat, NEG, TRUE);
				}
		}
		succes_rotate(angle);
		return;
	}

	int sel_lin = ph->bot_x - ph->top_x + 1;
	int sel_col = ph->bot_y - ph->top_y + 1;
	if (sel_lin != sel_col) {
		error_square_sel();
		return;
	}

	if (angle > 0) {
		for (int i = 0; i < rot_cnt; ++i)
			if (is_color(ph->type)) {
				overwrite_rotate(ph, ph->rgb_mat.red, sel_lin, sel_col, POS);
				overwrite_rotate(ph, ph->rgb_mat.green, sel_lin, sel_col, POS);
				overwrite_rotate(ph, ph->rgb_mat.blue, sel_lin, sel_col, POS);
			} else {
				overwrite_rotate(ph, ph->photo_mat, sel_lin, sel_col, POS);
			}
	} else {
		//make it positive
		rot_cnt *= -1;
		for (int i = 0; i < rot_cnt; ++i)
			if (is_color(ph->type)) {
				overwrite_rotate(ph, ph->rgb_mat.red, sel_lin, sel_col, NEG);
				overwrite_rotate(ph, ph->rgb_mat.green, sel_lin, sel_col, NEG);
				overwrite_rotate(ph, ph->rgb_mat.blue, sel_lin, sel_col, NEG);
			} else {
				overwrite_rotate(ph, ph->photo_mat, sel_lin, sel_col, NEG);
			}
	}
	succes_rotate(angle);
}

//overwrite the old math with the rotated one
void overwrite_rotate(photo_t *ph, int **mat, int lin, int col, int dir)
{
	int **rotated;
	if (dir > 0)
		rotated = rotate_right(ph, mat, lin, col);
	else 
		rotated = rotate_left(ph, mat, lin, col);

	int new_i = 0;
	int new_j = 0;
	for (int i = ph->top_x; i <= ph->bot_x; ++i)
		for (int j = ph->top_y; j <= ph->bot_y; ++j) {
			mat[i][j] = rotated[new_i][new_j];
			++new_j;
			if (new_j >= col) {
				new_j = 0;
				++new_i;
			}
		}

	free_mat(rotated, lin);
}

int **rotate_right(photo_t *ph, int **mat, int lin, int col)
{
	//lin and col are actually equal lol u dumb fuck
	int **rotated = alloc_matrix(lin, col);

	int new_i = 0;
	int new_j = col - 1;

	for (int i = ph->top_x; i <= ph->bot_x; ++i)
		for (int j = ph->top_y; j <= ph->bot_y; ++j) {
			rotated[new_i][new_j] = mat[i][j];
			++new_i;
			if (new_i >= lin) {
				new_i = 0;
				--new_j;
			}
		}
	// for (int i = ph->top_x; i <= ph->bot_x; ++i) {
	// 	for (int j = ph->top_y; j <= ph->bot_y; ++j)
	// 		printf("%d ", mat[i][j]);
	// 	printf("\n");
	// }
	
	
	return rotated;
}

int **rotate_left(photo_t *ph, int **mat, int lin, int col)
{
	int **rotated = alloc_matrix(lin, col);

	int new_i = lin - 1;
	int new_j = 0;
	for (int i = ph->top_x; i <= ph->bot_x; ++i)
		for (int j = ph->top_y; j <= ph->bot_y; ++j) {
			rotated[new_i][new_j] = mat[i][j];
			--new_i;
			if (new_i < 0) {
				new_i = lin - 1;
				++new_j;
			}
		}

	return rotated;
}

void rotate_all(photo_t *ph, int ***mat, int dir, int ch)
{
	int **rotated;
	if (dir > 0)
		rotated = rot_all_r(ph, *mat, ph->lin, ph->col);
	else 
		rotated = rot_all_l(ph, *mat, ph->lin, ph->col);

	free_mat(*mat, ph->lin);
	*mat = rotated;
	
	//swap lines and cols (only if its bw or the last color channel
	//to be rotated)
	if (ch == 1) { //TODO swap
		swap_int(&ph->lin, &ph->col);
		swap_int(&ph->bot_x, &ph->bot_y);
	}
}

int **rot_all_r(photo_t *ph, int **mat, int lin, int col)
{
	int **rotated = alloc_matrix(col, lin);

	int new_i = 0;
	int new_j = ph->lin - 1;
	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j) {
			rotated[new_i][new_j] = mat[i][j];
			++new_i;
			if (new_i >= ph->col) {
				new_i = 0;
				--new_j;
			}
		}
	return rotated;
}

int **rot_all_l(photo_t *ph, int **mat, int lin, int col)
{
	int **rotated = alloc_matrix(col, lin);

	int new_i = ph->col - 1;
	int new_j = 0;
	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j) {
			rotated[new_i][new_j] = mat[i][j];
			--new_i;
			if (new_i < 0) {
				new_i = ph->col - 1;
				++new_j;
			}
		}
	return rotated;
}
