
#ifndef INTERCONNECT_H
#define INTERCONNECT_H
//#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

namespace INTC
{
	/*
	//Use of extern instead of const so that value can be changed at runtime (by config file)
	namespace OPE
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

	//bool IsOperator(char character, int index);

	namespace EQN
	{

		/*enum EquationNodeType
		{
			Value,
			//Operator,
		};*/

		struct EquationNode
		{
			//EquationNodeType Type;

			virtual bool Evaluate();
			virtual bool AddNode(EquationNode *node);
			virtual bool FullNodes();
		};

		struct ROOT : EquationNode
		{
			EquationNode *Node1 = 0;

			bool Evaluate();
			bool AddNode(EquationNode *node);
			bool FullNodes();
		};

		struct NOT : EquationNode
		{
			EquationNode *Node1 = 0;

			bool Evaluate();
			bool AddNode(EquationNode *node);
			bool FullNodes();
		};

		struct AND : EquationNode
		{
			EquationNode *Node1 = 0;
			EquationNode *Node2 = 0;

			bool Evaluate();
			bool AddNode(EquationNode *node);
			bool FullNodes();
		};

		struct OR : EquationNode
		{
			EquationNode *Node1 = 0;
			EquationNode *Node2 = 0;

			bool Evaluate();
			bool AddNode(EquationNode *node);
			bool FullNodes();
		};

		struct XOR : EquationNode
		{
			EquationNode *Node1 = 0;
			EquationNode *Node2 = 0;

			bool Evaluate();
			bool AddNode(EquationNode *node);
			bool FullNodes();
		};

		struct VAL : EquationNode
		{
			std::string Name;
			bool Status;

			bool Evaluate();
			bool AddNode(EquationNode *node);
			bool FullNodes();
		};

		struct Equation
		{
			std::vector<EquationNode *> Nodes;
			std::vector<VAL *> Values;
			EquationNode *RootNode;

			~Equation();
			
			bool Evaluate(std::vector<std::string> stringList);

			bool GenFromReversePolish(std::vector<std::string> reversePolish);
		};
	}

	//bool Evaluate();
}


#endif // !INTERCONNECT_H

