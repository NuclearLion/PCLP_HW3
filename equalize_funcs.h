// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _EQUALIZE_FUNCS_H_
#define _EQUALIZE_FUNCS_H_

#include <stdio.h>
#include <math.h>

#include "photo_type.h"
#include "errors.h"
#include "succes.h"
#include "utils.h"

#define VALS 256
#define ZERO 0
#define MAX_VAL 255

void equalize(photo_t *ph);

int eq_pixel(int pixel, long long area, int *pixel_frq);

#endif
