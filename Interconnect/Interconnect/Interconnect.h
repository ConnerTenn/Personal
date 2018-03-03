
#ifndef INTERCONNECT_H
#define INTERCONNECT_H
//#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "Parser.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

namespace INTC
{
	struct Node;

	//bool IsOperator(char character, int index);

	/*
	namespace EQN
	{
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

		class Equation
		{
		public:
			std::vector<EquationNode *> Nodes;
			std::vector<VAL *> Values;
			EquationNode *RootNode;

			~Equation();
			void DeleteNodes();
			
			bool Evaluate(std::vector<std::string> stringList);

			bool GenFromReversePolish(std::vector<std::string> reversePolish);
		};
	}
	*/

	class Network;

	namespace EQN
	{
		struct EquationNode
		{
			//EquationNodeType Type;

			virtual std::vector<Node *> Evaluate(Network *network);
			//virtual bool AddNode(EquationNode *node);
			//virtual bool FullNodes();
		};

		struct ROOT : EquationNode
		{
			EquationNode *Node1 = 0;

			std::vector<Node *> Evaluate(Network *network);
			//bool AddNode(EquationNode *node);
			//bool FullNodes();
		};

		struct ADD : EquationNode
		{
			EquationNode *Parent = 0;
			EquationNode *Child = 0;

			std::vector<Node *> Evaluate(Network *network);
			//bool AddNode(EquationNode *node);
			//bool FullNodes();
		};

		struct SUB : EquationNode
		{
			EquationNode *Parent = 0;

			std::vector<Node *> Evaluate(Network *network);
			//bool AddNode(EquationNode *node);
			//bool FullNodes();
		};

		struct ALL : EquationNode
		{
			EquationNode *Node1 = 0;

			std::vector<Node *> Evaluate(Network *network);
			//bool AddNode(EquationNode *node);
			//bool FullNodes();
		};

		struct ANY : EquationNode
		{
			EquationNode *Node1 = 0;

			std::vector<Node *> Evaluate(Network *network);
			//bool AddNode(EquationNode *node);
			//bool FullNodes();
		};

		class Equation
		{
		public:
			std::vector<EquationNode *> Nodes;
			//std::vector<VAL *> Values;
			EquationNode *RootNode;

			~Equation();
			void DeleteNodes();

			std::vector<Node *> Evaluate(Network *network);

			//bool GenFromReversePolish(std::vector<std::string> reversePolish);
		};
	}

	//extern std::vector<Node> Network;

	struct Node
	{
		std::string Name;
		std::vector<Node *> Nodes;

		Node() {}
		Node(std::string name) : Name(name) {}

		std::vector<std::string> GetSubNodeNames();
	};

	class Network
	{
	public:
		std::vector<Node *> NodeNetwork;

		~Network();

		void Add(std::string name, std::string sub = "");
		//std::vector<Node *> Find(EQN::Equation &equation);
		//std::vector<Node *> Find(std::vector<std::string> reversePolish);

		
	};

	

	//bool Evaluate();
}


#endif // !INTERCONNECT_H

