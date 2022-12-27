//Dan-Dominic Staicu 311CA 2023
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "matrix_op.h"
#include "query.h"
#include "photo_type.h"

#define TRUE 1
#define COMMAND_LENGTH 12

int main(void) 
{
	photo_t loaded_ph;
	loaded_ph.photo_mat = NULL;

	char command[COMMAND_LENGTH];
	scanf("%s", command);
	//printf("comanda: %s\nhash comanda: %d\n", command, hash_command(command));
	while(TRUE) {
		switch (hash_command(command)) {
		case 0:
			//printf("in case 0\n");
			load(&loaded_ph);
			// printf("type ousdie func: %d\n", loaded_ph.type);
			// printf("cols: %d and lins: %d outside func\n", loaded_ph.col, loaded_ph.lin);
			
			// printf("PHOTO MATRIX:\n");


			// FILE *test_photo = fopen("outbin.pgm", "wb");
			// if (!test_photo) {
			// 	printf("test photo fail\n");
			// 	return -1;
			// }

			// fprintf(test_photo, "P6\n");
			// fprintf(test_photo, "%d %d\n", loaded_ph.col/3, loaded_ph.lin);
			// fprintf(test_photo, "255");
			// for (int i = 0; i < loaded_ph.lin; ++i) {
			// 	fwrite(loaded_ph.photo_mat[i], sizeof(int), loaded_ph.col, test_photo);
			// }
			break;
		case 9:
			free_mat(loaded_ph.photo_mat, loaded_ph.lin);
			return 0;
		default:
			//in case command was not recognized
			printf("Invalid command\n");
			break;
		}
		getchar();
		scanf("%s", command);
	}
	return 0;
}
