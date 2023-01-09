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
					rotate_all(ph, &ph->rgb_mat.red, rot_all_r, FALSE);
					rotate_all(ph, &ph->rgb_mat.green, rot_all_r, FALSE);
					rotate_all(ph, &ph->rgb_mat.blue, rot_all_r, TRUE);
				} else {
					rotate_all(ph, &ph->photo_mat, rot_all_r, TRUE);
				}
		} else {
			//make the count positive
			rot_cnt *= -1;
			////rotate to left the image 90 degrees for rot_cnt times
			for (int i = 0; i < rot_cnt; ++i)
				if (is_color(ph->type)) {
					rotate_all(ph, &ph->rgb_mat.red, rot_all_l, FALSE);
					rotate_all(ph, &ph->rgb_mat.green, rot_all_l, FALSE);
					rotate_all(ph, &ph->rgb_mat.blue, rot_all_l, TRUE);
				} else {
					rotate_all(ph, &ph->photo_mat, rot_all_l, TRUE);
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
				overwrite_rotate(ph, ph->rgb_mat.red, sel_lin, rotate_right);
				overwrite_rotate(ph, ph->rgb_mat.green, sel_lin, rotate_right);
				overwrite_rotate(ph, ph->rgb_mat.blue, sel_lin, rotate_right);
			} else {
				overwrite_rotate(ph, ph->photo_mat, sel_lin, rotate_right);
			}
	} else {
		rot_cnt *= -1;
		for (int i = 0; i < rot_cnt; ++i)
			if (is_color(ph->type)) {
				overwrite_rotate(ph, ph->rgb_mat.red, sel_lin, rotate_left);
				overwrite_rotate(ph, ph->rgb_mat.green, sel_lin, rotate_left);
				overwrite_rotate(ph, ph->rgb_mat.blue, sel_lin, rotate_left);
			} else {
				overwrite_rotate(ph, ph->photo_mat, sel_lin, rotate_left);
			}
	}
	succes_rotate(angle);
}

//TODO create function with function as parameter

//overwrite the old matrix with the rotated one
void overwrite_rotate(photo_t *ph, int **mat, int side,
					  int **(*dir)(photo_t *, int **, int))
{
	//if the direction parameter is positive, the rotation must be done
	//to right, otherwise to the left
	int **rotated = dir(ph, mat, side);

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

	if (!rotated) {
		fprintf(stderr, "Rotated right could not pe allocated\n");
		rotated = NULL;
		free_photo(ph);
		exit(1);
	}

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

	if (!rotated) {
		fprintf(stderr, "Rotated left could not pe allocated\n");
		rotated = NULL;
		free_photo(ph);
		exit(1);
	}

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
void rotate_all(photo_t *ph, int ***mat,
				int **(*dir)(photo_t *, int **, int, int), int ch)
{
	int **rotated = dir(ph, *mat, ph->lin, ph->col);

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

	if (!rotated) {
		fprintf(stderr, "Rotated all right could not pe allocated\n");
		rotated = NULL;
		free_photo(ph);
		exit(1);
	}

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

	if (!rotated) {
		fprintf(stderr, "Rotated all left could not pe allocated\n");
		rotated = NULL;
		free_photo(ph);
		exit(1);
	}

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
