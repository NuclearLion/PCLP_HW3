#ifndef _APPLY_FUNCS_H_
#define _APPLY_FUNCS_H_

#include <stdio.h>

#include "photo_type.h"
#include "succes.h"
#include "errors.h"
#include "utils.h"
#include "matrix_op.h"

#define KERNEL_LENGTH 14
#define KER_MAT_DIM 3

void apply(photo_t *ph);

void edge(photo_t *ph);

void sharpen(photo_t *ph);

void box_blur(photo_t *ph);

void gaussian_blur(photo_t *ph);

void kern(int **kernel, int **mat, photo_t *ph, int coef);

int **apply_kern(photo_t *ph, int **ch, int **ker, int lin, int col, int coef);

#endif
