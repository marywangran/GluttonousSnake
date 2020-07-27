#include <string.h>
#include <ncurses.h>

int sx = 10, sy = 10;
#define	LINES	30
#define	COLS	30
int main(int argc,char* argv[])
{
	int i, j, c, hx, hy, tx, ty, fx, fy;
	char dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	char pad[LINES][COLS];
	int hidx = 3, tidx = 3;

	initscr();
	noecho();
	keypad(stdscr, 1);
	nodelay(stdscr, 1);
	curs_set(0);

	memset(pad, 0, sizeof(pad));
	pad[sy][sx] = 1;
	hx = tx = sx;
	hy = ty = sy;

	while (1) {
		fx = rand()%COLS;
		fy = rand()%LINES;
		if (pad[fy][fx] == 1)
			continue;
		pad[fy][fx] = 2;

		while (c = getch()) {
			if (c == KEY_UP)
				hidx = 0;
			else if (c == KEY_DOWN)
				hidx = 1;
			else if (c == KEY_LEFT)
				hidx = 2;
			else if (c == KEY_RIGHT)
				hidx = 3;
			hy += dir[hidx][0];
			hx += dir[hidx][1];
			if (pad[hy][hx] == 1 || hy > LINES || hx > COLS || hx < 0 || hy < 0) {
				clear();
				mvprintw(COLS/2, LINES/2, "game over");
				refresh();
				sleep(100);
			}
			if (pad[hy][hx] == 2) {
				pad[hy][hx] = 1;
				break;
			}

			pad[hy][hx] = 1;
			pad[ty][tx] = 0;
			if (pad[ty - 1][tx] == 1)
				tidx = 0;
			else if (pad[ty + 1][tx] == 1)
				tidx = 1;
			else if (pad[ty][tx - 1] == 1)
				tidx = 2;
			else if (pad[ty][tx + 1] == 1)
				tidx = 3;
			ty += dir[tidx][0];
			tx += dir[tidx][1];
			for (i = 0; i < LINES; i ++) {
				for (j = 0; j < COLS; j ++) {
					mvprintw(i, j, pad[i][j]?"#":" ");
				}
			}
			refresh();
			usleep(500000);
		}
	}

	endwin();
	return 0;
}
