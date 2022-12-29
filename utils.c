//Dan-Dominic Staicu 311CA 2023
#include "utils.h"


int hash_command(char *command)
{
	
	if(strcmp(command, "LOAD") == 0)
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
	//for case default
	return -1;
}

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

void swap_int(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *b ^ *a;
	*a = *a ^ *b;
}
