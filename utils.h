//Dan-Dominic Staicu 311CA 2023
#ifndef _UTILS_C_
#define _UTILS_C_

#include <string.h>
#include <stdio.h>

#include "photo_type.h"

//hash the command to a int in order to use switch statement
int hash_command(char *command);

//hash the type in order to keep an int
int hash_type(char *type_name);

#endif