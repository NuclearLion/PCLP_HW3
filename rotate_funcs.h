#ifndef _ROTATE_FUNCS_H_
#define _ROTATE_FUNCS_H_

#include "errors.h"
#include "succes.h"
#include "photo_type.h"
#include "matrix_op.h"
#include "utils.h"

#define TRUE 1
#define FALSE 0
#define POS 1
#define NEG -1

void rotate(photo_t *ph);

void rotate_sel(int direction);

void overwrite_rotate(photo_t *ph, int **mat, int lin, int col, int dir);

int **rotate_right(photo_t *ph, int **mat, int lin, int col);

int **rotate_left(photo_t *ph, int **mat, int lin, int col);

void rotate_all(photo_t *ph, int ***mat, int dir, int ch);

int **rot_all_r(photo_t *ph, int **mat, int lin, int col);

int **rot_all_l(photo_t *ph, int **mat, int lin, int col);

#endif
