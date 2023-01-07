// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _ERRORS_H_
#define _ERRORS_H_

#include <stdio.h>

//this file includes the functions which display
//all the errors regarding to user input

void error_load(char *file_name);

void error_no_load(void);

void error_select(void);

void error_balck_white(void);

void error_apply_parameter(void);

void error_charlie(void);

void error_rotation_angle(void);

void error_square_sel(void);

void error_invalid(void);

#endif
