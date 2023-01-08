// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "load_funcs.h"

//main call of LOAD command
void load(photo_t *ph)
{
	//read the given filename
	char name[FILENAME_LEN];
	scanf("%s", name);

	//check if any mat was loaded before (RGB or Black and White)
	if (ph->rgb_mat.red) {
		free_mat(ph->rgb_mat.red, ph->lin);
		free_mat(ph->rgb_mat.green, ph->lin);
		free_mat(ph->rgb_mat.blue, ph->lin);

		ph->rgb_mat.red = NULL;
		ph->rgb_mat.green = NULL;
		ph->rgb_mat.blue = NULL;
	}

	if (ph->photo_mat) {
		free_mat(ph->photo_mat, ph->lin);

		ph->photo_mat = NULL;
	}

	//try to open the file
	//checker forced me into doing this horrible star placement, sorry
	FILE * photo_file = fopen(name, "rb");
	if (!photo_file) {
		// check if the file could be opened print the error if it couldn't
		error_load(name);
		return;
	}

	//read the magic number
	char type[TYPE_LEN];
	memset(type, ZERO, sizeof(type));
	fscanf(photo_file, "%s", type);

	//save the magic number as a hashed type (in order to keep it as int)
	ph->type = hash_type(type);

	//read and save dimensions of photo
	//read only (%d) ints in order to step over the comments
	while (fscanf(photo_file, "%d%d", &ph->col, &ph->lin) != 2) {
		char trash[TRASH_LEN];
		fscanf(photo_file, "%s", trash);
	}

	//step over the 255 value when reading, already know max value is 255
	//read only (%d) ints in order to step over the comments
	int _255;
	while (fscanf(photo_file, "%d", &_255) != 1) {
		char trash[TRASH_LEN];
		fscanf(photo_file, "%s", trash);
	} //after this the coursor pointer stays at the end of 255

	//acording to the magic number, load the photo as a matrix
	switch (ph->type) {
	case 2:
		p2_load(ph, photo_file);
		break;
	case 3:
		p3_load(ph, photo_file);
		break;
	case 5:
		p5_load(ph, photo_file);
		break;
	case 6:
		p6_load(ph, photo_file);
		break;
	default:
		break;
	}

	//init the select zone as SELECT ALL
	//the whole picture is selected
	select_all(ph);

	//print succes message in the end
	succes_load(name);
	//close the file
	fclose(photo_file);
}

void p2_load(photo_t *ph, FILE *photo_f)
{
	ph->photo_mat = alloc_matrix(ph->lin, ph->col);

	//check if memory could be allocated
	check_load_alloc(ph);

	//read the actual values as text and load them in memory
	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			fscanf(photo_f, "%d", &ph->photo_mat[i][j]);
}

void p3_load(photo_t *ph, FILE *photo_f)
{
	//alloc memory for every colour matrix
	ph->rgb_mat.red = alloc_matrix(ph->lin, ph->col);
	ph->rgb_mat.green = alloc_matrix(ph->lin, ph->col);
	ph->rgb_mat.blue = alloc_matrix(ph->lin, ph->col);

	//check if memory could be allocated
	check_load_alloc(ph);

	//read the actual values as text and load them in memory
	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j) {
			fscanf(photo_f, "%d", &ph->rgb_mat.red[i][j]);
			fscanf(photo_f, "%d", &ph->rgb_mat.green[i][j]);
			fscanf(photo_f, "%d", &ph->rgb_mat.blue[i][j]);
		}
}

void p5_load(photo_t *ph, FILE *photo_f)
{
	ph->photo_mat = alloc_matrix(ph->lin, ph->col);

	//check if memory could be allocated
	check_load_alloc(ph);

	//step over the endline after the 255 max value
	char garbage;
	fread(&garbage, 1, 1, photo_f);

	//read the actual values as binary and load them in memory
	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			fread(&ph->photo_mat[i][j], 1, 1, photo_f);
}

void p6_load(photo_t *ph, FILE *photo_f)
{
	//alloc memory for every colour matrix
	ph->rgb_mat.red = alloc_matrix(ph->lin, ph->col);
	ph->rgb_mat.green = alloc_matrix(ph->lin, ph->col);
	ph->rgb_mat.blue = alloc_matrix(ph->lin, ph->col);

	//check if memory could be allocated
	check_load_alloc(ph);

	//step over the endline after the 255 max value
	char garbage;
	fread(&garbage, 1, 1, photo_f);

	//read the actual values as binary and load them in memory
	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j) {
			//todo 1 bcs of sizeof char can be different on systems
			fread(&ph->rgb_mat.red[i][j], 1, 1, photo_f);
			fread(&ph->rgb_mat.green[i][j], 1, 1, photo_f);
			fread(&ph->rgb_mat.blue[i][j], 1, 1, photo_f);
		}
}
