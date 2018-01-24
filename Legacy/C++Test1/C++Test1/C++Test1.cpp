// C++Test1.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;
using namespace System;


class CustomFunc 
{
	public:
		int one;
		static int add(int a, int b)
		{
			return a + b;
		}
		void Exit()
		{
			cout << endl;
			cout << "Press [Enter] To Continue";
			Console::ReadLine();
			exit(0);
		}
};

void main()
{
	CustomFunc Func;
	Func.one = 2;
	int a = 5;
	int b = 7;
	cout << a << "+" << b << "=" << Func.add(a, b) << endl;

	
	Func.Exit();
}
