// C++Test1.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;
using namespace System;

int add(int, int);
void end();

void main()
{
	int a = 1;
	int b = 5;
	cout<< a << "+" << b << "=" <<add(a, b) << endl;

	end();
}
