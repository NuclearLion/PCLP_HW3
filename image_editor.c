//Dan-Dominic Staicu 311CA 2023
#include "load_funcs.h"
#include "save_funcs.h"
#include "select_funcs.h"
#include "histo_funcs.h"

#define TRUE 1
#define COMMAND_LENGTH 12

int main(void) 
{
	photo_t loaded_ph;
	loaded_ph.photo_mat = NULL;

	char command[COMMAND_LENGTH];
	scanf("%s", command);

	while(TRUE) {
		switch (hash_command(command)) {
		case 0:
			load(&loaded_ph);
			getchar();
			break;
		case 1:
			select(&loaded_ph);
			break;
		case 2:
			histogram(&loaded_ph);
			break;
		case 7:
			save(&loaded_ph);
			break;
		case 8:
			if (loaded_ph.photo_mat == NULL) {
				error_no_load();
				getchar();
			} else {
				free_mat(loaded_ph.photo_mat, loaded_ph.lin);
				return 0;
			}
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
