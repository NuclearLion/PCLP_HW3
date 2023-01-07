// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#ifndef _PHOTO_TYPE_H_
#define _PHOTO_TYPE_H_

//struct to define 3 more matrixes, each for a color channel in a RGB photo
typedef struct {
	int **red;
	int **green;
	int **blue;
} rgb_t;

//struct to define a point in a 2D plan
typedef struct {
	int x, y;
} coords_point_t;

//struct to define a photo and it's characteristics
typedef struct {
	//coordinates of selection
	coords_point_t top;
	coords_point_t bot;

	//number of columns and lines
	int col, lin;

	//magic number (P2 P3 P5 P6) as an int
	int type;

	//the actual photo as a matrix
	int **photo_mat;
	rgb_t rgb_mat;
} photo_t;

#endif
