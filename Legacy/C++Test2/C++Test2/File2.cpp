#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;
using namespace System;

int add(int a = 0, int b = 0)
{
	return a + b;
}

void end()
{
	Console::WriteLine();
	Console::Write("Press [Enter] To Continue.");
	Console::ReadLine();
	exit(0);
}