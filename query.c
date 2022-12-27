#include "query.h"

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
	
	printf("TYPE: %s\n", type);
	ph->type = hash_type(type);

	fscanf(photo_f, "%d%d", &ph->col, &ph->lin);

	//step over the 255 value
	int _255;
	fscanf(photo_f, "%d", &_255);


	fpos_t pos_ptr;
	fgetpos(photo_f, &pos_ptr);
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
}
