// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "histo_funcs.h"

void histogram(photo_t *ph)
{
	//check if any photo was loaded
	if (check_load(ph)) {
		error_no_load();
		//step over the next inputed text
		trash_invalid();
		return;
	}

	//try to read the parameters of this command
	//and check if their count is correct
	int stars, bins;
	int res_scan = scanf("%d%d", &stars, &bins);
	if (res_scan != 2) {
		error_invalid();
		return;
	}
	//check if there are more than 2 parameters
	if (res_scan == 2) {
		char trash[TRASH_LEN];
		fgets(trash, TRASH_LEN, stdin);
		if (strcmp(trash, "\n") != 0) {
			error_invalid();
			return;
		}
	}

	//check if photo is black and white
	if (is_color(ph->type)) {
		error_balck_white();
		return;
	}

	//init the frequency array and init it with 0 using memset
	int pixel_freq[VALS];
	memset(pixel_freq, ZERO, sizeof(pixel_freq));

	//save the frequency of pixels
	freq_counter(ph, pixel_freq);

	//calculate how many pixels there are in a bin
	int bin_step = VALS / bins;
	//create the bins and alloc memory for them (already inited with 0)
	int *bin_val;
	bin_val = calloc(bins, sizeof(int));

	if (!bin_val) {
		fprintf(stderr, "calloc failed at bin_val\n");
		bin_val = NULL;
		free_photo(ph);
		exit(1);
	}

	int bin_index = 0;
	int val_max = 0;
	for (int i = 0; i < VALS; i += bin_step) {
		//sum the pixels occurences in the bins
		for (int j = i; j < i + bin_step; ++j)
			bin_val[bin_index] += pixel_freq[j];

		//save the max value of a bin
		if (bin_val[bin_index] > val_max)
			val_max = bin_val[bin_index];

		++bin_index;
	}

	//print the histogram
	for (int i = 0; i < bins; ++i) {
		// formula of calculating the stars / line
		int stars_on_line = bin_val[i] * stars / val_max;

		printf("%d\t|\t", stars_on_line);
		for (int star = 0; star < stars_on_line; ++star)
			printf("*");
		printf("\n");
	}

	//gratefuly free the memory
	free(bin_val);
}
