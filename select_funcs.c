#include "select_funcs.h"

void select(photo_t *ph)
{
	//it can be select or select all
	int x1 = -50, y1 = -50, x2 = -50, y2 = -50;

	//BIG TODO
	//wtf is this this creationism
	if (scanf("%d%d%d%d", &y1, &x1, &y2, &x2) == 4) {

		// if (x1 == -50 || y1 == -50 || x2 == -50 || y2 == -50) {
		// 	trash_invalid();
		// 	printf("PULA in eroare sus\n");
		// 	trash_invalid();
		// 	error_invalid();
		// 	return;
		// }

		//check if any photo was loaded
		if (!ph->photo_mat && !ph->rgb_mat.red) {
			error_no_load();
			return;
		}

		//check input order
		if (x1 > x2)
			swap_int(&x1, &x2);
		if (y1 > y2)
			swap_int(&y1, &y2);

		int initial_values[4];
		initial_values[0] = y1;
		initial_values[1] = x1;
		initial_values[2] = y2;
		initial_values[3] = x2;

		//check if selection zone exists
		if (x1 == x2 || y1 == y2) {
			error_select();
			return;
		}

		//check if coords are inside the mat according to photo's type
		if (y1 < 0 || y2 > ph->col || x1 < 0 || x2 > ph->lin) {
			// printf("y2 : %d\nx2 : %d\n", y2, x2);
			// printf("col : %d\nlin : %d\n", ph->col, ph->lin);
			error_select();
			return;
		}
		//printf("PULA in select\n");
		//save the final values of selection
		ph->top_x = x1;
		ph->top_y = y1;
		ph->bot_x = x2 - 1;
		ph->bot_y = y2 - 1;

		succes_select(initial_values);
	} else {
		//check if ALL was inputed or it's an invalid command
		char all[ALL_LEN];
		// scanf("%s", all);
		fgets(all, ALL_LEN, stdin);

		// for (int i = 1; all[i]; ++i)
		// 	all[i - 1] = all[i];

		int no_space_cnt = 0;
		for (int i = 0; all[i] != '\0'; ++i) {
			if (all[i] != ' ')
				all[no_space_cnt++] = all[i];
		}

		all[no_space_cnt] = '\0';

		//printf("asta e all: %s\n", all);

		//printf("asta e all: %s\n", all);

		// if (strcmp(all, "\n") == 0) {
		// 	trash_invalid();
		// 	error_invalid();
		// 	return;
		// }
		// printf("all aici: %s\n", all);
		//getchar();
		//in case SELECT ALL was inputed
		//read ALL in order to step over it
		if (strcmp(all, "ALL\n") == 0) {
			// printf("PULA in ALLLLL\n");

			//check if any photo was loaded
			if (ph->photo_mat == NULL && ph->rgb_mat.red == NULL) {
				error_no_load();
				return;
			}

			//use extremes as selection coords
			select_all(ph);
			succes_select_all();
		} else {
			//trash_invalid();
			// printf("PULA in eroare\n");
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
