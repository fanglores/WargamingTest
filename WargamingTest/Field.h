#pragma once

class Field
{
private:
	int* field;

public:
	Field();

	void init();

	void print();

	bool move(int, int, int, int);

	bool check();

	void flush();

	~Field();
};