// ControllTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Custom.h"

using namespace std;


void main()
{
	int SpaceCount = 0;

	for (int Count = 0; Count < 80; Count++)
	{
		char Char = getchar();
		switch (Char)
		{
			case '\n':
				Count = 80;
				break;
			case ' ':
				SpaceCount++;
		}
	}
	cout << "You Typed " << SpaceCount << " Spaces" << endl;

	end();

	//return 0;
}

