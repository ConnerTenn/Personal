
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
	/*namespace EQN
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
	}*/
	namespace ACT
	{
		struct Action
		{
			virtual void Evaluate();
		};
		
		struct DirSub
		{
			void Evaluate();
		};
		
		struct Add
		{
			
		};
		
		struct Actions
		{
			std::vector<Actions> ActionList;
		};
	}
}


#endif // !INTERCONNECT_H

