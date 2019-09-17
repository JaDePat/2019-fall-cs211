#define PDC_DLL_BUILD 1
#include "curses.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
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
	keypad(sub, TRUE);

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

	cbreak();
	
	//displays cursor
	curs_set(2);
	
	//adds message and refreshes screen
	mvwaddstr(main_window, 1, 1, "Press ESC to quit...");
	wrefresh(main_window);

	mvwaddstr(sub, 0, 0, "Type name of file and press enter: ");
	wrefresh(sub);

	//gets string for file opening
	char file[80];
	wgetstr(sub, file);

	//allows user to open and display a file
	ifstream myfile;
	myfile.open(file);
	string file2;
	if (myfile.is_open())
	{
		cout << "Hell yeah!" << endl;
		while (getline(myfile, file2))
		{
			strcpy_s(file, file2.c_str());
			wprintw(sub, file);
			wprintw(sub, "\n");
		}
	}
	else
	{
		string failOpen = "The file did not open.";
		strcpy_s(file, failOpen.c_str());
		wprintw(sub, file);
	}

	//gets initial character before loop
	int result = wgetch(sub);

	//lets user type in the window
	while (result != 27)
	{
		noecho();
		result = wgetch(sub);
		int y, x;
		getyx(sub, y, x);

		//moves the cursor down when user gets to the side of the screen
		if (x == num_cols-5)
		{
			x++;
			wmove(sub, y, x);
			wprintw(sub, "->");
			y++;
			x = 0;
			wmove(sub, y, x);
		}

		switch (result)
		{

		//Lets the user backspace and delete characters
		case 8:
			wprintw(sub, "\b");
			wprintw(sub, " ");
			mvwaddch(sub, y, x, result);
			break;

		//custom enter key
		case 10:
			y++;
			x = 0;
			wmove(sub, y, x);
			break;

		//arrow keys
		case KEY_UP:
			y--;
			wmove(sub, y, x);
			break;
		case KEY_DOWN:
			y++;
			wmove(sub, y, x);
			break;
		case KEY_RIGHT:
			x++;
			wmove(sub, y, x);
			break;
		case KEY_LEFT:
			x--;
			wmove(sub, y, x);
			break;
		default:
			mvwaddch(sub, y, x, result);
		}

		wrefresh(sub);
	}

	endwin();

}
