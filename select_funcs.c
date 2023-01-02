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
		int initial_values[4];
		initial_values[0] = x1;
		initial_values[1] = y1;
		initial_values[2] = x2;
		initial_values[3] = y2;


		printf("y2 after read: %d\n", y2);

		//check input order
		if (x1 > x2)
			swap_int(&x1, &x2);
		if (y1 > y2)
			swap_int(&y1, &y2);

		// //dimension of 1 pixel
		// int px1 = 1;
		if (x2 > 1)
			x2--;
		if (y2 > 1)
			y2--;

		//in case photo is type P3 or P6, it's matrix actually has 3 * col_nr
		//so the selection must start from the firxt value of the selected 
		//pixel (RGB)
		if (ph->type == P3 || ph->type == P6) {
			if (y1 != 0)
				y1 *= 3;
			if (y2 != 0)
				y2 *= 3;
			//px1 = 3;
		}

		//check if coords are inside the mat
		if (y1 < 0 || y2 > ph->col || x1 < 0 || x2 > ph->lin) { //maybe +1px
			error_select();
			return;
		}

		//save the final values of selection
		ph->top_x = x1;
		ph->top_y = y1;
		ph->bot_x = x2;
		printf("y2 just before save %d\n", y2);
		ph->bot_y = y2;

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
	ph->bot_x = ph->lin;
	ph->bot_y = ph->col; //for bw i think
}