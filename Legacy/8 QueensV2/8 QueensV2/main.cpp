
#include <iostream>
#include <string>
#include <Windows.h>

bool *OpenUp;
bool *OpenUpLeft;
bool *OpenUpRight;
int *GridY;
int Dimensions;

struct Pos
{
	int X, Y;
};

void Init()
{
	OpenUp = new bool[Dimensions];
	for (int x = 0; x < Dimensions; ++x) { OpenUp[x] = false; }

	OpenUpLeft = new bool[2 * Dimensions + 1];
	for (int x = 0; x < 2 * Dimensions + 1; ++x) { OpenUpLeft[x] = false; }
	OpenUpRight = new bool[2 * Dimensions + 1];
	for (int x = 0; x < 2 * Dimensions + 1; ++x) { OpenUpRight[x] = false; }

	GridY = new int[Dimensions];
	for (int y = 0; y < Dimensions; ++y) { GridY[y] = -1; }
}

void Display()//fix
{
	/*for (int y = 0; y < Dimensions; ++y)
	{
		for (int x = 0; x < Dimensions; ++x)
		{
			if (OpenUp[x] == y) { std::cout << "# "; }
			else { std::cout << "- "; }
		}
		std::cout << "\n";
	}*/
	static int y = 0;
	static int x = 0;
	for (y = 0; y < Dimensions; ++y)
	{
		for (x = 0; x < GridY[y]; ++x)
		{
			std::cout << "- ";
		}
		if (GridY[y] != -1) { std::cout << "# "; }
		for (x = GridY[y] + 1; x < Dimensions; ++x)
		{
			std::cout << "- ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

bool ClearSquare(int inX, int inY)
{
	//up
	if (OpenUp[inX]) { return false; }
	if (OpenUpLeft[inX + inY]) { return false; }
	if (OpenUpRight[inY - inX + Dimensions]) { return false; }
	//up, left
	/*int x = inX - 1, y = inY - 1;
	for (; x >= 0 && y >= 0; --x, --y)
	{
		//if (GridY[y] == x) { return false; }
	}

	//up, right
	x = inX + 1; y = inY - 1;
	for (; x < Dimensions && y >= 0; ++x, --y)
	{
		if (GridY[y] == x) { return false; }
	}*/
	return true;
}

void Run()
{
	int x = 0, y = 0;
	while (y < Dimensions)
	{
		if (x >= Dimensions)
		{
			--y;

			if (y < 0)
			{
				std::cout << "No Soloutuions\n"; return;
			}

			x = GridY[y];
			OpenUp[x] = false;
			OpenUpLeft[x + y] = false; OpenUpRight[y - x + Dimensions] = false;
			GridY[y] = -1;
			++x;
		}
		else
		{
			if (ClearSquare(x, y))
			{
				GridY[y] = x; OpenUp[x] = true; 
				OpenUpLeft[x + y] = true; OpenUpRight[y - x + Dimensions] = true;
				x = 0; ++y;
			}
			else
			{
				++x;
			}
		}
	}
}

void main()
{
	std::string input;
	std::cout << "Enter Dimensions:";
	std::getline(std::cin, input);
	Dimensions = stoi(input);

	Init();
	Run();
	Display();

	delete[] OpenUp;
	delete[] OpenUpLeft;
	delete[] OpenUpRight;
	delete[] GridY;

	std::cout << "\nPress Enter To Continue";
	std::string out;
	std::getline(std::cin, out);
}
