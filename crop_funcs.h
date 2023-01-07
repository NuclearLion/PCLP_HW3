// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _CROP_FUNCS_H_
#define _CROP_FUNCS_H_

#include "succes.h"
#include "errors.h"
#include "photo_type.h"
#include "matrix_op.h"
#include "select_funcs.h"

//main call of crop command
void crop(photo_t *ph);

//alloc a new memory area and fill it with values inside
//the selection from the old matrix
int **crop_mat(int **mat, photo_t *ph, int new_lin, int new_col);

#endif
