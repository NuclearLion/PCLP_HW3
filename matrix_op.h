// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _MATRIX_OP_H_
#define _MATRIX_OP_H_

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "photo_type.h"

//alloc memory for a new matrix
int **alloc_matrix(int n, int m);

//free memory of a mat
void free_mat(int **mat, int n);

//check if memory could be allocated in load funcs
void check_load_alloc(photo_t *ph);

void free_photo(photo_t *ph);

#endif
