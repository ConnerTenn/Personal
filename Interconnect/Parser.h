
#ifndef PARSER_H
#define PARSER_H
//#pragma once

//#include <iostream>
//#include <string>
//#include <vector>
#include "Interconnect.h"

namespace PARSE
{
#define str(s) std::string(1, s)

	enum Result
	{
		End,
		Error,
		Continue
	};

	class Parser
	{
	protected:
		std::string String;
		int Index = 0;

	public:
		//std::vector<std::string> ParseOut;
		bool EndOfString = false;

	public:

		std::vector<std::string> Parse(std::string in, Result &result);
		std::vector<std::string> Parse(std::string in);
		virtual Result Call(char current, char next);

		virtual Result Start(char next);
		virtual Result End();
	};

	class InputParser : public Parser
	{
	private:
		//u8 OperatorState = 0;
		//u8 IdentifierState = 0;

		Result (InputParser::*Func)(char next);

	public:
		Result Call(char current, char next);

		Result Start(char next);
		Result End();

		Result Identifier(char next);
		//Result Operator(char next);
		Result Whitespace(char next);
	};
}

#endif // !PARSER_H
