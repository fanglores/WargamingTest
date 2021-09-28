#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "Field.h"
using namespace std;

int secure_cin();
bool secure_cin_mp(int*);
void sys_pause(string);
void print_rules();

int main()
{
	Field gameField;
	int ans = -1;

	//main infinite game loop (play until you want to exit)
	while (ans != 3)
	{
		cout << "\t\tWelcome to the Nightmare Realm MiniGame!" << endl << endl;
		cout << "1. New game" << endl;
		cout << "2. Rules" << endl;
		cout << "3. Exit" << endl << endl;
		cout << "Enter a number of option: ";

		ans = secure_cin();

		switch (ans)
		{
		case 1:
		{
			gameField.flush();

			//while tiles are not in correct poition take user input
			int* p;
			while (!gameField.check())
			{
				system("cls");
				gameField.print();
				cout << "Enter row and column(\"y x y x\"): ";

				p = new int[4];
				if (!secure_cin_mp(p)) sys_pause("Input error. Press any key to try again...");
				else
				{
					if (!gameField.move(p[1], p[0], p[3], p[2])) sys_pause("Runtime error. Press any key to try again...");
				}
				delete[] p;

			}

			cout << string(40, '=') << endl;
			cout << "You won! Returning to main menu..." << endl;

			Sleep(4000);
			system("cls");
			break;
		}

		case 2:
			print_rules();
			break;

		case 3:
			exit(0);

		default:
			sys_pause("Input error. Press any key to try again...");
			system("cls");
		}
	}
}

//secure input function. Helps to avoid incorrect user`s input
int secure_cin()
{
	string str;
	getline(cin, str);
	if (str.size() > 1) return -1;
	else
	{
		if (str[0] >= '0' && str[0] <= '9') return (str[0] - '0');
		else return -1;
	}
}

//secure input funtion for multiply input data
bool secure_cin_mp(int* out)
{
	string str;
	getline(cin, str);

	int cnt = 0;
	bool is_letter = false;
	for(int i = 0; i < str.size() && cnt != 4; i++)
	{
		if (str[i] >= '1' && str[i] <= '5')
		{
			out[cnt] = static_cast<int>(str[i] - '0');
			cnt++;
		}
		else if (str[i] != ' ') is_letter = true;
	}

	if (cnt != 4) return false;
	else if (str.size() != 7 || is_letter)
	{
		cout << ">>>>Input warning. Interpreted as: ";
		for (int i = 0; i < 4; i++) cout << out[i] << ' ';
		cout << endl << endl;
		Sleep(1500);
	}

	return true;
}

//self-made system("pause") function, which prints message and holds programm execution until any key is pressed
void sys_pause(string out)
{
	string tmp;
	cout << ">>>>" << out << endl;
	cin.clear();
	cin.sync();
	_getch();
}

void print_rules()
{
	system("cls");
	cout << "Use only single-digit numbers." << endl;
	cout << "In the main menu you can select one of the options." << endl;
	cout << "When you start a new game you will be presented with the generated field." << endl;
	cout << "You need to put all cells with number 1 in the first column,\nwith 2 in the second column, with 3 in the third column." << endl;
	cout << "To do this, enter the coordinates of the cells you want to swap\nin the format \"y x y x\"." << endl;
	cout << "The first pair of coordinates is where to move the cell from,\nand the second pair is where." << endl;
	cout << "Blocked cells are displayed as \'X\'. Empty cells are displayed as \'_\'." << endl;
	cout << "Enjoy the game!" << endl << endl;

	sys_pause("Press any key to return to the main menu...");
	system("cls");
}