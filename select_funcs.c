// Copyright 2023 311CA Dan-Dominic Staicu <dando.ds11@gmail.com>
#include "select_funcs.h"

//main call for SELECT command
void select(photo_t *ph)
{
	//it can be select or select all
	int y1, x1, y2, x2;

	//read and check if exactly 4 ints were readen
	if (scanf("%d%d%d%d", &x1, &y1, &x2, &y2) == 4) {
		//check if any photo was loaded
		if (check_load(ph)) {
			error_no_load();
			return;
		}

		//check input order
		if (y1 > y2)
			swap_int(&y1, &y2);
		if (x1 > x2)
			swap_int(&x1, &x2);

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
		ph->top.x = y1;
		ph->top.y = x1;
		ph->bot.x = y2 - 1;
		ph->bot.y = x2 - 1;

		succes_select(x1, y1, x2, y2);
	} else {
		//check if ALL was inputed or it's an invalid command
		char all[ALL_LEN];
		fgets(all, ALL_LEN, stdin);

		//remove spaces from the string and try to make the string be "ALL"
		int no_space_cnt = 0;
		for (int i = 0; all[i] != '\0'; ++i) {
			if (all[i] != ' ')
				all[no_space_cnt++] = all[i];
		}
		all[no_space_cnt] = '\0';

		//in case SELECT ALL was probably inputed
		//read ALL (probably) in order to step over it
		if (strcmp(all, "ALL\n") == 0) {
			//check if any photo was loaded
			if (check_load(ph)) {
				error_no_load();
				return;
			}

			//use extremes as selection coords
			select_all(ph);
			succes_select_all();
		} else {
			//in case some garbage text was inputed in place of ALL
			getchar();
			error_invalid();
			return;
		}
	}
}

//set coords as full photo is selected
void select_all(photo_t *ph)
{
	ph->top.x = 0;
	ph->top.y = 0;
	ph->bot.x = ph->lin - 1;
	ph->bot.y = ph->col - 1;
}
