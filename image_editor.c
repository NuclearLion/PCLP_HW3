//Dan-Dominic Staicu 311CA 2023
#include "load_funcs.h"
#include "save_funcs.h"
#include "select_funcs.h"
#include "histo_funcs.h"
#include "equalize_funcs.h"
#include "exit_funcs.h"
#include "crop_funcs.h"
#include "apply_funcs.h"
#include "rotate_funcs.h"

#define COMMAND_LENGTH 12

int main(void)
{
	//declare the main memory where the photo and it's atributes are loaded
	photo_t loaded_ph;
	//init the matrix as NULL in order to check if anything was loaded
	loaded_ph.photo_mat = NULL;
	loaded_ph.rgb_mat.red = NULL;
	loaded_ph.rgb_mat.green = NULL;
	loaded_ph.rgb_mat.blue = NULL;
	loaded_ph.lin = 0;
	loaded_ph.col = 0;
	loaded_ph.bot_x = 0;
	loaded_ph.bot_y = 0;
	loaded_ph.top_x = 0;
	loaded_ph.top_y = 0;
	loaded_ph.type = 0;

	char command[COMMAND_LENGTH];
	scanf("%s", command);

	while(TRUE) {
		//"hash" the command into a code in order to be able to use switch
		switch (hash_command(command)) {
		case 0:
			load(&loaded_ph);
			break;
		case 1:
			select(&loaded_ph);
			break;
		case 2:
			histogram(&loaded_ph);
			break;
		case 3:
			equalize(&loaded_ph);
			break;
		case 4:
			rotate(&loaded_ph);
			break;
		case 5:
			crop(&loaded_ph);
			break;
		case 6:
			apply(&loaded_ph);
			break;
		case 7:
			save(&loaded_ph);
			break;
		case 8:
			exit_editor(&loaded_ph);
			break;
		default:
			//in case command was not recognized
			error_invalid();
			break;
		}

		scanf("%s", command);
	}

	exit_editor(&loaded_ph);
	return 0;
}


// diff -w -y ./tasks/image_editor/tests/00-image_editor/00-image_editor.ref ./tasks/image_editor/tests/00-image_editor/00-image_editor.out

// watch test 28 for memups valgrind