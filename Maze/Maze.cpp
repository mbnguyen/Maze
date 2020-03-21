//
//  main.cpp
//  Maze
//
//  Created by Minh Nguyen on 11/4/19.
//  Copyright © 2019 Minh Nguyen. All rights reserved.
//
// Project's name: Maze Traversal
// Programmer: Minh Nguyen


#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include "MMSystem.h"
//#include <curses.h>

//#define getch() wgetch(stdscr)
#define WALL '#'
#define ROAD ' '
#define KEY 'o'
#define POSITION 'X'
#define END 'O'
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_RIGHT 77
#define KEY_LEFT 75
#define KEY_ENTER '\r'
#define KEY_ESCAPE 27

using namespace std;


struct point {
	int row, col;
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
};

void printBanner();
void menuGame(int &row, int &col, int &keys, int &level);
void printMenu(int line, int optionLevel, int optionSound);
char** createMaze(int row, int col);
void randomMaze(char** maze, int startRow, int startCol, int row, int col, int level);
void addKeys(char** maze, int row, int col, int keys);
void printMaze(char** maze, int row, int col, int posR = -1, int posC = -1);
void play(char** maze, int row, int col, int keys);

int main() {
	const char
		TITLE[] = "TITLE Maze Traversal Game   (by Minh Nguyen)",
		COLOR[] = "Color 2F";
	system(TITLE);
	system(COLOR);

	bool again = true;
	while (again) {
		int row, col, level, keys;

		menuGame(row, col, keys, level);

		char **maze = createMaze(row, col);
		int startRow = 9;
		int startCol = 10;

		randomMaze(maze, startRow, startCol, row, col, level);
		addKeys(maze, row, col, keys);

		system("CLS");
		printBanner();
		cout << "\n\nHere is your maze:\n\n";
		printMaze(maze, row, col);
		cout << "\n\nPress 'Enter' to start the game!";

		int input = 0;
		while (input != KEY_ENTER) {
			input = _getch();
		}

		play(maze, row, col, keys);
		cout
			<< "\n\n"
			<< "\t\tCongratulation! You have solved the maze!"
			<< "\n\n"
			<< "\t\tPress 'Enter' to play again. Press 'Esc' to exit.\n\n";

		input = 0;
		while (input != KEY_ENTER && input != KEY_ESCAPE) {
			input = _getch();
		}

		if (input == KEY_ESCAPE) {
			again = false;
		}
		system("CLS");
	}

	return 0;
}

void printBanner() {
	cout
		<< "\n\n"
		<< "\t\t*********************************************\n"
		<< "\t\t*            MAZE TRAVERSAL GAME            *\n"
		<< "\t\t*                                           *\n"
		<< "\t\t* By: Minh Nguyen                           *\n"
		<< "\t\t*********************************************\n";
}

