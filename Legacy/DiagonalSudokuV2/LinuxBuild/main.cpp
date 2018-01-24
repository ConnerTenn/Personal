
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <thread>
#include <math.h>

int **Array = 0; //List of horizontal elements: [y][x]
//std::vector<std::vector<int>> Array;
bool **HorizontalList = 0;
bool **VerticalList = 0;

int Size = 0;
bool Play = true;
int StartTime = 0;
bool Process = true;
std::thread *Thread = 0;

void Init()
{
	//for (int i = 0; i < Size; i++) { Array.push_back(std::vector<int>(Size, 0)); }
	Array = new int*[Size];
	for (int i = 0; i < Size; i++)
	{
		Array[i] = new int[Size];
	}

	for (int y = 0; y < Size; y++)
	{
		for (int x = 0; x < Size; x++)
		{
			Array[y][x] = 0;
		}
	}

	HorizontalList = new bool*[Size];
	for (int i = 0; i < Size; i++)
	{
		HorizontalList[i] = new bool[Size];
	}

	for (int i = 0; i < Size; i++)
	{
		for (int n = 0; n < Size; n++)
		{
			HorizontalList[i][n] = true;
		}
	}

	VerticalList = new bool*[Size];
	for (int i = 0; i < Size; i++)
	{
		VerticalList[i] = new bool[Size];
	}

	for (int i = 0; i < Size; i++)
	{
		for (int n = 0; n < Size; n++)
		{
			VerticalList[i][n] = true;
		}
	}
}

void Shutdown()
{
	int Size = 0;
	bool Play = true;
	int StartTime = 0;

	for (int i = 0; i < Size; ++i)
	{
		if (Array[i]) { delete[] Array[i]; Array[i] = 0; }
	}
	if (Array) { delete[] Array; Array = 0; }

	for (int i = 0; i < Size; ++i)
	{
		if (HorizontalList[i]) { delete[] HorizontalList[i]; HorizontalList[i] = 0; }
	}
	if (HorizontalList) { delete[] HorizontalList; HorizontalList = 0; }

	for (int i = 0; i < Size; ++i)
	{
		if (VerticalList[i]) { delete[] VerticalList[i]; VerticalList[i] = 0; }
	}
	if (VerticalList) { delete[] VerticalList; VerticalList = 0; }
}

bool CheckValidDiagonalPlace(int &x, int &n)
{
	for (int i = x - 1; i >= 0; --i)
	{
		if (Array[Size - i - 1][i] == n + 1) { return false; }
	}
	return true;
}

bool OnDiagonal(int x, int y)
{
	if (x == y) { return true; }
	if (y == -x + Size - 1) { return true; }
	return false;
}

void Display()
{
	int buffer = (int)log10(Size);
	for (int y = 0; y < Size; y++)
	{
		for (int x = 0; x < Size; x++)
		{
			std::string val = std::to_string(Array[y][x]);
			if (val == "0") { val = "-"; }
			//for (int i = (int)val.size(); i < buffer + 1; i++) { val = " " + val; }
			val = std::string((buffer + 1) - (int)val.size(), ' ') + val;
			std::cout << val << " ";
		}
		std::cout << "\n";
	}
}

bool Calculate(bool &process)
{
	//int num = 1;
	int x = 0;
	int y = 0;
	int n = 0;
	bool proceed = false;
	StartTime = (int)clock();

	{/*Generate Diagonals*/}
	{
		//down right
		for (int i = 0; i < Size; i++)
		{
			Array[i][i] = i + 1; VerticalList[i][i] = false; HorizontalList[i][i] = false;
		}

		//up right
		int i = 0;
		while (i < Size)
		{
			if (!(i == Size - i - 1))
			{
				if (VerticalList[Size - i - 1][n] && HorizontalList[i][n] && CheckValidDiagonalPlace(i, n))//valid place
				{
					//set number and move on
					Array[Size - i - 1][i] = n + 1; VerticalList[Size - i - 1][n] = false; HorizontalList[i][n] = false;
					++i; n = 0;
				}
				else
				{
					//check next number
					++n;
				}
				if (n >= Size)
				{
					//backtrack
					do
					{
						--i;
					}
					while (i == Size - i - 1);
					if (i < 0) { return false; }
					n = Array[Size - i - 1][i];
				}
			}
			else
			{
				++i;
			}
		}
	}

	n = 0;
	//Array[3][0] = 2; VerticalList[3][1] = false; HorizontalList[0][1] = false;
	//Array[2][1] = 1; VerticalList[2][0] = false; HorizontalList[1][0] = false;
	//Array[1][2] = 4; VerticalList[1][3] = false; HorizontalList[2][3] = false;
	//Array[0][3] = 3; VerticalList[0][2] = false; HorizontalList[3][2] = false;

	Display(); std::cout << "\n\n";

	//until end case

	while (y < Size && process)
	{
		proceed = false;

		while (!proceed && n < Size && process)
		{
			if (OnDiagonal(x, y))
			{
				proceed = true; n = 0; ++x;
				if (x >= Size) { ++y; x = 0; }
			}
			else
			{
				if (VerticalList[y][n] && HorizontalList[x][n])
				{
					Array[y][x] = n + 1; VerticalList[y][n] = false; HorizontalList[x][n] = false;
					proceed = true; n = 0; ++x;
					if (x >= Size) { ++y; x = 0; }
				}
				else
				{
					++n;
				}
			}
		}
		if (!proceed) 
		{
			do
			{
				--x;
			}
			while (OnDiagonal(x, y));
			if (x < 0) { x = Size - 1; --y; }
			//if (x < 0) { --y; x = Size - 1; }
			n = Array[y][x] - 1; Array[y][x] = 0;
			VerticalList[y][n] = true; HorizontalList[x][n] = true;
			++n;
		}
		//Display(); std::cout << "\n";
	}

	return true;
}

void Run()
{
	Init();
	bool result = Calculate(Process);
	int endTime = (clock() - StartTime);
	if (result)
	{
		std::cout << "\nSolved:\n";
		Display();
	}
	else
	{
		std::cout << "No Soloution\n";
	}
	std::cout << "Time:" << (double)endTime / 1000.0 << "\n\n";
	Shutdown();
	Process = false;
}


int main()
{
	Process = false;
	while (Play)
	{
		std::string in;

		/*{
		bool proceed = false;
		while (!proceed)
		{
		proceed = true;
		std::cout << "Enter Grid Size:"; std::getline(std::cin, in);
		try { Size = stoi(in); }
		catch (...) { proceed = false; }
		if (in == "exit") { Play = false; proceed = true; }
		}
		}*/

		//std::cout << ">"; 
		std::getline(std::cin, in);
		if (in == "exit")
		{
			Play = false;
			Process = false;
			if (Thread) { Thread->join(); delete Thread; Thread = 0; }
		}
		else if (in == "end")
		{
			Process = false;
			if (Thread) { Thread->join(); delete Thread; Thread = 0; }
		}
		else if (in == "print" && Process)
		{
			Display();
			std::cout << "Time:" << (double)(clock() - StartTime) / 1000.0 << "\n\n";
		}
		else if (!Process && [=]() { try { Size = stoi(in); } catch (...) { return false; } return true; }())//check if int
		{
			if (Size > 0)
			{
				if (Thread) { Thread->join(); delete Thread; Thread = 0; }
				Process = true;
				Thread = new std::thread(Run);
			}
		}
	}

	//std::cout << "\nPress Enter To Continue";
	//std::string out;
	//std::getline(std::cin, out);
	return 0;
}

