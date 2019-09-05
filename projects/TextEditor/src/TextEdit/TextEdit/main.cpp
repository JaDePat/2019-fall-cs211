#define PDC_DLL_BUILD 1
#include "curses.h"
#include <string>
using namespace std;

int main(void)
{
	WINDOW* main_window = nullptr;
	int num_rows = 0;
	int num_cols = 0;

	//initialize screen, begin curses mode
	main_window = initscr();

	//take up most of the screen
	/*getmaxyx(main_window, num_rows, num_cols);
	resize_term(num_rows - 1, num_cols - 1);
	getmaxyx(main_window, num_rows, num_cols);*/
	wborder(main_window, 0, 0, 1161, 0, 0, 0, 0, 0);

	//Checks if terminal can handle color. 
	//Code from linuxjournal.com by Jim Hall
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your window does not support color\n");
		exit(1);
	}

	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	attron(COLOR_PAIR(1));
	mvaddstr(0, 5, "FILE");
	mvaddstr(0, 13, "EDIT");
	attroff(COLOR_PAIR(1));


	//turn off key echo
	noecho();
	//nodelay(main_window, TRUE);
	//keypad(main_window, TRUE);
	curs_set(TRUE);
	
	//tells curses to draw
	refresh();

	//revert back to normal console mode
	//nodelay(main_window, TRUE);
	//keypad(main_window, TRUE);
	mvaddstr(1, 1, "Press ESC to quit...");
	move(2, 1);
	int result = ' ';

	//lets user type in the window
	while (result != 27)
	{
		int result2 = getch();
		if (result2 == 8)
		{
			printw("\b");
			printw(" ");
		}
		addch(result2);
		result = result2;
	}

	endwin();

}