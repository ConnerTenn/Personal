
#include "Parser.h"
using namespace PARSE;

Result InputParser::Call(char current, char next)
{
	return (this->*Func)(next);
}


Result InputParser::Start(char next)
{
	std::cout << "Start: " << next << "\n";

	if (next == ' ')
	{
		Func = &InputParser::Whitespace;
	}
	else if (isalpha(next))
	{
		Func = &InputParser::Identifier;
	}
	else if (INTC::IsOperator(next, 0))
	{
		Func = &InputParser::Operator;
	}


	return Result::Continue;
}

Result InputParser::End()
{
	return Result::End;
}


Result InputParser::Identifier(char next)
{
	std::cout << "Identifier: " << next << "\n";
	return Result::Continue;
}

Result InputParser::Operator(char next)
{
	std::cout << "Operator: " << next << "\n";
	return Result::Continue;
}

Result InputParser::Whitespace(char next)
{
	std::cout << "Whitespace: " << next << "\n";
	return Result::Continue;
}
