#ifndef _LOAD_FUNCS_H_
#define _LOAD_FUNCS_H_

#include <stdio.h>

#include "photo_type.h"
#include "matrix_op.h"

#define COL_COLOR 3

void p2_load(photo_t *ph, FILE *photo_f);

void p3_load(photo_t *ph, FILE *photo_f);

void p5_load(photo_t *ph, FILE *photo_f);

void p6_load(photo_t *ph, FILE *photo_f);

#endif