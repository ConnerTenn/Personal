// Base Convert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

#include "Custom.h"
#include "OtherFiles.h"

using namespace std;


int main()
{
	cout << "######################" << endl;
	cout << "#                    #" << endl;
	cout << "#   Base Converter   #" << endl;
	cout << "#                    #" << endl;
	cout << "######################" << endl;
	cout << "Enter a Number: ";
	string NumberIn;
	getline(cin, NumberIn);

	cout << "Enter The Radix For The Number: ";
	string CurrentRadixIn;
	getline(cin, CurrentRadixIn);

	cout << "Enter The Radix For The New Number: ";
	string NextRadixIn;
	getline(cin, NextRadixIn);

	//cout << DecToAny(AnyToDec(NumberIn, CurrentRadixIn), NextRadixIn) << endl;
	cout << endl << NumberIn << "[" << CurrentRadixIn << "]" << " = " << DecToAny(AnyToDec(NumberIn, CurrentRadixIn), NextRadixIn) << "[" << NextRadixIn << "]" << endl;
	end();
	return 0;
}

