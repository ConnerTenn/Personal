
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <thread>

//int **PosData = 0; //List of horizontal elements: [y][x]
				 //std::vector<std::vector<int>> PosData;
int **Array = 0;
int **PosData = 0;//[number][y pos] = x pos

bool **HorizontalList = 0;//[y][number]
bool **VerticalList = 0;


int Size = 0;
bool Play = true;
int StartTime = 0;
bool Process = true;
std::thread *Thread = 0;

void Init()
{
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

	PosData = new int*[Size];
	for (int i = 0; i < Size; i++)
	{
		PosData[i] = new int[Size];
	}

	for (int n = 0; n < Size; n++)
	{
		for (int y = 0; y < Size; y++)
		{
			PosData[n][y] = -1;
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
		if (PosData[i]) { delete[] PosData[i]; PosData[i] = 0; }
	}
	if (PosData) { delete[] PosData; PosData = 0; }

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
		if (PosData[n][Size - i - 1] == i) { return false; }
	}
	return true;
}

inline bool OnDiagonal(int x, int y)
{
	if (x == y) { return true; }
	if (y == -x + Size - 1) { return true; }
	return false;
}

void Display()
{

	int lengthBuff = (int)log10(Size);
	for (int y = 0; y < Size; y++)
	{
		for (int x = 0; x < Size; x++)
		{
			std::string val = std::to_string(Array[y][x]);
			if (val == "0") { val = "-"; }
			//for (int i = (int)val.size(); i < lengthBuff + 1; i++) { val = " " + val; }
			val = std::string((lengthBuff + 1) - (int)val.size(), ' ') + val;
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
	int num = 0;
	bool proceed = false;

	{/*Generate Diagonals*/ }
	{
		//down right
		for (int i = 0; i < Size; i++)
		{
			//PosData[i][i] = i + 1; VerticalList[i][i] = false; HorizontalList[i][i] = false;
			PosData[i][i] = i; Array[i][i] = i + 1; VerticalList[i][i] = false; HorizontalList[i][i] = false;
		}

		//use 8 queens algorthm here
		/*//up right
		int i = 0;
		while (i < Size)
		{
			if (!(i == Size - i - 1))// if intersect with other diagonal
			{
				if (VerticalList[Size - i - 1][num] && HorizontalList[i][num] && CheckValidDiagonalPlace(i, num))//valid place
				{
					//set number and move on
					//PosData[Size - i - 1][i] = num + 1; VerticalList[Size - i - 1][num] = false; HorizontalList[i][num] = false;
					PosData[num][Size - i - 1] = i; VerticalList[Size - i - 1][num] = false; HorizontalList[i][num] = false;
					++i; num = 0;
				}
				else
				{
					//check next number
					++num;
				}
				if (num >= Size)
				{
					//backtrack
					do
					{
						--i;
					}
					while (i == Size - i - 1);
					if (i < 0) { return false; }
					num = PosData[Size - i - 1][i];
				}
			}
			else
			{
				++i;
			}
		}*/

		int i = 0;
		while (i < Size)
		{
			if (!(i == Size - i - 1))
			{
				if (VerticalList[Size - i - 1][num] && HorizontalList[i][num] && CheckValidDiagonalPlace(i, num))//valid place
				{
					//set number and move on
					PosData[num][Size - i - 1] = i; Array[Size - i - 1][i] = num + 1; VerticalList[i][num] = false; HorizontalList[Size - i - 1][num] = false;
					++i; num = 0;
				}
				else
				{
					//check next number
					++num;
				}
				if (num >= Size)
				{
					//backtrack
					do
					{
						--i;
					}
					while (i == Size - i - 1);
					if (i < 0) { return false; }
					num = Array[Size - i - 1][i];
				}
			}
			else
			{
				++i;
			}
		}
	}

	Display(); std::cout << "\n";

	num = 0;
	//until end case
	while (num < Size)
	{
		while (y < Size)
		{
			//Display(); std::cout << "\n";

			if (!process) { return false; }

			/*if (!OnDiagonal(x, y))
			{
				if (HorizontalList[y][num] && VerticalList[x][num])
				{
					PosData[num][y] = x; Array[y][x] = num + 1; HorizontalList[y][num] = false; VerticalList[x][num] = false;
					++y; x = 0;
				}
				else
				{
					++x;

					//backtrack
					if (x >= Size)
					{
						--y;
						if (y < 0) { num--; y = Size - 1; }
						if (num < 0) { return false; }

						x = PosData[num][y];
						HorizontalList[y][num] = true; VerticalList[x][num] = true;
						PosData[num][y] = -1;
						Array[x][y] = 0;

						++x;
					}
				}
			}
			else
			{
				//x = 0; ++y;
				//if (x >= Size)
				//{
				//	++y; x = 0;
				//}
				if (Array[y][x] - 1 == num)
				{
					++y; x = 0;
				}
				else
				{
					++x;

					if (x >= Size)
					{
						++y; x = 0;
					}
				}
			}*/

			//just arrive at new line
			if (!HorizontalList[y][num])//check if number exists already
			{
				++y;
			}
			else if (OnDiagonal(x, y))
			{
				++x;
			}
			else if (HorizontalList[y][num] && VerticalList[x][num] && Array[y][x] == 0)
			{
				PosData[num][y] = x; Array[y][x] = num + 1; HorizontalList[y][num] = false; VerticalList[x][num] = false;
				++y; x = 0;
			}
			else
			{
				++x;
			}

			//if (y < 0) { return false; }

			while (x >= Size)
			{
				do
				{
					--y;
					if (y < 0) { num--; y = Size - 1; }
					if (num < 0) { return false; }

					x = PosData[num][y];
				}
				while (OnDiagonal(x, y));
				

				HorizontalList[y][num] = true; VerticalList[x][num] = true;
				PosData[num][y] = -1;
				Array[y][x] = 0;

				++x;
			}
			//if (x >= Size){}

		}
		++num; x = 0; y = 0;
	}
	return true;
}

void Run()
{
	Init();
	StartTime = (int)clock();
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


void main()
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
			std::cout << "Time:" << (double)(clock() - StartTime) / 1000.0 << "\n";
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
}