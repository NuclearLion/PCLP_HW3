// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _ROTATE_FUNCS_H_
#define _ROTATE_FUNCS_H_

#include "errors.h"
#include "succes.h"
#include "photo_type.h"
#include "matrix_op.h"
#include "utils.h"

#define TRUE 1
#define FALSE 0

//main call for ROTATE command
void rotate(photo_t *ph);

//overwrite the old matrix with the rotated one
void overwrite_rotate(photo_t *ph, int **mat, int side,
					  int **(*dir)(photo_t *, int **, int));

//create a new square matrix with values from
//the selection in the old one, but rotated to right
int **rotate_right(photo_t *ph, int **mat, int side);

//create a new square matrix with values from
//the selection in the old one, but rotated to left
int **rotate_left(photo_t *ph, int **mat, int side);

void rotate_all(photo_t *ph, int ***mat,
				int **(*dir)(photo_t *, int **, int, int), int ch);

//alloc and fill a new rotated to right mat
int **rot_all_r(photo_t *ph, int **mat, int lin, int col);

//alloc and fill a new rotated to left mat
int **rot_all_l(photo_t *ph, int **mat, int lin, int col);

#endif
