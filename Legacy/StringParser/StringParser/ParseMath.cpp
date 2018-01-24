
#include "ParseMath.h"


ParseMath::ParseMath()
{
	//Func = &ParseMath::Start;
}

Result ParseMath::Call(char current, char next)
{
	return (this->*Func)(current, next);
}

Result ParseMath::Start(char next)
{
	if (EndOfString)
	{
		return Result::End;
	}
	else if (next == '(')
	{
		Func = &ParseMath::OpenBrackets;
		return Result::Continue;
	}
	else if (next >= '0' && next <= '9')
	{
		Func = &ParseMath::NumberInt;
		return Result::Continue;
	}
	else if (next == ' ')
	{
		Func = &ParseMath::WhitespaceAftOpe;
		return Result::Continue;
	}
	
	return Result::Error;
}

Result ParseMath::End()
{
	int count = 0;
	for (int i = 0; i < ParseOut.size(); i++)
	{
		if (ParseOut[i] == "(") { count++; }
		else if (ParseOut[i] == ")") { count--; }
	}

	return count == 0 ? Result::End : Result::Error;
}

Result ParseMath::WhitespaceAftNum(char current, char next)
{
	if (EndOfString)
	{
		return Result::End;
	}
	else if (next == ' ')
	{
		Func = &ParseMath::WhitespaceAftNum;
		return Result::Continue;
	}
	else if (next == '+' || next == '-' || next == '*' || next == '/')
	{
		Func = &ParseMath::Operation;
		return Result::Continue;
	}

	return Result::Error;
}

Result ParseMath::WhitespaceAftOpe(char current, char next)
{
	if (EndOfString)
	{
		return Result::End;
	}
	else if (next == ' ')
	{
		Func = &ParseMath::WhitespaceAftOpe;
		return Result::Continue;
	}
	else if (next >= '0' && next <= '9')
	{
		Func = &ParseMath::NumberInt;
		return Result::Continue;
	}
	else if (next == '(')
	{
		Func = &ParseMath::OpenBrackets;
		return Result::Continue;
	}

	return Result::Error;
}

Result ParseMath::OpenBrackets(char current, char next)
{
	ParseOut.push_back(str(current));

	if (EndOfString)
	{
		return Result::End;
	}
	else if (next == ' ')
	{
		Func = &ParseMath::WhitespaceAftOpe;
		return Result::Continue;
	}
	else if (next == '(')
	{
		Func = &ParseMath::OpenBrackets;
		return Result::Continue;
	}
	else if (next >= '0' && next <= '9')
	{
		Func = &ParseMath::NumberInt;
		return Result::Continue;
	}

	return Result::Error;
}

Result ParseMath::CloseBrackets(char current, char next)
{
	ParseOut.push_back(str(current));

	if (EndOfString)
	{
		return Result::End;
	}
	else if (next == ' ')
	{
		Func = &ParseMath::WhitespaceAftNum;
		return Result::Continue;
	}
	else if (next == '+' || next == '-' || next == '*' || next == '/')
	{
		Func = &ParseMath::Operation;
		return Result::Continue;
	}
	return Result::Error;
}

Result ParseMath::NumberInt(char current, char next)
{
	//NumberBuff += String[Index];
	NumberBuff += current;

	if (EndOfString)
	{
		ParseOut.push_back(NumberBuff);
		NumberBuff = "";
		return Result::End;
	}
	else if (next == ' ')
	{
		ParseOut.push_back(NumberBuff);
		NumberBuff = "";
		Func = &ParseMath::WhitespaceAftNum;
		return Result::Continue;
	}
	else if (next == ')')
	{
		ParseOut.push_back(NumberBuff);
		NumberBuff = "";
		Func = &ParseMath::CloseBrackets;
		return Result::Continue;
	}
	else if (next >= '0' && next <= '9')
	{
		Func = &ParseMath::NumberInt;
		return Result::Continue;
	}
	else if (next == '.')
	{
		Func = &ParseMath::Decimal;
		return Result::Continue;
	}
	else if (next == '+' || next == '-' || next == '*' || next == '/')
	{
		ParseOut.push_back(NumberBuff);
		NumberBuff = "";
		Func = &ParseMath::Operation;
		return Result::Continue;
	}

	return Result::Error;
}

Result ParseMath::NumberDec(char current, char next)
{
	NumberBuff += current;

	if (EndOfString)
	{
		ParseOut.push_back(NumberBuff);
		NumberBuff = "";
		return Result::End;
	}
	else if (next >= '0' && next <= '9')
	{
		Func = &ParseMath::NumberInt;
		return Result::Continue;
	}
	else if (next == ' ')
	{
		ParseOut.push_back(NumberBuff);
		NumberBuff = "";
		Func = &ParseMath::WhitespaceAftNum;
		return Result::Continue;
	}
	else if (next == '+' || next == '-' || next == '*' || next == '/')
	{
		Func = &ParseMath::Operation;
		return Result::Continue;
	}

	return Result::Error;
}

Result ParseMath::Decimal(char current, char next)
{
	NumberBuff += current;

	if (EndOfString)
	{
		ParseOut.push_back(NumberBuff);
		NumberBuff = "";
		return Result::Error;
	}
	else if (next >= '0' && next <= '9')
	{
		Func = &ParseMath::NumberDec;
		return Result::Continue;
	}
	else if (next == '+' || next == '-' || next == '*' || next == '/')
	{
		Func = &ParseMath::Operation;
		return Result::Continue;
	}

	return Result::Error;
}

Result ParseMath::Operation(char current, char next)
{
	ParseOut.push_back(str(current));

	if (EndOfString)
	{
		return Result::Error;
	}
	else if (next == ' ')
	{
		Func = &ParseMath::WhitespaceAftOpe;
		return Result::Continue;
	}
	else if (next == '(')
	{
		Func = &ParseMath::OpenBrackets;
		return Result::Continue;
	}
	else if (next >= '0' && next <= '9')
	{
		Func = &ParseMath::NumberInt;
		return Result::Continue;
	}

	return Result::Error;
}
