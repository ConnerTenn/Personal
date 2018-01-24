// Mandelbrot.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

struct Complex
{
	long double Num[2] = { 0.0, 0.0 };
	Complex()
	{
		Num[0] = 0;
		Num[1] = 0;
	}
	Complex(long double InNum[2])
	{
		Num[0] = InNum[0];
		Num[1] = InNum[1];
	}
	Complex(long double InNum0, long double InNum1)
	{
		Num[0] = InNum0;
		Num[1] = InNum1;
	}
	Complex operator+(Complex In)
	{
		return { this->Num[0] + In.Num[0], this->Num[1] + In.Num[1] };
	}
	Complex operator-(Complex In)
	{
		return { this->Num[0] - In.Num[0], this->Num[1] - In.Num[1] };
	}
	Complex operator*(Complex In)
	{
		return { this->Num[0] * In.Num[0] - this->Num[1] * In.Num[1], this->Num[0] * In.Num[1] + this->Num[1] * In.Num[0] };
	}
	Complex operator/(Complex In)
	{
		return { this->Num[0] / In.Num[0] - this->Num[1] / In.Num[1], this->Num[0] / In.Num[1] + this->Num[1] / In.Num[0] };
	}
	bool operator==(Complex In)
	{
		return this->Num[0] == In.Num[0] && this->Num[1] == In.Num[1];
	}
};

bool TendsToInfinity(Complex In)
{
	vector<Complex> NumberList = {};
	Complex Total(0, 0);

	bool Continue = true;
	int Count = 0;
	while (Total.Num[0] < 2.0 && Continue)
	{
		Total = Total * Total + In;
		vector<Complex>::iterator It = find(NumberList.begin(), NumberList.end(), Total);
		if (It != NumberList.end() && NumberList.size() > 0)
		{
			Continue = false;
		}
		else
		{
			NumberList.push_back(Total);
		}
		Count++;
		if (Count > 10000) { Continue = false; }
	}
	if (Continue)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void main()
{
	const int NumPerArrayIndex = 30;
	const int ArrayWidth = 4;
	const Complex Offset = {0, 0};
	//vector<vector<int>> Array[ArrayXMax * 2 * NumPerArrayIndex][ArrayXMax * 2 * NumPerArrayIndex];
	//vector<vector<int>> Array( );//ArrayXMax * 2 * NumPerArrayIndex, ArrayXMax * 2 * NumPerArrayIndex);
	char Array[ArrayWidth * NumPerArrayIndex + 1][ArrayWidth * NumPerArrayIndex + 1];

	vector<Complex> NumberList = {};

	//Complex Number(-1.5, 0);
	//TendsToInfinity(Number) ? cout << "Infinity\n" : cout << "Finite\n";

	for (int Y = ArrayWidth * NumPerArrayIndex; Y >= 0; Y--)
	{
		for (int X = 0; X <= ArrayWidth * NumPerArrayIndex; X++)
		{
			cout << ((X - (ArrayWidth * NumPerArrayIndex) / 2.0) / NumPerArrayIndex) + Offset.Num[0] << " + " << ((Y - (ArrayWidth * NumPerArrayIndex) / 2.0) / NumPerArrayIndex) + Offset.Num[1] << "i ::\t\t";
			//double a = (X - (ArrayWidth * NumPerArrayIndex) / 2.0) / NumPerArrayIndex;
			if (TendsToInfinity(Complex(((X - (ArrayWidth * NumPerArrayIndex) / 2.0) / NumPerArrayIndex) + Offset.Num[0], ((Y - (ArrayWidth * NumPerArrayIndex) / 2.0) / NumPerArrayIndex) + Offset.Num[1])))
			{
				Array[X][Y] = '#';
				cout << "Infinity\n";
			}
			else
			{
				Array[X][Y] = ' ';
				cout << "Finite\n";
			}
		}
	}

	for (int Y = ArrayWidth * NumPerArrayIndex; Y >= 0; Y--)
	{
		for (int X = 0; X <= ArrayWidth * NumPerArrayIndex; X++)
		{
			cout << Array[X][Y];
		}
		cout << "\n";
	}

	int a = 0;
	std::cin >> a;
}

