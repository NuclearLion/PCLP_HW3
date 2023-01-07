// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "errors.h"

void error_load(char *file_name)
{
	printf("Failed to load %s\n", file_name);
}

void error_no_load(void)
{
	printf("No image loaded\n");
}

void error_select(void)
{
	printf("Invalid set of coordinates\n");
}

void error_balck_white(void)
{
	printf("Black and white image needed\n");
}

void error_apply_parameter(void)
{
	printf("APPLY parameter invalid\n");
}

void error_charlie(void)
{
	printf("Easy, Charlie Chaplin\n");
}

void error_rotation_angle(void)
{
	printf("Unsupported rotation angle\n");
}

void error_square_sel(void)
{
	printf("The selection must be square\n");
}

void error_invalid(void)
{
	printf("Invalid command\n");
}
