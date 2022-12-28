#include "save_funcs.h"

// https://stackoverflow.com/questions/2663559/optional-read-from-stdin-in-c
void save(photo_t *ph)
{
	if (ph->photo_mat == NULL) {
		error_no_load();
		return;
	}

	char name_ascii[NAME_AND_ASCII];
	memset(name_ascii, FALSE, sizeof(name_ascii));
	//scanf("%s", new_name);

	// if (sscanf(name_ascii, "%s %s", new_name, ascii) == 2) {
	// 	printf("some dumb message name : %s, ascii: yes: %s\n", new_name, ascii);
	// } else if (sscanf(name_ascii, "%s", new_name) == 1) {
	// 	printf("no ascii here just the new name: %s\n", new_name);
	// } else {
	// 	printf("how did it even get here???\n");
	// }
	getchar();
	fgets(name_ascii, NAME_AND_ASCII, stdin);
	char *ptr = strtok(name_ascii, " ");
	char *new_name = ptr;
	// printf("newname: %s\n", new_name);
	int word_cnt = 0;
	while (ptr != NULL) {
		//printf("%s\n", ptr);
		word_cnt++;
		ptr = strtok(NULL, " ");
	}
	// printf("newname2: %s\n", new_name);

	if(word_cnt == 2)
		save_f(ph, new_name, TRUE);
	else
		save_f(ph, new_name, FALSE);

	succes_save(new_name);
}

void save_f(photo_t *ph, char *new_f_name, int bool_ascii)
{
	FILE *text_f = fopen(new_f_name, "wb");
	if (!text_f) {
		printf("something went wrong while creating the save file\n");
		return;
	}

	if (bool_ascii) {
		if (ph->type == 2 || ph->type == 5)
			print_type(text_f, 2);
		else 
			print_type(text_f, 3);
	} else {
		if (ph->type == 2 || ph->type == 5)
			print_type(text_f, 5);
		else 
			print_type(text_f, 6);
	}

	print_dim(text_f, ph);
	fprintf(text_f, "255\n");

	if (bool_ascii) {
		for (int i = 0; i < ph->lin; ++i) {
			for (int j = 0; j < ph->col; ++j)
				fprintf(text_f, "%d ", ph->photo_mat[i][j]);
			fprintf(text_f, "\n");
		}
	} else {
		// fprintf(test_photo, "P6\n");
			// fprintf(test_photo, "%d %d\n", loaded_ph.col/3, loaded_ph.lin);
			// fprintf(test_photo, "255");
			// for (int i = 0; i < loaded_ph.lin; ++i) {
			// 	fwrite(loaded_ph.photo_mat[i], sizeof(int), loaded_ph.col, test_photo);
			// }
		for (int i = 0; i < ph->lin; ++i)
			fwrite(ph->photo_mat[i], sizeof(int), ph->col, text_f);
	}

	fclose(text_f);	
}

void print_type(FILE *print_f, int type)
{
	switch (type)
	{
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

void print_dim(FILE *print_f, photo_t *ph)
{
	if (ph->type == 2 || ph->type == 5)
		fprintf(print_f, "%d %d\n", ph->col, ph->lin);
	else if (ph->type == 3 || ph->type == 6)
		fprintf(print_f, "%d %d\n", ph->col / 3, ph->lin);
}
