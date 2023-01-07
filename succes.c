// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "succes.h"

void succes_load(char *name_f)
{
	printf("Loaded %s\n", name_f);
}

void succes_save(char *name_f)
{
	printf("Saved %s\n", name_f);
}

void succes_select_all(void)
{
	printf("Selected ALL\n");
}

void succes_equalize(void)
{
	printf("Equalize done\n");
}

void succes_crop(void)
{
	printf("Image cropped\n");
}

void succes_select(int x1, int y1, int x2, int y2)
{
	printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
}

void succes_apply(char *parameter)
{
	printf("APPLY %s done\n", parameter);
}

void succes_rotate(int angle)
{
	printf("Rotated %d\n", angle);
}
