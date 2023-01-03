#ifndef _APPLY_FUNCS_H_
#define _APPLY_FUNCS_H_

#include <stdio.h>

#include "photo_type.h"
#include "succes.h"
#include "errors.h"
#include "utils.h"
#include "matrix_op.h"

#define KERNEL_LENGTH 14
#define P2 2
#define P5 5

void apply(photo_t *ph);

void edge(photo_t *ph);

#endif
