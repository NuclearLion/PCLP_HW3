#include "rotate_funcs.h"

void rotate(photo_t *ph)
{
	if (!ph->photo_mat && !ph->rgb_mat.red) {
		error_no_load();
		return;
	}

	int angle;
	scanf("%d", &angle);

	if (angle < -360 || angle > 360 || angle % 90 != 0) {
		error_rotation_angle();
		return;
	}

	int sel_lin = ph->bot_x - ph->top_x + 1;
	int sel_col = ph->bot_y - ph->top_y + 1;

	if (sel_lin != sel_col) {
		error_square_sel();
		return;
	}

	//count of rotations of 90 degrees
	int rot_cnt = angle / 90;
	if (angle > 0) {
		for (int i = 0; i < rot_cnt; ++i)
			rotate_sel(1);
	} else {
		//make it positive
		rot_cnt *= -1;
		for (int i = 0; i < rot_cnt; ++i)
			rotate_sel(-1);
		
	}

	succes_rotate(angle);
}

void rotate_sel(int direction)
{
	printf("%d\n", direction);
}