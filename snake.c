#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define	LINES	30
#define	COLS	60

int start_x = 10, start_y = 10;
int main(int argc,char* argv[])
{
	int i, j, c, head_x, head_y, tail_x, tail_y, fx, fy;
	char dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int head_dir_index = 3, tail_dir_index = 3;
	char pad[LINES][COLS];

	initscr();
	noecho();
	keypad(stdscr, 1);
	nodelay(stdscr, 1);
	curs_set(0);

	memset(pad, 0, sizeof(pad));
	pad[start_y][start_x] = 1;
	head_x = tail_x = start_x;
	head_y = tail_y = start_y;
	srand(time(NULL));

	for (i = 0; i < LINES; i ++) {
		pad[i][0] = 1;
		pad[i][COLS - 1] = 1;
	}
	for (i = 0; i < COLS; i ++) {
		pad[0][i] = 1;
		pad[LINES - 1][i] = 1;
	}

	while (1) {
		fx = rand()%COLS;
		fy = rand()%LINES;
		if (pad[fy][fx] == 1)
			continue;
		pad[fy][fx] = 2;

		while (c = getch()) {
			if (c == KEY_UP)
				head_dir_index = 0;
			else if (c == KEY_DOWN)
				head_dir_index = 1;
			else if (c == KEY_LEFT)
				head_dir_index = 2;
			else if (c == KEY_RIGHT)
				head_dir_index = 3;
			head_y += dir[head_dir_index][0];
			head_x += dir[head_dir_index][1];
			if (head_y >= LINES - 1 || head_x >= COLS - 1 || head_x <= 0 || head_y <= 0 ||
				pad[head_y][head_x] == 1) {
				mvprintw(LINES/2, (COLS - 9)/2, "game over");
				refresh();
				sleep(2);
				endwin();
				exit(1);
			}
			if (pad[head_y][head_x] == 2) {
				pad[head_y][head_x] = 1;
				break;
			}

			pad[head_y][head_x] = 1;
			pad[tail_y][tail_x] = 0;
			if (tail_y - 1 > 0 && pad[tail_y - 1][tail_x] == 1)
				tail_dir_index = 0;
			else if (tail_y + 1 < LINES - 1 && pad[tail_y + 1][tail_x] == 1)
				tail_dir_index = 1;
			else if (tail_x - 1 > 0 && pad[tail_y][tail_x - 1] == 1)
				tail_dir_index = 2;
			else if (tail_x + 1 < COLS -1 && pad[tail_y][tail_x + 1] == 1)
				tail_dir_index = 3;
			tail_y += dir[tail_dir_index][0];
			tail_x += dir[tail_dir_index][1];
			for (i = 0; i < LINES; i ++)
				for (j = 0; j < COLS; j ++)
					mvprintw(i, j, pad[i][j]?"#":" ");
			refresh();
			usleep(200000);
		}
	}

	return 0;
}
