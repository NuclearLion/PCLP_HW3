//Dan-Dominic Staicu 311CA 2023
#ifndef _MATRIX_OP_H_
#define _MATRIX_OP_H_

#include <stdio.h>
#include <stdlib.h>

#include "photo_type.h"

int **alloc_matrix(int n, int m);

void free_mat(int **mat, int n);

#endif