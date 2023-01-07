// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
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
	photo_t loaded_ph; //loaded photo
	//init the matrix as NULL in order to check if anything was loaded
	init_photo(&loaded_ph);

	char command[COMMAND_LENGTH];
	scanf("%s", command);

	while (TRUE) {
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
			trash_invalid();
			error_invalid();
			break;
		}

		scanf("%s", command);
	}

	//in case while failed
	exit_editor(&loaded_ph);
	return 0;
}

// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
//check_load(ph)
