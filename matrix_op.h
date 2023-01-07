// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _MATRIX_OP_H_
#define _MATRIX_OP_H_

#include <stdio.h>
#include <stdlib.h>

#include "photo_type.h"

//shamelessly reused my own functions from my_octave because my code is
//easily reusable and scalable

//alloc memory for a new matrix
int **alloc_matrix(int n, int m);

//free memory of a mat
void free_mat(int **mat, int n);

#endif
