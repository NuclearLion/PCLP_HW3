//Dan-Dominic Staicu 311CA 2023
#include "load_funcs.h"

//todo read photos with if (fscanf("%d")) in order to read only ints and use
//fscanf("%s") in order to step over the unnecesarry comments


void load(photo_t *ph)
{
	//read the given filename
	char name[FILENAME_LEN];
	scanf("%s", name);

	//try to open the file
	FILE *photo_f = fopen(name, "rb");
	//check if the file could be opened
	if (!photo_f) {
		//print the error if it couldn't
		error_load(name);
		return;
	}

	//read the magic number
	char type[TYPE_LEN];
	memset(type, ZERO, sizeof(type));
	fscanf(photo_f, "%s", type);
	//save the magic number as a hashed type (in order to keep it as int)
	ph->type = hash_type(type);

	//read and save dimensions of photo
	fscanf(photo_f, "%d%d", &ph->col, &ph->lin);

	//step over the 255 value when reading
	int _255;
	fscanf(photo_f, "%d", &_255);
	//after this the coursor pointer stays at the end of 255

	//acording to the magic number, load the photo as a matrix
	switch (ph->type)
	{
	case 2:
		p2_load(ph, photo_f);
		break;
	case 3:
		p3_load(ph, photo_f);
		break;
	case 5:
		p5_load(ph, photo_f);
		break;
	case 6:
		p6_load(ph, photo_f);
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
	fclose(photo_f);
}


void p2_load(photo_t *ph, FILE *photo_f)
{
	ph->photo_mat = alloc_matrix(ph->lin, ph->col);

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
