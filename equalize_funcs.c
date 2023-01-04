#include "equalize_funcs.h"

void equalize(photo_t *ph)
{
	if (ph->photo_mat == NULL && ph->rgb_mat.red == NULL) {
		error_no_load();
		return;
	}

	if (is_color(ph->type)) {
		error_balck_white();
		return;
	}

	long long area = ph->lin * ph->col;

	int pixel_freq[VALS];
	memset(pixel_freq, ZERO, sizeof(pixel_freq));

	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j)
			++pixel_freq[ph->photo_mat[i][j]];

	for (int i = 0; i < ph->lin; ++i)
		for (int j = 0; j < ph->col; ++j) {
			int old_pixel = ph->photo_mat[i][j];
			int new = (int)round(eq_pixel(old_pixel, area, pixel_freq));
			ph->photo_mat[i][j] = new;
		}
	succes_equalize();
}

int eq_pixel(int pixel, long long area, int *pixel_frq)
{
	double sum = 0;
	for (int i = 0; i <= pixel; ++i)
		sum += pixel_frq[i];
	double unclamped = sum / area * MAX_VAL;
	double result = clamp(unclamped);
	return result;
}