void menuGame(int &row, int &col, int &keys, int &level) {
	int line = 0, optionLevel = 0, optionSound = 0;
	row = 20; col = 20; level = 250; keys = 10; bool sound = true;
	PlaySound(TEXT("music.wav"), NULL, SND_LOOP | SND_ASYNC);

	printMenu(line, optionLevel, optionSound);
	bool done = false;
	int input;
	while (!done)
	{
		input = 0;

		switch ((input = _getch())) {
		case KEY_UP: // Key up
			line--;
			if (line == -1)
				line = 2;
			system("CLS");
			printMenu(line, optionLevel, optionSound);
			break;
		case KEY_DOWN:
			line++;
			if (line == 3)
				line = 0;
			system("CLS");
			printMenu(line, optionLevel, optionSound);
			break;
		case KEY_LEFT:
			if (line == 0) {
				optionLevel--;
				if (optionLevel == -1)
					optionLevel = 2;
				if (optionLevel == 0) {
					row = 20; col = 20; level = 250; keys = 10;
				}
				else if (optionLevel == 1) {
					row = 30; col = 30; level = 600; keys = 20;
				}
				else if (optionLevel == 2) {
					row = 40; col = 40; level = 1200; keys = 30;
				}
			}
			else if (line == 1) {
				optionSound--;
				if (optionSound == -1)
					optionSound = 1;
				if (optionSound == 0) {
					if (sound == false) {
						PlaySound(TEXT("music.wav"), NULL, SND_LOOP | SND_ASYNC);
					}
					sound = true;
				}
				else if (optionSound == 1) {
					if (sound == true) {
						PlaySound(NULL, NULL, 0);
					}
					sound = false;
				}
			}
			system("CLS");
			printMenu(line, optionLevel, optionSound);
			break;
		case KEY_RIGHT:
			if (line == 0) {
				optionLevel++;
				if (optionLevel == 3)
					optionLevel = 0;
				if (optionLevel == 0) {
					row = 20; col = 20; level = 250; keys = 10;
				}
				else if (optionLevel == 1) {
					row = 30; col = 30; level = 600; keys = 20;
				}
				else if (optionLevel == 2) {
					row = 40; col = 40; level = 1200; keys = 30;
				}
			}
			else if (line == 1) {
				optionSound++;
				if (optionSound == 2)
					optionSound = 0;
				if (optionSound == 0) {
					if (sound == false) {
						PlaySound(TEXT("music.wav"), NULL, SND_LOOP | SND_ASYNC);
					}
					sound = true;
				}
				else if (optionSound == 1) {
					if (sound == true) {
						PlaySound(NULL, NULL, 0);
					}
					sound = false;
				}
			}
			system("CLS");
			printMenu(line, optionLevel, optionSound);
			break;
		case KEY_ENTER:
			if (line == 0) {
				optionLevel++;
				if (optionLevel == 3)
					optionLevel = 0;
				if (optionLevel == 0) {
					row = 20; col = 20; level = 250; keys = 10;
				}
				else if (optionLevel == 1) {
					row = 30; col = 30; level = 600; keys = 20;
				}
				else if (optionLevel == 2) {
					row = 40; col = 40; level = 1200; keys = 30;
				}
			}
			else if (line == 1) {
				optionSound++;
				if (optionSound == 2)
					optionSound = 0;
				if (optionSound == 0) {
					if (sound == false) {
						PlaySound(TEXT("music.wav"), NULL, SND_LOOP | SND_ASYNC);
					}
					sound = true;
				}
				else if (optionSound == 1) {
					if (sound == true) {
						PlaySound(NULL, NULL, 0);
					}
					sound = false;
				}
			}
			else if (line == 2) {
				done = true;
			}
			system("CLS");
			printMenu(line, optionLevel, optionSound);
			break;
		}

	}
	return;
}

void printMenu(int line, int optionLevel, int optionSound) {
	printBanner();
	cout
		<< "\n\n"
		<< "\tInstruction: Use arrow keys and 'Enter' to go through menu and play game.\n"
		<< "\t             Collect all the keys before getting to the exit.\n"
		<< "\n\n"
		<< "\t\t" << (line == 0 ? ">" : " ") << "Level" << (line == 0 ? "<" : "") << "\t\t\t";
	switch (optionLevel)
	{
	case 0:
		cout << "Easy";
		break;
	case 1:
		cout << "Medium";
		break;
	case 2:
		cout << "Hard";
		break;
	}

	cout
		<< "\n\n"
		<< "\t\t" << (line == 1 ? ">" : " ") << "Sound" << (line == 1 ? "<" : "") << "\t\t\t" << (optionSound == 0 ? "On" : "Off")
		<< "\n\n\n"
		<< "\t\t" << (line == 2 ? ">" : " ") << "Create Maze" << (line == 2 ? "<" : "")
		<< "\n\n";

	return;
}

char** createMaze(int row, int col) {
	char ** maze;
	maze = new char*[row];
	for (int i = 0; i < row; i++) {
		maze[i] = new char[col];
	}

	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			maze[r][c] = WALL;
		}
	}

	return maze;
}

