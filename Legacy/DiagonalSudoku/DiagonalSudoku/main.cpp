
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <thread>

int **Array = 0; //List of horizontal elements: [y][x]
//std::vector<std::vector<int>> Array;
int Size = 0;
bool Play = true;
int StartTime = 0;
bool Process = true;
std::thread *Thread;

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
}

void Shutdown()
{
	//Array.clear();
	int Size = 0;
	bool Play = true;
	int StartTime = 0;
	
	//std::cout << "begin\n";
	for (int i = 0; i < Size; ++i)
	{
		if (Array[i]) { delete[] Array[i]; Array[i] = 0; }
	}
	//std::cout << "middle\n";
	if (Array) { delete[] Array; Array = 0; }
	//std::cout << "end\n";
	
}

bool CheckValidPlace(int &x, int &y, int &num)
{
	if (x >= Size || y >= Size) { return false; }

	if (Array[y][x] != 0) { return false; }

	//check vertical
	for (int i = y; i >= 0; --i)
	{
		if (Array[i][x] == num) { return false; }
	}

	//check diagonal
	//check if on up left diagonal
	if (y == x)
	{
		for (int i = y; i >= 0; --i)
		{
			if (Array[i][i] == num) { return false; }
		}
	}
	//check if on down left diagonal
	if (y == -x + Size - 1)
	{
		for (int i = y; i >= 0; --i)
		{
			if (Array[i][Size - i - 1] == num) { return false; }
		}
	}
	
	return true;
}

bool CheckValidDiagonal(int &num)
{
	bool containNum = false;
	//check if on up left diagonal
	for (int i = 0; i < Size && !containNum; ++i)
	{
		if (Array[i][i] == num) { containNum = true; }
	}

	if (!containNum) { return false; }
	containNum = false;

	//check if on down left diagonal
	for (int i = 0; i < Size && !containNum; ++i)
	{
		if (Array[i][Size - i - 1] == num) { containNum = true; }
	}

	return containNum;
}

int FindNumInRow(int y, int num)
{
	for (int x = 0; x < Size; ++x)
	{
		if (Array[y][x] == num) { return x; }
	}
	return -1;
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
	int num = 1;
	int x = 0, y = 0;
	StartTime = (int)clock();

	//until end case
	while (num <= Size)
	{
		//std::cout << "Num:" << num << "\n";
		//{ static int previousNum = 0; if (num != previousNum) { previousNum = num; std::cout << "Num:" << num << "\n"; } }

		while (y < Size)
		{
			if (!process) { return false; }
			//{
				//const int max = 5000;
				//if ((clock() - StartTime) % max == max - 1)
				//{
					//Display(); 
					//std::cout << "Time:" << (double)(clock() - StartTime)/1000.0 << "\n\n";
				//}
			//}

			//Array[y][x] = num;
			if (CheckValidPlace(x, y, num))
			{
				Array[y][x] = num;
				x = 0;
				++y;
				//std::cout << "\n\n"; Display();
			}
			else
			{
				++x;
				
				if (x >= Size)
				{
					//backtrack
					--y;
					if (y < 0) { num--; y = Size - 1; }
					if (num <= 0) { return false; }
					//if (y < 1) { return false; }
					x = FindNumInRow(y, num);
					Array[y][x] = 0;
					++x;
				}
			}
		}
		if (CheckValidDiagonal(num))
		{
			++num;
			x = 0;
			y = 0;
		}
		else
		{
			--y;
			x = FindNumInRow(y, num);
			Array[y][x] = 0;
			++x;
		}
	}
	return true;
}

void Run()
{
	Init();
	if (Calculate(Process))
	{
		std::cout << "\nSolved:\n";
		Display();
	}
	else
	{
		std::cout << "No Soloution\n";
	}
	std::cout << "Time:" << (double)(clock() - StartTime) / 1000.0 << "\n\n";
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
			Thread->join();
			delete Thread;
		}
		else if (in == "end")
		{
			Process = false;
			Thread->join();
			delete Thread;
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
				Process = true;
				Thread = new std::thread(Run);
			}
		}
	}
	
	//std::cout << "\nPress Enter To Continue";
	//std::string out;
	//std::getline(std::cin, out);
}