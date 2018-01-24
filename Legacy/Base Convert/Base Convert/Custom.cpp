//#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

int add(int a, int b)
{
	return(a + b);
}

void end()
{
	cout << endl;
	cout << "Press [Enter] To Continue.";
	string a;
	getline(cin, a);
	exit(0);
}