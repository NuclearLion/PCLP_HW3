#include "histo_funcs.h"

void histogram(photo_t *ph)
{
	int stars, bins;
	scanf("%d%d", &stars, &bins);

	if (ph->photo_mat == NULL) {
		error_no_load();
		return;
	}

	if (ph->type == 3 || ph->type == 6) {
		error_balck_white();
		return;
	}

	//formula: stars_on_line = val_freq/max_freq * stars

	int pixel_freq[VALS];
	memset(pixel_freq, ZERO, sizeof(pixel_freq));

	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			++pixel_freq[ph->photo_mat[i][j]];

	// for (int i = 0; i < 256; ++i) {
	// 	printf("%d: %d\n", i, pixel_freq[i]);
	// }


	int bin_step = VALS / bins;
	//printf("bin step: %d\n", bin_step);
	int *bin_val;
	bin_val = calloc(bins, sizeof(int));

	int bin_index = 0;
	int val_max = 0;
	for (int i = 0; i < VALS; i += bin_step) {
		for (int j = i; j < i + bin_step; ++j)
			bin_val[bin_index] += pixel_freq[j];
		if (bin_val[bin_index] > val_max)
			val_max = bin_val[bin_index];
		++bin_index;
	}

	// for (int i = 0; i <= bin_index; ++i)
	// 	printf("%d bin value: %d\n", i, bin_val[i]);
	// printf("val max: %d\n", val_max);

	// //check zone
	// for (int i = 0; i < bin_index; ++i) {
	// 	printf("%d\n", bin_val[i]);
	// }

	for (int i = 0; i < bins; ++i) {
		int stars_on_line = bin_val[i] * stars / val_max;
		printf("%d\t|\t", stars_on_line);
		for (int star = 0; star < stars_on_line; ++star)
			printf("*");
		printf("\n");
	}

	free(bin_val);
}
