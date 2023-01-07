// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "rotate_funcs.h"

//main call for ROTATE command
void rotate(photo_t *ph)
{
	//init and read the angle of rotation
	int angle;
	scanf("%d", &angle);
	//check if any photo was loaded
	if (check_load(ph)) {
		error_no_load();
		return;
	}
	//check if the rotation angle is permited
	if (angle < -360 || angle > 360 || angle % 90 != 0) {
		error_rotation_angle();
		return;
	}
	//count of rotations of 90 degrees
	int rot_cnt = angle / 90;

	//if its selected the whole photo rotate it even if it's not square
	if (ph->top.x == 0 && ph->top.y == 0 &&
		ph->bot.x + 1 == ph->lin && ph->bot.y + 1 == ph->col) {
		// if the angle is positive
		if (angle > 0) {
			//rotate to right the image 90 degrees for rot_cnt times
			for (int i = 0; i < rot_cnt; ++i)
				//if it's color, every channel has to be rotated
				if (is_color(ph->type)) {
					rotate_all(ph, &ph->rgb_mat.red, POS, FALSE);
					rotate_all(ph, &ph->rgb_mat.green, POS, FALSE);
					rotate_all(ph, &ph->rgb_mat.blue, POS, TRUE);
				} else {
					rotate_all(ph, &ph->photo_mat, POS, TRUE);
				}
		} else {
			//make the count positive
			rot_cnt *= -1;
			////rotate to left the image 90 degrees for rot_cnt times
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

	//new dimensions of the selected area inside the photo
	int sel_lin = ph->bot.x - ph->top.x + 1;
	int sel_col = ph->bot.y - ph->top.y + 1;
	//check if the selection is square
	if (sel_lin != sel_col) {
		error_square_sel();
		return;
	}

	//same thing as the above, but calling other functions special for select
	if (angle > 0) {
		for (int i = 0; i < rot_cnt; ++i)
			if (is_color(ph->type)) {
				overwrite_rotate(ph, ph->rgb_mat.red, sel_lin, POS);
				overwrite_rotate(ph, ph->rgb_mat.green, sel_lin, POS);
				overwrite_rotate(ph, ph->rgb_mat.blue, sel_lin, POS);
			} else {
				overwrite_rotate(ph, ph->photo_mat, sel_lin, POS);
			}
	} else {
		rot_cnt *= -1;
		for (int i = 0; i < rot_cnt; ++i)
			if (is_color(ph->type)) {
				overwrite_rotate(ph, ph->rgb_mat.red, sel_lin, NEG);
				overwrite_rotate(ph, ph->rgb_mat.green, sel_lin, NEG);
				overwrite_rotate(ph, ph->rgb_mat.blue, sel_lin, NEG);
			} else {
				overwrite_rotate(ph, ph->photo_mat, sel_lin, NEG);
			}
	}
	succes_rotate(angle);
}

//overwrite the old matrix with the rotated one
void overwrite_rotate(photo_t *ph, int **mat, int side, int dir)
{
	int **rotated;

	//if the direction parameter is positive, the rotation must be done
	//to right, otherwise to the left
	if (dir > 0)
		rotated = rotate_right(ph, mat, side);
	else
		rotated = rotate_left(ph, mat, side);

	//overwrite the selected area from the old matrix
	//with the values inside the new one
	int new_i = 0;
	int new_j = 0;
	for (int i = ph->top.x; i <= ph->bot.x; ++i)
		for (int j = ph->top.y; j <= ph->bot.y; ++j) {
			mat[i][j] = rotated[new_i][new_j];
			++new_j;
			if (new_j >= side) {
				new_j = 0;
				++new_i;
			}
		}

	free_mat(rotated, side);
}

//create a new square matrix with values from
//the selection in the old one, but rotated to right
int **rotate_right(photo_t *ph, int **mat, int side)
{
	int **rotated = alloc_matrix(side, side);

	//start the parameters from the top right corner of the new matrix
	//and go down - left with filling it
	int new_i = 0;
	int new_j = side - 1;
	for (int i = ph->top.x; i <= ph->bot.x; ++i)
		for (int j = ph->top.y; j <= ph->bot.y; ++j) {
			rotated[new_i][new_j] = mat[i][j];
			++new_i;
			if (new_i >= side) {
				new_i = 0;
				--new_j;
			}
		}
	return rotated;
}

//create a new square matrix with values from
//the selection in the old one, but rotated to left
int **rotate_left(photo_t *ph, int **mat, int side)
{
	int **rotated = alloc_matrix(side, side);

	//start the parameters from bottom left corner of the new matrix
	//and go up - right with filling it
	int new_i = side - 1;
	int new_j = 0;
	for (int i = ph->top.x; i <= ph->bot.x; ++i)
		for (int j = ph->top.y; j <= ph->bot.y; ++j) {
			rotated[new_i][new_j] = mat[i][j];
			--new_i;
			if (new_i < 0) {
				new_i = side - 1;
				++new_j;
			}
		}
	return rotated;
}

//create a new rotated matrix of the whole photo
void rotate_all(photo_t *ph, int ***mat, int dir, int ch)
{
	int **rotated;
	if (dir > 0)
		rotated = rot_all_r(ph, *mat, ph->lin, ph->col);
	else
		rotated = rot_all_l(ph, *mat, ph->lin, ph->col);

	//free the old matrix and point to the new memory area
	free_mat(*mat, ph->lin);
	*mat = rotated;

	//swap lines and cols (only if its black and white or
	//the last color channel to be rotated)
	if (ch == 1) {
		swap_int(&ph->lin, &ph->col);
		swap_int(&ph->bot.x, &ph->bot.y);
	}
}

//alloc and fill a new rotated to right mat
int **rot_all_r(photo_t *ph, int **mat, int lin, int col)
{
	//the number of columns and lines are inversed after one rotation
	int **rotated = alloc_matrix(col, lin);

	//start the parameters from the top right corner of the new matrix
	//and go down - left with filling it
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

//alloc and fill a new rotated to left mat
int **rot_all_l(photo_t *ph, int **mat, int lin, int col)
{
	//the number of columns and lines are inversed after one rotation
	int **rotated = alloc_matrix(col, lin);

	//start the parameters from bottom left corner of the new matrix
	//and go up - right with filling it
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
