// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "equalize_funcs.h"

//main call of equalize function
void equalize(photo_t *ph)
{
	//check if any photo was loaded
	if (check_load(ph)) {
		error_no_load();
		return;
	}

	//check if photo is black and white
	if (is_color(ph->type)) {
		error_balck_white();
		return;
	}

	//the area of the photo, in pixels
	long long area = ph->lin * ph->col;

	//create a freqency array and init it with 0 everywhere uusing memset
	int pixel_freq[VALS];
	memset(pixel_freq, ZERO, sizeof(pixel_freq));

	//count the frequency of every pixel
	freq_counter(ph, pixel_freq);

	//calculate the new pixels' values and overwrite them
	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j) {
			int old_pixel = ph->photo_mat[i][j];
			int new_pixel = (int)round(eq_pixel(old_pixel, area, pixel_freq));
			ph->photo_mat[i][j] = new_pixel;
		}
	succes_equalize();
}

//calculate the unrounded value of the new pixel
int eq_pixel(int pixel, long long area, int *pixel_frq)
{
	//calculate the sum of pixels from 0 to current pixel
	double sum = 0;
	for (int i = 0; i <= pixel; ++i)
		sum += pixel_frq[i];

	//apply the formula of equalization and clamp it
	double unclamped = sum / area * MAX_VAL;
	double result = clamp(unclamped);

	return result;
}
