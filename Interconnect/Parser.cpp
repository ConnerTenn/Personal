
#include "Parser.h"
using namespace PARSE;

std::vector<std::string> Parser::Parse(std::string in, Result &result)
{
	//void (Parser::*h)() = &Parser::Start;
	//((*this).*(h))();
	//(this->*(h))();
	String = in;

	//bool run = true;
	//Result result;
	//bool run = Start(String[0]) == Result::Continue;//change run to result
	result = Start(String[0]);
	while (result == Result::Continue)
	{
		result = Call(String[Index], String[Index + 1]);
		Index++;
		if (Index + 1 >= (int)String.length())
		{
			EndOfString = true;
		}
		else
		{
			EndOfString = false;
		}


		if (Index >= (int)String.length())
		{
			result = Result::End;
		}
	}

	if (result == Result::End)
	{
		result = End();
	}

	if (result == Error)
	{
		std::cout << "Parse Error\n";
	}

	//result == Result::End ? true : false;

	//return ParseOut;
	return {};
}

std::vector<std::string> Parser::Parse(std::string in)
{
	Result result;
	return Parse(in, result);
}

Result Parser::Call(char current, char next)
{
	return Result::End;
}

Result Parser::Start(char next)
{
	return Result::End;
}

Result Parser::End()
{
	return Result::End;
}

