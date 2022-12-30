//Dan-Dominic Staicu 311CA 2023
#ifndef _LOAD_FUNCS_H_
#define _LOAD_FUNCS_H_

#include <stdio.h>
#include <string.h>

#include "matrix_op.h"
#include "errors.h"
#include "photo_type.h"
#include "utils.h"
#include "succes.h"

#define COL_COLOR 3
#define FILENAME_LEN 258
#define TYPE_LEN 3
#define ZERO 0

//main call of LOAD command
void load(photo_t *ph);

//load values in photo matrix according to their magic number
void p2_load(photo_t *ph, FILE *photo_f);

void p3_load(photo_t *ph, FILE *photo_f);

void p5_load(photo_t *ph, FILE *photo_f);

void p6_load(photo_t *ph, FILE *photo_f);

#endif