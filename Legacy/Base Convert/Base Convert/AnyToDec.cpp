#include "stdafx.h"
#include <string>
#include <iostream>
#include <map>

using namespace std;


string AnyToDec(string NumberIn, string CurrentRadixIn)
{
	int Number = atoi(NumberIn.c_str());
	int CurrentRadix = atoi(CurrentRadixIn.c_str());
	int NextNum = 0;

	map<char, int> Alphabet;

	Alphabet['A'] = 10; Alphabet['B'] = 11; Alphabet['C'] = 12; Alphabet['D'] = 13; Alphabet['E'] = 14; Alphabet['F'] = 15; Alphabet['G'] = 16;
	Alphabet['H'] = 17; Alphabet['I'] = 18; Alphabet['J'] = 19; Alphabet['K'] = 20; Alphabet['L'] = 21; Alphabet['M'] = 22; Alphabet['N'] = 23;
	Alphabet['O'] = 24; Alphabet['P'] = 25; Alphabet['Q'] = 26; Alphabet['R'] = 27; Alphabet['S'] = 28; Alphabet['T'] = 29; Alphabet['U'] = 30;
	Alphabet['V'] = 31; Alphabet['W'] = 32; Alphabet['X'] = 33; Alphabet['Y'] = 34; Alphabet['Z'] = 35;

	string ReverseNum = "";
	for each (const char Value in NumberIn)
	{
		ReverseNum = Value + ReverseNum;
	}
	//cout << ReverseNum << endl;

	int i = 0;
	for each (const char Value in ReverseNum)
	{
		//cout << "Value=" << Value-'0' <<  "      i=" << i << endl;
		if (Value - '0' <= 10)
		{
			NextNum = NextNum + (Value - '0') * (int)pow( CurrentRadix, i);
			//cout << "NextNum=" << to_string((Value - '0') * (int)pow(CurrentRadix, i)) << endl;
		}
		else
		{
			NextNum = NextNum + (Alphabet[Value]) * (int)pow(CurrentRadix, i);
		}
		i++;
	}
	//cout << endl << Alphabet['C'];
	return to_string( NextNum );
}