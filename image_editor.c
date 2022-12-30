//Dan-Dominic Staicu 311CA 2023
#include "load_funcs.h"
#include "save_funcs.h"
#include "select_funcs.h"
#include "histo_funcs.h"
#include "equalize_funcs.h"
#include "exit_funcs.h"

#define TRUE 1
#define COMMAND_LENGTH 12

int main(void) 
{
	//declare the main memory where the photo and it's atributes are loaded
	photo_t loaded_ph;
	//init the matrix as NULL in order to check if anything was loaded
	loaded_ph.photo_mat = NULL;

	char command[COMMAND_LENGTH];
	scanf("%s", command);

	while(TRUE) {
		//"hash" the command into a code in order to be able to use switch
		switch (hash_command(command)) {
		case 0:
			load(&loaded_ph);
			//getchar();
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
		case 7:
			save(&loaded_ph);
			break;
		case 8:
			exit_editor(&loaded_ph);
			break;
		default:
			//in case command was not recognized
			printf("Invalid command\n");
			break;
		}

		scanf("%s", command);
	}
	return 0;
}
