
#pragma once
#include "Parser.h"

class ParseMath : public Parser
{

public:

public:
	Result (ParseMath::*Func)(char current, char next);

	std::string NumberBuff;

	ParseMath();

	Result Call(char current, char next);
	Result Start(char next);
	Result End();

	Result WhitespaceAftNum(char current, char next);
	Result WhitespaceAftOpe(char current, char next);
	Result OpenBrackets(char current, char next);
	Result CloseBrackets(char current, char next);
	Result NumberInt(char current, char next);
	Result NumberDec(char current, char next);
	Result Decimal(char current, char next);
	Result Operation(char current, char next);
};
