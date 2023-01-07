// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _HISTO_FUNCS_H_
#define _HISTO_FUNCS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "photo_type.h"
#include "errors.h"
#include "utils.h"

#define VALS 256
#define ZERO 0

void histogram(photo_t *ph);

#endif
