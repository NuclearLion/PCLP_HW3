// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _CROP_FUNCS_H_
#define _CROP_FUNCS_H_

#include "succes.h"
#include "errors.h"
#include "photo_type.h"
#include "matrix_op.h"
#include "select_funcs.h"

void crop(photo_t *ph);

int **crop_mat(int **mat, photo_t *ph, int new_lin, int new_col);

#endif
