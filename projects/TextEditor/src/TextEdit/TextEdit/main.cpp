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
	getmaxyx(main_window, num_rows, num_cols);
	
	//creates border 
	wborder(main_window, 0, 0, 1161, 0, 0, 0, 0, 0);

	//creates new windwo to be typed in
	WINDOW* sub = newwin(num_rows-3, num_cols-2,2,1);

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
	
	//displays cursor
	curs_set(2);
	
	//adds message and refreshes screen
	mvwaddstr(main_window, 1, 1, "Press ESC to quit...");
	wrefresh(main_window);

	int result = ' ';
	int y_pos = 2;

	//lets user type in the window
	while (result != 27)
	{
		int result2 = wgetch(sub);
		int y, x;
		getyx(sub, y, x);

		//moves the cursor down when user gets to the side of the screen
		if (x == num_cols - 2)
		{
			y++;
			wmove(sub, y, x);
		}

		//Lets the user backspace and delete characters
		if (result2 == 8)
		{
			wprintw(sub,"\b");
			wprintw(sub," ");
		}

		mvwaddch(sub, y, x, result2);

		wrefresh(sub);

		result = result2;
	}

	endwin();

}