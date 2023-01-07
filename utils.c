// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "utils.h"

//hash the command to a int in order to use switch statement
int hash_command(char *command)
{
	if (strcmp(command, "LOAD") == 0)
		return 0;
	if (strcmp(command, "SELECT") == 0)
		return 1;
	if (strcmp(command, "HISTOGRAM") == 0)
		return 2;
	if (strcmp(command, "EQUALIZE") == 0)
		return 3;
	if (strcmp(command, "ROTATE") == 0)
		return 4;
	if (strcmp(command, "CROP") == 0)
		return 5;
	if (strcmp(command, "APPLY") == 0)
		return 6;
	if (strcmp(command, "SAVE") == 0)
		return 7;
	if (strcmp(command, "EXIT") == 0)
		return 8;
	//for case default in switch statement
	return -1;
}

//hash the type in order to keep an int
int hash_type(char *type_name)
{
	if (strcmp(type_name, "P2") == 0)
		return 2;
	if (strcmp(type_name, "P3") == 0)
		return 3;
	if (strcmp(type_name, "P5") == 0)
		return 5;
	if (strcmp(type_name, "P6") == 0)
		return 6;
	return -1;
}

//swap 2 ints using XOR
void swap_int(int *a, int *b)
{
	//maybe insert documentation from wikipedia
	*a = *a ^ *b;
	*b = *b ^ *a;
	*a = *a ^ *b;
}

//clamp a double value between 0 and 255
double clamp(double pixel)
{
	double minimum = 0;
	double maximum = 255;
	if (pixel > maximum)
		return maximum;
	if (pixel < minimum)
		return minimum;
	return pixel;
}

//clamp a int value between 0 and 255
int clamp_i(int pixel)
{
	int minimum = 0;
	int maximum = 255;
	if (pixel > maximum)
		return maximum;
	if (pixel < minimum)
		return minimum;
	return pixel;
}

//hash values of apply parameters in order to use switch statement
int hash_apply(char *ker)
{
	if (strcmp(ker, "EDGE") == 0)
		return 0;
	if (strcmp(ker, "SHARPEN") == 0)
		return 1;
	if (strcmp(ker, "BLUR") == 0)
		return 2;
	if (strcmp(ker, "GAUSSIAN_BLUR") == 0)
		return 3;
	return -1;
}

//check if given photo is colour or not according to it's magic word
int is_color(int type)
{
	if (type == P2 || type == P5)
		return 0;
	return 1;
}

//step over invalid text
void trash_invalid(void)
{
	char trash_[TRASH_LEN];
	fgets(trash_, TRASH_LEN, stdin);
}

//check if any image is loaded
int check_load(photo_t *ph)
{
	if (!ph->photo_mat && !ph->rgb_mat.red)
		return 1;
	return 0;
}

//init the matrix as NULL in order to easily check if anything was loaded
void init_photo(photo_t *loaded_ph)
{
	loaded_ph->photo_mat = NULL;
	loaded_ph->rgb_mat.red = NULL;
	loaded_ph->rgb_mat.green = NULL;
	loaded_ph->rgb_mat.blue = NULL;
	loaded_ph->lin = 0;
	loaded_ph->col = 0;
	loaded_ph->bot_x = 0;
	loaded_ph->bot_y = 0;
	loaded_ph->top_x = 0;
	loaded_ph->top_y = 0;
	loaded_ph->type = 0;
}

// save the count of pixels in a given frequency array
void freq_counter(photo_t *ph, int *pixel_freq)
{
	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			++pixel_freq[ph->photo_mat[i][j]];
}
