#include "stdafx.h"
#include <string>
#include <iostream>
#include <map>

using namespace std;


string DecToAny(string NumberIn, string NextRadixIn)
{
	int Number = atoi(NumberIn.c_str());
	int NextRadix = atoi(NextRadixIn.c_str());
	string NextNum = "";

	map<int, string> Alphabet;

	Alphabet[10] = "A"; Alphabet[11] = "B"; Alphabet[12] = "C"; Alphabet[13] = "D"; Alphabet[14] = "E"; Alphabet[15] = "F"; Alphabet[16] = "G";
	Alphabet[17] = "H"; Alphabet[18] = "I"; Alphabet[19] = "J";	Alphabet[20] = "K";	Alphabet[21] = "L";	Alphabet[22] = "M";	Alphabet[23] = "N";
	Alphabet[24] = "O";	Alphabet[25] = "P";	Alphabet[26] = "Q";	Alphabet[27] = "R";	Alphabet[28] = "S";	Alphabet[29] = "T";	Alphabet[30] = "U";
	Alphabet[31] = "V";	Alphabet[32] = "W";	Alphabet[33] = "X";	Alphabet[34] = "Y";	Alphabet[35] = "Z";

	while (Number>0)
	{
		if (Number % NextRadix >= 10)
		{
			NextNum = Alphabet[Number % NextRadix] + NextNum;
		}
		else
		{
			NextNum = to_string(Number % NextRadix) + NextNum;
		}
		Number = (int)(Number / NextRadix);
	}
	
	//for each (const char a in NumberIn)
	//{
	//	cout << a << " ";
	//}
	return  NextNum;
}