void randomMaze(char** maze, int startRow, int startCol, int row, int col, int level) {
	/*          0
			3       2
				1
	*/

	srand(static_cast<unsigned int>(time(NULL)));
	vector<point> path;
	point p;
	p.row = startRow; p.col = startCol;
	maze[startRow][startCol] = ROAD;
	path.push_back(p);

	bool isDone = false;
	int count = 0;
	int exit = 0;

	while (!isDone) { //Complete the maze
		count++;
		int dir, index = rand() % path.size(); // Get a random known point
		p = path[index];
		if (p.up && p.down && p.right && p.left) { // Erase a closed point
			path.erase(path.begin() + index);
			continue;
		}
		int r = p.row;
		int c = p.col;

		bool again = true;
		while (again) {	// Get a valid open direction for a point
			dir = rand() % 4;
			if (dir == 0 && p.up)
				continue;
			if (dir == 1 && p.down)
				continue;
			if (dir == 2 && p.right)
				continue;
			if (dir == 3 && p.left)
				continue;
			again = false;
		}
		switch (dir)
		{
		case 0:	// Going up
			if (r - 2 <= 0) {	// Get to the side of the maze, if it's not "random" enough, try again
				if (count < level) {
					count--;
					continue;
				}
				else {	// Reached to the side and ready to exit
					exit++;
					if (exit == 2) // Done
						isDone = true;
					bool printed = false;
					if (r - 2 >= 0) { 
						maze[r - 2][c] = END;
						printed = true;
					}
					if (r - 1 >= 0) {
						if (printed)
							maze[r - 1][c] = ROAD;
						else
							maze[r - 1][c] = END;
					}
				}
			}
			else { // Have not reached to the side
				if (maze[r - 2][c] == WALL) { // Have not discovered, replace it with a "ROAD"
					maze[r - 1][c] = ROAD;
					maze[r - 2][c] = ROAD;
					point n;
					n.row = r - 2;
					n.col = c;
					n.down = true;
					path.push_back(n);	// Store the discovered point in the vector
				}
				p.up = true;	// Store the status of the point
				path.erase(path.begin() + index);
				path.insert(path.begin() + index, p);
			}
			break;

		case 1: // Going down
			if (r + 2 >= row - 1) {
				if (count < level) {
					count--;
					continue;
				}
				else {
					exit++;
					if (exit == 2)
						isDone = true;
					bool printed = false;
					if (r + 2 < row) {
						maze[r + 2][c] = END;
						printed = true;
					}
					if (r + 1 < row) {
						if (printed)
							maze[r + 1][c] = ROAD;
						else
							maze[r + 1][c] = END;
					}
				}
			}
			else {
				if (maze[r + 2][c] == WALL) {
					maze[r + 1][c] = ROAD;
					maze[r + 2][c] = ROAD;
					point n;
					n.row = r + 2;
					n.col = c;
					n.up = true;
					path.push_back(n);
				}
				p.down = true;
				path.erase(path.begin() + index);
				path.insert(path.begin() + index, p);
			}
			break;

		case 2:	// Going right
			if (c + 2 >= col - 1) {
				if (count < level) {
					count--;
					continue;
				}
				else {
					exit++;
					if (exit == 2)
						isDone = true;
					bool printed = false;
					if (c + 2 < col) {
						maze[r][c + 2] = END;
						printed = true;
					}
					if (c + 1 < col) {
						if (printed)
							maze[r][c + 1] = ROAD;
						else
							maze[r][c + 1] = END;
					}
				}
			}
			else {
				if (maze[r][c + 2] == WALL) {
					maze[r][c + 1] = ROAD;
					maze[r][c + 2] = ROAD;
					point n;
					n.row = r;
					n.col = c + 2;
					n.left = true;
					path.push_back(n);
				}
				p.right = true;
				path.erase(path.begin() + index);
				path.insert(path.begin() + index, p);
			}
			break;

		case 3: // Going left
			if (c - 2 <= 0) {
				if (count < level) {
					count--;
					continue;
				}
				else {
					exit++;
					if (exit == 2)
						isDone = true;
					bool printed = false;
					if (c - 2 >= 0) {
						maze[r][c - 2] = END;
						printed = true;
					}
					if (c - 1 >= 0) {
						if (printed)
							maze[r][c - 1] = ROAD;
						else
							maze[r][c - 1] = END;
					}
				}
			}
			else {
				if (maze[r][c - 2] == WALL) {
					maze[r][c - 1] = ROAD;
					maze[r][c - 2] = ROAD;
					point n;
					n.row = r;
					n.col = c - 2;
					n.right = true;
					path.push_back(n);
				}
				p.left = true;
				path.erase(path.begin() + index);
				path.insert(path.begin() + index, p);
			}
			break;
		}
	}
}

void addKeys(char** maze, int row, int col, int keys) {
	int count = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	while (count < keys) {
		int r = rand() % row;
		int c = rand() % col;
		if (maze[r][c] == ROAD) {
			maze[r][c] = KEY;
			count++;
		}
	}
}

