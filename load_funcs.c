//Dan-Dominic Staicu 311CA 2023
#include "load_funcs.h"

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

	//print succes message in the end
	succes_load(name);
	//close the file
	fclose(photo_f);
}


void p2_load(photo_t *ph, FILE *photo_f)
{
	ph->photo_mat = alloc_matrix(ph->lin, ph->col);
	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			fscanf(photo_f, "%d", &ph->photo_mat[i][j]);
}

void p3_load(photo_t *ph, FILE *photo_f)
{
	ph->col *= COL_COLOR;
	ph->photo_mat = alloc_matrix(ph->lin, ph->col);
	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			fscanf(photo_f, "%d", &ph->photo_mat[i][j]);
}

void p5_load(photo_t *ph, FILE *photo_f)
{
	ph->photo_mat = alloc_matrix(ph->lin, ph->col);

	//even I dont know what is this
	char garbage;
	fread(&garbage, sizeof(char), 1, photo_f);

	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			fread(&ph->photo_mat[i][j], sizeof(char), 1, photo_f);
}

void p6_load(photo_t *ph, FILE *photo_f)
{
	ph->col *= COL_COLOR;
	ph->photo_mat = alloc_matrix(ph->lin, ph->col);
	
	//even I dont know what is this
	char garbage;
	fread(&garbage, sizeof(char), 1, photo_f);

	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			fread(&ph->photo_mat[i][j], sizeof(char), 1, photo_f);
}
