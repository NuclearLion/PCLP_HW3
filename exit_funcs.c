#include "exit_funcs.h"

void exit_editor(photo_t *ph)
{
	//check if any photo was loaded
	if (ph->photo_mat == NULL) {
		//if not, print error and contiune running the program
		error_no_load();
		getchar();
	} else {
		//else graciously free used memory and exit the program 
		//with suucces status
		free_mat(ph->photo_mat, ph->lin);
		exit(0);
	}
}
