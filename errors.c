//Dan-Dominic Staicu 311CA 2023
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
	printf("Invalid coordinates\n");
}

void error_balck_white(void)
{
	printf("Black and white image needed");
}