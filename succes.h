// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _SUCCES_H_
#define _SUCCES_H_

#include <stdio.h>

//functions that print succes messages when commands were executed successfully

void succes_load(char *name_f);

void succes_save(char *name_f);

void succes_select_all(void);

void succes_equalize(void);

void succes_crop(void);

void succes_select(int x1, int y1, int x2, int y2);

void succes_apply(char *parameter);

void succes_rotate(int angle);

#endif
