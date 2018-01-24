
#pragma once

#include <vector>
#include <string>

enum Operator
{
	Add,
	Sub,
	Mul,
	Div
};

class Test
{
public:
	int &Val;
	Test(int &val) :
		Val(val)
	{

	}
};

static class InterpretMath
{
private:
	std::vector<std::vector<Operator>> OperatorBuffer;
	std::vector<std::string> ParseBuffer;

	std::string OperatorToString(Operator ope)
	{
		switch (ope)
		{
		case Add:
			return "+";
		case Sub:
			return "-";
		case Mul:
			return "*";
		case Div:
			return "/";
		}
		return "\0";
	}
public:
	void Parse(std::vector<std::string> list)
	{
		ParseBuffer.resize(list.size());
		int ParseBufferIndex = ParseBuffer.size() - 1;
		std::string current;
		double total = 0;
		int OperatorBufferIndex = 0;
		for (int i = 0; i < list.size(); i++)//go backwards
		{
			current = list[i];
			if (current == ")") { OperatorBuffer.push_back({}); }
			if (current == "(") 
			{ 
				while (OperatorBuffer[OperatorBufferIndex].size())
				{
					//Remove the last operator off the buffer and add it into the parse buffer
					ParseBuffer[ParseBufferIndex] = OperatorToString(OperatorBuffer[OperatorBufferIndex][OperatorBuffer[OperatorBufferIndex].size() - 1]);
					OperatorBuffer[OperatorBufferIndex].pop_back();
					ParseBufferIndex--;
				}
				OperatorBuffer.pop_back(); 
			}
		}
	}
	/*
	Parse Rules:

	if opeerator
		if operation is equal or lower priority
			add operator onto buffer
		else
			remove 
	if open bracket
		increment operator buffer
	if close bracket
		remove operations form buffer
		decrement operator buffer
	
	*/
};