void printMaze(char** maze, int row, int col, int posR, int posC) {
	for (int r = 0; r < row; r++) {
		cout << "\t\t";
		for (int c = 0; c < col; c++) {
			if (r == posR && c == posC) {
				cout << POSITION << " ";
			}
			else {
				cout << (maze[r][c] == END ? ROAD : maze[r][c]) << " ";
			}
		}
		cout << endl;
	}
}

void play(char** maze, int row, int col, int keys) {
	int startR, startC, endR, endC;
	for (int count = 0, r = 0; r < row && count < 2; r++) {
		for (int c = 0; c < col && count < 2; c++) {
			if (maze[r][c] == END) {
				if (count == 0) {
					startR = r;
					startC = c;
				}
				if (count == 1) {
					endR = r;
					endC = c;
				}
				count++;
			}
		}
	}

	int input = 0, r = startR, c = startC, countKeys = 0;
	bool done = false;


	system("CLS");
	cout << "\n\t\tKEYS LEFT: " << keys - countKeys << "\n\n";
	printMaze(maze, row, col, r, c);

	while (!done)
	{
		input = 0;

		switch ((input = _getch())) {
		case KEY_UP: // Key up
			r--;
			if (r < 0) {
				r++;
			}
			else {
				if (maze[r][c] == WALL) {
					r++;
				}
				else {
					if (maze[r][c] == KEY) {
						countKeys++;
						maze[r][c] = ROAD;
					}
					if (r == endR && c == endC) {
						if (countKeys == keys) {
							done = true;
						}
						else {
							system("CLS");
							printMaze(maze, row, col, r, c);
							cout << "\n\n\t\tYOU HAVE " << keys - countKeys << " KEY(S) MORE TO COLLECT\n\n\n";
							system("PAUSE");
						}
					}
					system("CLS");
					cout << "\n\t\tKEYS LEFT: " << keys - countKeys << "\n\n";
					printMaze(maze, row, col, r, c);
				}
			}
			break;
		case KEY_DOWN:
			r++;
			if (r >= row) {
				r--;
			}
			else {
				if (maze[r][c] == WALL) {
					r--;
				}
				else {
					if (maze[r][c] == KEY) {
						countKeys++;
						maze[r][c] = ROAD;
					}
					if (r == endR && c == endC) {
						if (countKeys == keys) {
							done = true;
						}
						else {
							system("CLS");
							printMaze(maze, row, col, r, c);
							cout << "\n\n\t\tYOU HAVE " << keys - countKeys << " KEY(S) MORE TO COLLECT\n\n\n";
							system("PAUSE");
						}
					}
					system("CLS");
					cout << "\n\t\tKEYS LEFT: " << keys - countKeys << "\n\n";
					printMaze(maze, row, col, r, c);
				}
			}
			break;
		case KEY_LEFT:
			c--;
			if (c < 0) {
				c++;
			}
			else {
				if (maze[r][c] == WALL) {
					c++;
				}
				else {
					if (maze[r][c] == KEY) {
						countKeys++;
						maze[r][c] = ROAD;
					}
					if (r == endR && c == endC) {
						if (countKeys == keys) {
							done = true;
						}
						else {
							system("CLS");
							printMaze(maze, row, col, r, c);
							cout << "\n\n\t\tYOU HAVE " << keys - countKeys << " KEY(S) MORE TO COLLECT\n\n\n";
							system("PAUSE");
						}
					}
					system("CLS");
					cout << "\n\t\tKEYS LEFT: " << keys - countKeys << "\n\n";
					printMaze(maze, row, col, r, c);
				}
			}
			break;
		case KEY_RIGHT:
			c++;
			if (c >= col) {
				c--;
			}
			else {
				if (maze[r][c] == WALL) {
					c--;
				}
				else {
					if (maze[r][c] == KEY) {
						countKeys++;
						maze[r][c] = ROAD;
					}
					if (r == endR && c == endC) {
						if (countKeys == keys) {
							done = true;
						}
						else {
							system("CLS");
							printMaze(maze, row, col, r, c);
							cout << "\n\n\t\tYOU HAVE " << keys - countKeys << " KEY(S) MORE TO COLLECT\n\n\n";
							system("PAUSE");
						}
					}
					system("CLS");
					cout << "\n\t\tKEYS LEFT: " << keys - countKeys << "\n\n";
					printMaze(maze, row, col, r, c);
				}
			}
			break;
		}

	}

}
