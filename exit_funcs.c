// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "exit_funcs.h"

//main call for EXIT command
void exit_editor(photo_t *ph)
{
	//check if any kind of photo was loaded
	if (check_load(ph)) {
		//if not, print error and contiune running the program
		error_no_load();
	}

	//else gratefully free used memory and exit the program
	//with succes status
	free_photo(ph);
	exit(0);
}
