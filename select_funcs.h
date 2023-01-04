#ifndef _SELECT_FUNCS_H_
#define _SELECT_FUNCS_H_

#include <stdio.h>
#include <string.h>

#include "photo_type.h"
#include "errors.h"
#include "succes.h"
#include "utils.h"

#define ARGS_LEN 25
#define ALL_LEN 4

//main call for SELECT command
void select(photo_t *ph);

//set coords as full photo is selected
void select_all(photo_t *ph);

#endif