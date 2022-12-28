//Dan-Dominic Staicu 311CA 2023
#ifndef _PHOTO_TYPE_H_
#define _PHOTO_TYPE_H_

typedef struct {
	//coordinates of selection
	int top_x, top_y;
	int bot_x, bot_y;

	//number of columns and lines
	int col, lin;

	//P2 P3 P5 P6
	int type;

	//the actual photo as a matrix
	int **photo_mat;
} photo_t;

#endif
