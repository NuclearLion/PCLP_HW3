#ifndef _SAVE_FUNCS_H_
#define _SAVE_FUNCS_H_

#include <stdio.h>

#include "photo_type.h"
#include "utils.h"
#include "errors.h"
#include "succes.h"

#define FILENAME_LEN 258
#define NAME_AND_ASCII 263
#define TRUE 1
#define FALSE 0

void save(photo_t *ph);

void save_f(photo_t *ph, char *new_f_name, int bool_ascii);

//unhash type in order to save the file
void print_type(FILE *print_f, int type);

//because P3 and P6 actually have a matrix with dimension of 3 * no_cols,
//have to treat separately the cases where the no_cols in matrix is real
//and when it has to be /3
void print_dim(FILE *print_f, photo_t *ph);

#endif
