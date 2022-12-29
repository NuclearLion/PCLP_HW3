#include "select_funcs.h"

void select(photo_t *ph)
{
	//check if any photo was loaded
	if (ph->photo_mat == NULL) {
		error_no_load();
		return;
	}

	//it can be select or select all
	int x1, y1, x2, y2;
	if (scanf("%d%d%d%d", &x1, &y1, &x2, &y2)) {
		//check input order
		if (x1 > x2)
			swap_int(&x1, &x2);
		if (y1 > y2)
			swap_int(&y1, &y2);

		//dimension of 1 pixel
		int px1 = 1;

		//in case photo is type P3 or P6, it's matrix actually has 3 * col_nr
		//so the selection
		if (ph->type == 3 || ph->type == 6) {
			if (y1 != 0)
				y1 = y1 * 3 - 2;
			if (y2 != 0)
				y2 = y2 * 3 - 2;
			px1 = 3;
		}

		//check if coords are inside the mat
		if (y1 < 0 || y2 > ph->col || x1 < 0 || x2 > ph->lin) { //maybe +1px
			error_select();
			return;
		}

		//save the final values of selection
		ph->top_x = x1;
		ph->top_y = y1;
		ph->bot_x = x2 - px1;
		ph->bot_y = y2 - px1;
	} else {
		//in case SELECT ALL was inputed
		char all[4];
		scanf("%s", all);
		ph->top_x = 0;
		ph->top_y = 0;
		ph->bot_x = ph->lin;
		ph->bot_y = ph->col;
		succes_select_all();
		return;
	}
}