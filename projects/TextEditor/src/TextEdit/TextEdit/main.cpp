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
	resize_term(num_rows - 1, num_cols - 1);
	getmaxyx(main_window, num_rows, num_cols);

	//turn off key echo
	noecho();
	//nodelay(main_window, TRUE);
	keypad(main_window, TRUE);
	curs_set(TRUE);

	//FUN STUFF HAPPENS HERE

	for (int i = 0; i < num_cols; i++)
	{
		//top row
		mvaddch(0, i, 1161);

	}
	for (int i = 0; i < num_rows; i++)
	{
		//left column
		mvaddch(i+1, 0, '<');

		//right column
		mvaddch(i+1, num_cols - 1, '>');
	}
	
	//tells curses to draw
	refresh();

	//revert back to normal console mode
	//nodelay(main_window, TRUE);
	keypad(main_window, TRUE);
	mvaddstr(1, 1, "Press Q to quit...");
	move(2, 1);
	int result = ' ';

	//lets user type in the window
	while (result != 'Q')
	{
		int result2 = getch();
		addch(result2); 
		result = result2;
	}
	endwin();

}