
#include <iostream>
#include <string>

#include "Parser.h"
#include "ParseMath.h"
#include "InterpretMath.h"

/*
void foo()
{
	std::cout << "Works!\n";
}

void (*foo2())()
{
	return &foo;
}


void (*(*foo3())())()
{
	return &foo2;
}

typedef void (*qq)();

void *foo4();
void *foo5();

void *foo4()
{
	std::cout << "4\n";
	return foo5;
}

void *foo5()
{
	std::cout << "5\n";
	return foo4;
}
*/


void main()
{
	std::vector<std::string> parseList;
	ParseMath parser;
	parseList = parser.Parse("(   (2352.33              *2)  + 234.90-621)");//add end function
	
	int val = 10;
	Test test(val);
	val = 20;
	std::cout << test.Val << "\n";

	std::cout << '"';
	for (int i = 0; i < parseList.size(); i++)
	{
		std::cout << parseList[i] << "\"";
	}
	std::cout << "\n";
	//void *(*a)() = foo5;

	/*void *a = foo5();

	void *b = ((void *(*)())a)();

	((void *(*)())b)();

	std::cout << std::hex << ((unsigned int *)foo5()) << "\n" << (unsigned int *)(((void *(*)())foo5())()) << "\n";//print out the function pointer to foo4 as a hex integer
	*/
	
	std::string out = "Press Enter To Continue:"; std::cout << out;
	std::getline(std::cin, out);
}
