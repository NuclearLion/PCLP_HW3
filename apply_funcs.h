// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _APPLY_FUNCS_H_
#define _APPLY_FUNCS_H_

#include <stdio.h>

#include "photo_type.h"
#include "succes.h"
#include "errors.h"
#include "utils.h"
#include "matrix_op.h"

#define KERNEL_LENGTH 20
#define KER_MAT_DIM 3

//main call for apply command in order to validate input and call the right
//effect fucntion
void apply(photo_t *ph);

//overwrite old part of a color channel matrix with the newly created matrix
//with the effect applied
void kern(int kernel[][3], int **color_ch, photo_t *ph, int coef);

//apply the kernel matrix over the selection from a photo in
//a new matrix and return it
int **apply_kern(photo_t *ph, int **ch, int ker[][3],
				 int lin, int col, int coef);

//the 4 following create necesary matrix and coefficients
//and call apply_kern with them according to the effect
void edge(photo_t *ph);

void sharpen(photo_t *ph);

void box_blur(photo_t *ph);

void gaussian_blur(photo_t *ph);

#endif
