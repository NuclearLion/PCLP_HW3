#include "exit_funcs.h"

void exit_editor(photo_t *ph)
{
	//check if any kind of photo was loaded
	if (ph->photo_mat == NULL && ph->rgb_mat.red == NULL) {
		//if not, print error and contiune running the program
		error_no_load();
		getchar();
	} else {
		//else graciously free used memory and exit the program 
		//with suucces status
		if (ph->photo_mat != NULL)
			free_mat(ph->photo_mat, ph->lin);
		else {
			free_mat(ph->rgb_mat.red, ph->lin);
			free_mat(ph->rgb_mat.green, ph->lin);
			free_mat(ph->rgb_mat.blue, ph->lin);
		}
		exit(0);
	}
}
