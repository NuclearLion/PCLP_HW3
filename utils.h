// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _UTILS_C_
#define _UTILS_C_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "photo_type.h"

#define TRASH_LEN 100
#define P2 2
#define P3 3
#define P5 5
#define P6 6

//hash the command to a int in order to use switch statement
int hash_command(char *command);

//hash the type in order to keep an int
int hash_type(char *type_name);

//swap 2 ints using XOR
void swap_int(int *a, int *b);

//clamp a double value between 0 and 255
double clamp(double pixel);

//clamp a int value between 0 and 255
int clamp_i(int pixel);

//hash values of apply parameters in order to use switch statement
int hash_apply(char *ker);

//check if given photo is colour or not according to it's magic word
int is_color(int type);

//step over invalid text
void trash_invalid(void);

//check if any image is loaded
int check_load(photo_t *ph);

//init the matrix as NULL in order to easily check if anything was loaded
void init_photo(photo_t *loaded_ph);

// save the count of pixels in a given frequency array
void freq_counter(photo_t *ph, int *pixel_freq);

#endif
