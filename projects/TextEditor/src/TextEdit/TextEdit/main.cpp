#define PDC_DLL_BUILD 1
#include "curses.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{

	//2 args means 2nd arg is file name
	//allows user to open file from the command line
	/*ifstream commandFile;
	if (argc == 2)
	{
		commandFile.open(argv[1]);
		char contents;
		while (commandFile.good() == true)
		{
			commandFile.get(contents);
			addch(contents);
		}

		if (commandFile.is_open() == false)
		{
			//create that file for later
		}
	}*/

	WINDOW* main_window = nullptr;
	int num_rows = 0;
	int num_cols = 0;
	int x1 = 0;
	int y1 = 0;
	int top = 0;

	//initialize screen, begin curses mode
	main_window = initscr();

	//take up most of the screen
	getmaxyx(main_window, num_rows, num_cols);
	
	//creates border 
	wborder(main_window, 0, 0, 1161, 0, 0, 0, 0, 0);

	//creates new windwo to be typed in
	int sub_rows = num_rows - 3;
	int sub_cols = num_cols - 2;
	WINDOW* sub = newwin(sub_rows, sub_cols,2,1);
	keypad(sub, TRUE);

	//Checks if terminal can handle color. 
	//Code from linuxjournal.com by Jim Hall
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your window does not support color\n");
		exit(1);
	}

	/*start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	attron(COLOR_PAIR(1));
	mvaddstr(0, 5, "FILE");
	mvaddstr(0, 13, "EDIT");
	attroff(COLOR_PAIR(1));*/

	cbreak();
	
	//displays cursor
	curs_set(2);
	
	//adds message and refreshes screen
	mvwaddstr(main_window, 1, 1, "Press ESC to quit...");
	wrefresh(main_window);

	mvwaddstr(sub, 0, 0, "Type name of file and press enter: ");
	wrefresh(sub);

	//array of character for catching input string
	char input[80];
	vector<vector<char>> saver(0);
	vector<char> char_saver(0);
	
	//gets the string for the file name
	wgetstr(sub, input);

	//allows user to open and display a file
	ifstream myfile;
	myfile.open(input);
	char fileContents;
	if (myfile.is_open())
	{
		while (myfile.good() == true)
		{

			//collects the characters from the file
			myfile.get(fileContents);
			char_saver.push_back(fileContents);
			
			//pushes back the vector of characters into the vector of vectors
			if (fileContents == '\n')
			{
				saver.push_back(char_saver);
				char_saver.clear();
			}

			if (char_saver.size() == sub_cols)
			{
				saver.push_back(char_saver);
				char_saver.clear();
			}
		}

		//adds the final line into the 2d vector
		saver.push_back(char_saver);

		//closes the file
		myfile.close();
	}
	else
	{
		string failOpen = "The file did not open or does not exist.";
		strcpy_s(input, failOpen.c_str());
		wprintw(sub, input);
	}

	//adds contents of the file to the screen
	if (saver.size() > sub_rows)
	{
		wmove(sub, 0, 0);
		int difference = saver.size() - sub_rows - 2;
		top = difference;
		for (int i = difference; i < saver.size(); i++)
		{
			for (int j = 0; j < saver[i].size(); j++)
			{
				waddch(sub, saver[i][j]);
			}
		}

		
	}
	else
	{
		for (int i = 0; i < saver.size(); i++)
		{
			for (int j = 0; j < saver[i].size(); j++)
			{
				waddch(sub, saver[i][j]);
			}
		}
	}
	

	//gets initial character before loop
	int result = ' ';

	//lets user type in the window
	while (result != 27)
	{
		noecho();
		result = wgetch(sub);
		int y, x;
		getyx(sub, y, x);

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
			if (saver.size() > sub_rows)
			{
				y--;
				wmove(sub, y, x);
				//allows user to scroll up
				if (y < 0)
				{
					wclear(sub);
					wmove(sub, 0, 0);
					int newTop = top - 1;
					for (int i = newTop; i < (sub_rows + newTop) && i < saver.size(); i++)
					{
						for (int j = 0; j < saver[i].size(); j++)
						{
							waddch(sub, saver[i][j]);
						}
					}
					wmove(sub, 0, x);
					top--;
					if (top < 1)
					{
						top++;
					}
				}
			}
			else
			{
				y--;
				wmove(sub, y, x);
			}
			break;
		case KEY_DOWN:
			if (saver.size() > sub_rows)
			{
				y++;
				wmove(sub, y, x);
				//allows user to scroll down
				if (y == sub_rows)
				{
					wclear(sub);
					wmove(sub, 0, 0);
					int newTop = top + 1;
					int bottom = sub_rows + newTop;
					for (int i = newTop; i < bottom && i < saver.size(); i++)
					{
						for (int j = 0; j < saver[i].size(); j++)
						{
							waddch(sub, saver[i][j]);
						}
					}
					wmove(sub, sub_rows - 1, x);
					top++;

					//keeps top from increasing past size of vector
					if (top == saver.size())
					{
						top--;
					}

				}
			}
			else
			{
				y++;
				wmove(sub, y, x);
			}
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

			//moves the cursor down when user gets to the side of the screen
			if (x == sub_cols)
			{
				waddch(sub, '\n');
			}
			mvwaddch(sub, y, x, result);
		}

		wrefresh(sub);
	}

	endwin();

}
