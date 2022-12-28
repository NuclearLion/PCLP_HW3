//Dan-Dominic Staicu 311CA 2023
#include "load_funcs.h"

void load(photo_t *ph)
{
	char name[FILENAME_LEN];
	scanf("%s", name);

	FILE *photo_f = fopen(name, "rb");
	if (!photo_f) {
		error_load(name);
		return;
	}

	char type[TYPE_LEN];
	memset(type, ZERO, sizeof(type));
	// for (int i = 0; type[i] != '\0'; ++i)
	// 	printf("ceva%c", type[i]);
	
	//fread(type, sizeof(type), 1, photo_f);
	fscanf(photo_f, "%s", type);
	
	// for (int i = 0; type[i] != '\0'; ++i)
	// 	printf("%c", type[i]);
	// printf("sfarsit for\n");
	
	//printf("TYPE: %s\n", type);
	ph->type = hash_type(type);

	fscanf(photo_f, "%d%d", &ph->col, &ph->lin);

	//step over the 255 value
	int _255;
	fscanf(photo_f, "%d", &_255);

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

	succes_load(name);
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
	// for (int i = 0; i < ph->lin; ++i) {
	// 	fread(ph->photo_mat[i], sizeof(int), ph->col, photo_f);
	// }

	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			fread(&ph->photo_mat[i][j], sizeof(char), 1, photo_f);

	// for (int i = 0; i < ph->lin; ++i)
	// 	for (int j = 0; j < ph->col; ++j)
	// 		fscanf(photo_f, "%d", &ph->photo_mat[i][j]);
}

void p6_load(photo_t *ph, FILE *photo_f)
{
	ph->col *= COL_COLOR;
	ph->photo_mat = alloc_matrix(ph->lin, ph->col);
	// for (int i = 0; i < ph->lin; ++i) {
	// 	fread(ph->photo_mat[i], sizeof(int), ph->col, photo_f);
	// }
	//getchar();
	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			fread(&ph->photo_mat[i][j], sizeof(char), 1, photo_f);
}
