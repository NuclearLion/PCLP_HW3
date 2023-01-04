#include "select_funcs.h"

void select(photo_t *ph)
{
	//check if any photo was loaded
	if (ph->photo_mat == NULL && ph->rgb_mat.red == NULL) {
		error_no_load();
		return;
	}

	//it can be select or select all
	int x1, y1, x2, y2;

	//BIG TODO
	//wtf is this this creationism
	if (scanf("%d%d%d%d", &y1, &x1, &y2, &x2)) {
		int initial_values[4];
		initial_values[0] = y1;
		initial_values[1] = x1;
		initial_values[2] = y2;
		initial_values[3] = x2;

		//check input order
		if (x1 > x2)
			swap_int(&x1, &x2);
		if (y1 > y2)
			swap_int(&y1, &y2);

		//check if coords are inside the mat according to photo's type
		if (y1 < 0 || y2 > ph->col || x1 < 0 || x2 > ph->lin) {
			// printf("y2 : %d\nx2 : %d\n", y2, x2);
			// printf("col : %d\nlin : %d\n", ph->col, ph->lin);
			error_select();
			return;
		}

		//save the final values of selection
		ph->top_x = x1;
		ph->top_y = y1;
		ph->bot_x = x2 - 1;
		ph->bot_y = y2 - 1;

		succes_select(initial_values);
	} else {
		//in case SELECT ALL was inputed
		//read ALL in order to step over it
		char all[ALL_LEN];
		scanf("%s", all);

		//use extremes as selection coords
		select_all(ph);
		succes_select_all();
	}
}

void select_all(photo_t *ph)
{
	ph->top_x = 0;
	ph->top_y = 0;
	ph->bot_x = ph->lin - 1;
	ph->bot_y = ph->col - 1;
}