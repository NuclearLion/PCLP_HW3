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

void succes_select(int *coords)
{
	printf("Selected ");
	for (int i = 0; i < 4; ++i)
		printf("%d ", coords[i]);
	printf("\n");
}

void succes_apply(char *parameter)
{
	printf("APPLY %s done\n", parameter);
}

void succes_rotate(int angle)
{
	printf("Rotated %d\n", angle);
}
