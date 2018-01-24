// 8 Queens.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include<Windows.h>

using namespace std;

vector<int> Grid;
int GridSize = 40;
//int Grid[GridSize];
int X, Y = 0;

void Init()
{
	for (int i = 0; i < GridSize; i++)
	{
		Grid.push_back(-1);
	}
}

bool Check()
{
	//Vertical Check
	for (int y = Y; y >= 0; y--)
	{
		if (Grid[y] == X)
		{
			return false;
		}
	}

	//Diaginal Check
	int x = 0;
	for (int y = Y-1; y >= 0; y--)
	{
		//Left
		x++;
		if (Grid[y] == X - x)
		{
			return false;
		}

		//Right
		if (Grid[y] == X + x)
		{
			return false;
		}
	}

	return true;
}

void DisplayGrid()
{
	for (int y = 0; y < GridSize; y++)
	{
		int PieceX = Grid[y];
		for ( int x = 0; x < PieceX; x++ )
		{
			cout << "- ";
		}
		if (PieceX >= 0)
		{
			cout << "# ";
		}
		for (int x = PieceX; x < GridSize - 1; x++)
		{
			cout << "- ";
		}
		cout << "\n";
	}
	cout << "\n";

	/*
	do
	{

	} while (GetAsyncKeyState(VK_RETURN) >= 0);
	do
	{

	} while (GetAsyncKeyState(VK_RETURN) < 0);
	*/
}

void Play();
void Finish();

void Play()
{
	do
	{
		if (Check())
		{
			Grid[Y] = X;
			Y += 1;
			X = 0;

			//DisplayGrid();
		}
		else
		{
			X += 1;
		}

		if (X > GridSize - 1)
		{
			Grid[Y] = -1;
			Y -= 1;


			if (Y == -1)
			{
				cout << "All Possible Soloutions Have Been Generated!\n\n";

				Sleep(3000);

				cout << "Press ENTER To Continue\n";
				do
				{

				} while (GetAsyncKeyState(VK_RETURN) >= 0);
				exit(0);
			}


			X = Grid[Y];
		}
	} 
	while (Y < GridSize);

	Finish();
}

void Finish()
{
	cout << "DONE!\n";
	DisplayGrid();
	cout << "\nGenerate Another? y/n: \n";
	char ans;
	cin >> ans;
	if (ans == 'y' || ans == 'Y')
	{
		cout << "\n\n";
		Y -= 1;
		Play();
	}
}


void main()
{
	cout << "Enter Grid Size:";
	cin >> GridSize;
	cout << "\n\n";

	Init();	

	Play();
}

