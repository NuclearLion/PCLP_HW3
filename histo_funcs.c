#include "histo_funcs.h"

void histogram(photo_t *ph)
{
	if (!ph->photo_mat && !ph->rgb_mat.red) {
		error_no_load();
		trash_invalid();
		return;
	}

	int stars, bins;
	int res_scan = scanf("%d%d", &stars, &bins);
	if (res_scan != 2) {
		error_invalid();
		return;
	}

	//check if there are more than 2 parameters
	if (res_scan == 2) {
		char trash[10];
		fgets(trash, 10, stdin);
		if (strcmp(trash, "\n") != 0) {
			error_invalid();
			return;
		}
	}

	if (is_color(ph->type)) {
		error_balck_white();
		return;
	}

	int pixel_freq[VALS];
	memset(pixel_freq, ZERO, sizeof(pixel_freq));

	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			++pixel_freq[ph->photo_mat[i][j]];

	int bin_step = VALS / bins;
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

	for (int i = 0; i < bins; ++i) {
		int stars_on_line = bin_val[i] * stars / val_max;
		printf("%d\t|\t", stars_on_line);
		for (int star = 0; star < stars_on_line; ++star)
			printf("*");
		printf("\n");
	}

	free(bin_val);
}
