#include "load_funcs.h"

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
	for (int i = 0; i < ph->lin; ++i) {
		fread(ph->photo_mat[i], sizeof(int), ph->col, photo_f);
	}
}

void p6_load(photo_t *ph, FILE *photo_f)
{
	ph->col *= COL_COLOR;
	ph->photo_mat = alloc_matrix(ph->lin, ph->col);
	for (int i = 0; i < ph->lin; ++i) {
		fread(ph->photo_mat[i], sizeof(int), ph->col, photo_f);
	}
}