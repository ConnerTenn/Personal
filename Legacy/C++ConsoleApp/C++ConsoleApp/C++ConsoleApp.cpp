// C++ConsoleApp.cpp : main project file.

#include "stdafx.h"
#include <iostream>
using namespace System;
using namespace std;

int main()
{
    Console::WriteLine("Hello World");
	std::cout << "Hi ";
	cout << "HI2" << endl;
	cout << "Press [Enter] To Continue.";
	int a;
	cin >> a;
	cout << a.GetType() << endl;
	cout << "Press [Enter] To Continue.";
	cin >> a;
	return 0;
}
