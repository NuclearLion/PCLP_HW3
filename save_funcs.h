// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _SAVE_FUNCS_H_
#define _SAVE_FUNCS_H_

#include <stdio.h>

#include "photo_type.h"
#include "utils.h"
#include "errors.h"
#include "matrix_op.h"
#include "succes.h"

#define FILENAME_LEN 258
#define NAME_AND_ASCII 263
#define TRUE 1
#define FALSE 0
#define INTERPRET_COLS 3
#define BYTE 1

//main call of SAVE command
void save(photo_t *ph);

//creating the new file and writing in it
void save_f(photo_t *ph, char *new_f_name, int bool_ascii);

//unhash type in order to save the file
void print_type(FILE *print_f, int type);

#endif
