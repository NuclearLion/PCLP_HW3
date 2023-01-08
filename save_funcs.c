// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "save_funcs.h"

//main call of SAVE command
void save(photo_t *ph)
{
	char name_ascii[NAME_AND_ASCII];
	//init name with \0
	memset(name_ascii, FALSE, sizeof(name_ascii));

	getchar();
	//read parameters of SAVE as one, in order to count them later
	fgets(name_ascii, NAME_AND_ASCII, stdin);
	char *ptr = strtok(name_ascii, " ");

	//check if any photo was loaded
	if (check_load(ph)) {
		error_no_load();
		return;
	}

	//save the name of file which is the first parameter
	char *new_name = ptr;
	int len_new_name = strlen(new_name);

	//count how many parameters were read
	int word_cnt = 0;
	while (ptr) {
		word_cnt++;
		ptr = strtok(NULL, " ");
	}

	//if there is only one parameter, need to cut the \n from filename
	if (word_cnt == 1)
		new_name[len_new_name - 1] = '\0';

	//check if ascii parameter was read
	if (word_cnt == 2)
		save_f(ph, new_name, TRUE);
	else
		save_f(ph, new_name, FALSE);

	//display succes message at the end
	succes_save(new_name);
}

//creating the new file and writing in it
void save_f(photo_t *ph, char *new_f_name, int bool_ascii)
{
	//create new file for the new photo
	FILE *photo_f = fopen(new_f_name, "wb");
	if (!photo_f) {
		printf("something went wrong while creating the save file\n");
		free_photo(ph);
	}

	//write the magic number acording to SAVE instruction
	if (bool_ascii) {
		if (!is_color(ph->type))
			print_type(photo_f, P2);
		else
			print_type(photo_f, P3);
	} else {
		if (!is_color(ph->type))
			print_type(photo_f, P5);
		else
			print_type(photo_f, P6);
	}

	fprintf(photo_f, "%d %d\n", ph->col, ph->lin);

	//print the 255 max value
	fprintf(photo_f, "255\n");

	//check if ascii parameter was read and write in file according to it
	if (bool_ascii)
		if (!is_color(ph->type))
			for (int i = 0; i < ph->lin; ++i) {
				for (int j = 0; j < ph->col; ++j)
					fprintf(photo_f, "%d ", ph->photo_mat[i][j]);
				fprintf(photo_f, "\n");
			}
		else
			for (int i = 0; i < ph->lin; ++i) {
				for (int j = 0; j < ph->col; ++j) {
					fprintf(photo_f, "%d ", ph->rgb_mat.red[i][j]);
					fprintf(photo_f, "%d ", ph->rgb_mat.green[i][j]);
					fprintf(photo_f, "%d ", ph->rgb_mat.blue[i][j]);
				}
				fprintf(photo_f, "\n");
			}
	else
		if (!is_color(ph->type))
			for (int i = 0; i < ph->lin; ++i)
				for (int j = 0; j < ph->col; ++j)
					fwrite(&ph->photo_mat[i][j], 1, 1, photo_f);
		else
			for (int i = 0; i < ph->lin; ++i) {
				for (int j = 0; j < ph->col; ++j) {
					fwrite(&ph->rgb_mat.red[i][j], 1, 1, photo_f);
					fwrite(&ph->rgb_mat.green[i][j], 1, 1, photo_f);
					fwrite(&ph->rgb_mat.blue[i][j], 1, 1, photo_f);
				}
			}

	//close the saved file
	fclose(photo_f);
}

//unhash type in order to save the file
void print_type(FILE *print_f, int type)
{
	switch (type) {
	case 2:
		fprintf(print_f, "P2\n");
		break;
	case 3:
		fprintf(print_f, "P3\n");
		break;
	case 5:
		fprintf(print_f, "P5\n");
		break;
	case 6:
		fprintf(print_f, "P6\n");
		break;
	default:
		fprintf(stderr, "given type doesn't exit\n");
		break;
	}
}
