// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "select_funcs.h"

void select(photo_t *ph)
{
	//it can be select or select all
	int y1, x1, y2, x2;

	//BIG TODO
	//wtf is this creationism
	if (scanf("%d%d%d%d", &x1, &y1, &x2, &y2) == 4) {
		//check if any photo was loaded
		if (!ph->photo_mat && !ph->rgb_mat.red) {
			error_no_load();
			return;
		}

		//check input order
		if (y1 > y2)
			swap_int(&y1, &y2);
		if (x1 > x2)
			swap_int(&x1, &x2);

		int initial_values[4];
		initial_values[0] = x1;
		initial_values[1] = y1;
		initial_values[2] = x2;
		initial_values[3] = y2;

		//check if selection zone exists
		if (y1 == y2 || x1 == x2) {
			error_select();
			return;
		}

		//check if coords are inside the mat according to photo's type
		if (x1 < 0 || x2 > ph->col || y1 < 0 || y2 > ph->lin) {
			error_select();
			return;
		}

		//save the final values of selection
		ph->top_x = y1;
		ph->top_y = x1;
		ph->bot_x = y2 - 1;
		ph->bot_y = x2 - 1;

		succes_select(initial_values);
	} else {
		//check if ALL was inputed or it's an invalid command
		char all[ALL_LEN];
		fgets(all, ALL_LEN, stdin);

		int no_space_cnt = 0;
		for (int i = 0; all[i] != '\0'; ++i) {
			if (all[i] != ' ')
				all[no_space_cnt++] = all[i];
		}
		all[no_space_cnt] = '\0';

		//in case SELECT ALL was inputed
		//read ALL in order to step over it
		if (strcmp(all, "ALL\n") == 0) {
			//check if any photo was loaded
			if (!ph->photo_mat && !ph->rgb_mat.red) {
				error_no_load();
				return;
			}

			//use extremes as selection coords
			select_all(ph);
			succes_select_all();
		} else {
			getchar();
			error_invalid();
			return;
		}
	}
}

void select_all(photo_t *ph)
{
	ph->top_x = 0;
	ph->top_y = 0;
	ph->bot_x = ph->lin - 1;
	ph->bot_y = ph->col - 1;
}
