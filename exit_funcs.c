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
	//with suucces status
	if (ph->photo_mat)
		free_mat(ph->photo_mat, ph->lin);
	if (ph->rgb_mat.red) {
		free_mat(ph->rgb_mat.red, ph->lin);
		free_mat(ph->rgb_mat.green, ph->lin);
		free_mat(ph->rgb_mat.blue, ph->lin);
	}
	exit(0);
}
