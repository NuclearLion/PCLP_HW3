#ifndef _SUCCES_H_
#define _SUCCES_H_

#include <stdio.h>

//print succes messages when commands were executed successfully

void succes_load(char *name_f);

void succes_save(char *name_f);

void succes_select_all(void);

void succes_equalize(void);

void succes_crop(void);

void succes_select(int *coords);

#endif