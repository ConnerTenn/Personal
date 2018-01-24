// StringParsing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost_1_59_0\boost\algorithm\string.hpp>
#include <boost_1_59_0\boost\algorithm\algorithm.hpp>
#include <vector>
#include <iostream>
#include <string>         // std::string
#include <cstddef>        // std::size_t
using namespace std;
using namespace boost;



void main()
{
	string str("Please, replace the vowels in this sentence by asterisks.");
	size_t found = str.find_first_of("aeiou");
	while (found != string::npos)
	{
		str[found] = '*';
		found = str.find_first_of("aeiou", found + 1);
	}
	
	cout << str << '\n';
	
	int a;
	cin >> a;
}

