
#ifndef INTERCONNECT_H
#define INTERCONNECT_H
//#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

namespace INTC
{
	/*namespace OPE
	{
		extern char Not[2];
		//char And[2] = "&";
		//char Or[2] = "|";
		//char Xor[2] = "^";
		//std::string Dir = "/";
		//std::string ForwardDir = ">";
		//std::string Reverse = "<";
		//char EscapeChar[2] = "\\";
		//char OpenBracket[2] = "(";
		//char CloseBracket[2] = ")";
		//std::string OpenList = "{"; Not necessary 
		//std::string CloseList = "}";
		//std::string OpenQuote = "\"";
		//std::string CloseQuote = "\"";
		//std::string Delimeter = ",";
	}*/
	/*
	namespace LOGIC
	{
		class Element
		{

		};

		class And : public Element
		{

		};

		class Or : public Element
		{

		};

		class XOr : public Element
		{

		};

		class Not : public Element
		{

		};

		class Operator
		{

		};
	}

	class Directory
	{
		//std::vector<LOGIC::Operator> Dir;


	};


	class Node
	{
		std::string name;
		//Links
		//LinkToThis
	};


	class Network
	{
		//file File
		char *VirtualFile;

		

		int Find(Directory dir, std::string node);
		int Find(std::string path, std::string node);
	};
	*/



	struct Node
	{
		std::string Name;
		std::vector<Node *> Nodes;
		
		Node() {}
		Node(std::string name) : Name(name) {}
	};
	extern std::vector<Node> Network;

	std::vector<INTC::Node *> FindNodes(std::string search);

	
	namespace OPE
	{
		const char Not[3] = { '!', 0, 0 };
		//char And[2] = "&";
		//char Or[2] = "|";
		//char Xor[2] = "^";
		//std::string Dir = "/";
		//std::string ForwardDir = ">";
		//std::string Reverse = "<";
		//char EscapeChar[2] = "\\";
		//char OpenBracket[2] = "(";
		//char CloseBracket[2] = ")";
		//std::string OpenList = "{"; Not necessary 
		//std::string CloseList = "}";
		//std::string OpenQuote = "\"";
		//std::string CloseQuote = "\"";
		//std::string Delimeter = ",";
	}

	bool IsOperator(char character, int index);

	namespace EQN
	{

		enum EquationNodeType
		{
			Operator,
			Value,
		};

		struct EquationNode
		{
			std::string Name;
			EquationNodeType Tyoe;
			//bool Operator;
			//bool Value;
		};

		/*struct Operator : EquationNode
		{

		};

		struct Value : EquationNode
		{

		};*/

		struct Equation
		{
			std::vector<EquationNode> EquationNodes;

		};
	}

	//bool Evaluate();
}


#endif // !INTERCONNECT_H

