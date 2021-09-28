#include <iostream>
#include "Field.h"
using namespace std;


const int FS = 5; //field size 5x5

//initiation and destruction methods
Field::Field()
{
	//init array and place blocks on the field
	field = new int[25];
	field[0 * FS + 1] = -1;
	field[0 * FS + 3] = -1;

	field[1 * FS + 1] = 0;
	field[1 * FS + 3] = 0;

	field[2 * FS + 1] = -1;
	field[2 * FS + 3] = -1;

	field[3 * FS + 1] = 0;
	field[3 * FS + 3] = 0;

	field[4 * FS + 1] = -1;
	field[4 * FS + 3] = -1;

	init();
}

//initiate field with random tiles
void Field::init()
{
	srand(time(NULL));
	int c[] = { 5, 5, 5 }, g;

	for (int i = 0; i < 3 * FS; i++)
	{
		do g = rand() % 3; while (c[g] == 0);

		field[i % 5 * FS + i / 5 * 2] = g + 1;
		c[g]--;
	}
}

//reinitiate field (game restart)
void Field::flush()
{
	delete[] field;

	field = new int[25];
	field[0 * FS + 1] = -1;
	field[0 * FS + 3] = -1;

	field[1 * FS + 1] = 0;
	field[1 * FS + 3] = 0;

	field[2 * FS + 1] = -1;
	field[2 * FS + 3] = -1;

	field[3 * FS + 1] = 0;
	field[3 * FS + 3] = 0;

	field[4 * FS + 1] = -1;
	field[4 * FS + 3] = -1;

	init();
}

Field::~Field()
{
	delete[] field;
}

//user and interface methods
//print all field as in rules
void Field::print()
{
	cout << "   1 2 3 4 5" << endl << string(12, '_') << endl;
	for (int i = 0; i < FS; i++)
	{
		cout << i + 1 << "| ";
		for (int j = 0; j < FS; j++)
			if (field[i * FS + j] == -1) cout << "X ";
			else if (field[i * FS + j] == 0) cout << "_ ";
			else cout << field[i * FS + j] << ' ';
		cout << endl;
	}

	cout << endl;
}

//move tile [x;y] to [x_to;y_to]
bool Field::move(int x, int y, int x_to, int y_to)
{
	x--; y--; x_to--; y_to--;
	if (field[y_to * FS + x_to] != 0)
	{
		cout << "You can`t move tiles on occupied tiles!" << endl;
		return false;
	}
	else if ((x != x_to && y != y_to) || (abs(x - x_to) > 1 || abs(y - y_to) > 1))
	{
		cout << "You can`t move tiles by more than 1 square!" << endl;
		return false;
	}
	else if (field[y * FS + x] == -1)
	{
		cout << "You can`t move block tiles!" << endl;
		return false;
	}
	else
	{
		field[y_to * FS + x_to] = field[y * FS + x];
		field[y * FS + x] = 0;
		return true;
	}
}

//check if all tiles on their positions
bool Field::check()
{
	bool is_placed = true;

	for (int i = 0; i < FS && is_placed; i++) if (field[i * FS] != 1) is_placed = false;
	for (int i = 0; i < FS && is_placed; i++) if (field[i * FS + 2] != 2) is_placed = false;
	for (int i = 0; i < FS && is_placed; i++) if (field[i * FS + 4] != 3) is_placed = false;

	return is_placed;
}