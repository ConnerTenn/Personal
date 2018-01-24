// Define_A_Line.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

struct Point
{
	float x;
	float y;
};

struct Line
{
	float a;
	float b;
	float c;
};

void main()
{
	Point Start;
	Point End;
	Line Equation;

	cout << "Enter X1:";
	cin >> Start.x;
	cout << "Enter Y1:";
	cin >> Start.y;
	cout << "\n";

	cout << "Enter X2:";
	cin >> End.x;
	cout << "Enter Y2:";
	cin >> End.y;
	cout << "\n";

	Equation.a = -(End.y - Start.y);
	Equation.b = (End.x - Start.x);
	Equation.c = Equation.a * Start.x + Equation.b * Start.y;

	cout << "Points:\n";
	cout << "\n" << "{" << Start.x << ", " << Start.y << "}, {" << End.x << ", " << End.y << "}\n";
	cout << "\n\nEquation:\n";
	cout << "\n" << Equation.a << " * X + " << Equation.b << " * Y = " << Equation.c << "\n";

	int a;
	cin >> a;
}

