
#pragma once
#include "Cmd.h"

void Hello(std::vector<std::string> args)
{
	if (args.size() == 1)
	{
		std::cout << "HELLO " << args[0] << "! Nice to meet you!\n";
	}
}


void Test1(std::vector<std::string> args)
{
	if (args.size() == 0)
	{
		std::cout << "Test1 Confirmed\n";
	}
}

void Test2(std::vector<std::string> args)
{
	if (args.size() == 0)
	{
		std::cout << "Test2 Confirmed\n";
	}
}
