
#include "Interconnect.h"


//char INTC::OPE::Not[2] = "!";
/*char And[2] = "&";
char Or[2] = "|";
char Xor[2] = "^";
std::string Dir = "/";
std::string ForwardDir = ">";
std::string Reverse = "<";
char EscapeChar[2] = "\\";
char OpenBracket[2] = "(";
char CloseBracket[2] = ")";
std::string OpenList = "{"; Not necessary 
std::string CloseList = "}";
std::string OpenQuote = "\"";
std::string CloseQuote = "\"";
std::string Delimeter = ",";*/

/*bool INTC::IsOperator(char character, int index)
{
	if (character == OPE::Not[index]) { return true; }
	else if (character == OPE::And[index]) { return true; }
	else if (character == OPE::Or[index]) { return true; }
	else if (character == OPE::Xor[index]) { return true; }
	else if (character == OPE::EscapeChar[index]) { return true; }
	else if (character == OPE::OpenBracket[index]) { return true; }
	else if (character == OPE::CloseBracket[index]) { return true; }
	//return false;


}*/

std::vector<std::string> INTC::Node::GetSubNodeNames()
{
	std::vector<std::string> list;
	for (int i = 0; i < Nodes.size(); i++)
	{
		list.push_back(Nodes[i]->Name);
	}
	return list;
}

//std::vector<INTC::Node> INTC::Network = {};

/*
std::vector<INTC::Node *> INTC::FindNodes(std::string search)
{
	std::vector<std::string> names; 
	std::vector<Node *> out;
	
	{
		int index = -1; int wordState = 0;
		for (int i = 0; i < (int)search.size(); i++)
		{
			if (isalpha(search[i]) || search[i] == '_')
			{
				if (wordState == 0)
				{
					wordState = 1; index++; names.push_back("");
				}
				names[index] += search[i];
			}
			else if (search[i] == ' ')
			{
				wordState = 0;
			}
			else
			{
				return {};
			}
		}
	}

	for (int i = 0; i < (int)Network.size(); i++)
	{
		bool hasNames = true;

		for (int s = 0; s < (int)names.size() && hasNames; s++)
		{
			bool has = false;
			for (int n = 0; n <(int)Network[i].Nodes.size() && !has; n++)
			{
				if (Network[i].Nodes[n]->Name == names[s])
				{
					has = true;
				}
			}
			if (!has) { hasNames = false; }//if none of the nodes has the name, exit for this node
		}

		if (hasNames) { out.push_back(&Network[i]); }
	}

	return out;
}
*/


bool INTC::EQN::EquationNode::Evaluate()
{
	return false;
}

bool INTC::EQN::EquationNode::AddNode(EquationNode *node)
{
	return false;
}

bool INTC::EQN::EquationNode::FullNodes()
{
	return true;
}


bool INTC::EQN::ROOT::Evaluate()
{
	return Node1->Evaluate();
}

bool INTC::EQN::ROOT::AddNode(EquationNode *node)
{
	if (!Node1) { Node1 = node; return true; }
	return false;
}

bool INTC::EQN::ROOT::FullNodes()
{
	return !!Node1;
}


bool INTC::EQN::NOT::Evaluate()
{
	return !Node1->Evaluate();
};

bool INTC::EQN::NOT::AddNode(EquationNode *node)
{
	if (!Node1) { Node1 = node; return true; }
	return false;
}

bool INTC::EQN::NOT::FullNodes()
{
	return !!Node1;
}


bool INTC::EQN::AND::Evaluate()
{
	return Node1->Evaluate() && Node2->Evaluate();
}

bool INTC::EQN::AND::AddNode(EquationNode *node)
{
	if (!Node1) { Node1 = node; return true; }
	if (!Node2) { Node2 = node; return true; }
	return false;
}

bool INTC::EQN::AND::FullNodes()
{
	return Node1 && Node2;
}



bool INTC::EQN::OR::Evaluate()
{
	return Node1->Evaluate() || Node2->Evaluate();
};

bool INTC::EQN::OR::AddNode(EquationNode *node)
{
	if (!Node1) { Node1 = node; return true; }
	if (!Node2) { Node2 = node; return true; }
	return false;
}

bool INTC::EQN::OR::FullNodes()
{
	return Node1 && Node2;
}


bool INTC::EQN::XOR::Evaluate()
{
	return Node1->Evaluate() != Node2->Evaluate();
};

bool INTC::EQN::XOR::AddNode(EquationNode *node)
{
	if (!Node1) { Node1 = node; return true; }
	if (!Node2) { Node2 = node; return true; }
	return false;
}

bool INTC::EQN::XOR::FullNodes()
{
	return Node1 && Node2;
}


bool INTC::EQN::VAL::Evaluate()
{
	return Status;
}

bool INTC::EQN::VAL::AddNode(EquationNode *node)
{
	return false;
}

bool INTC::EQN::VAL::FullNodes()
{
	return true;
}


INTC::EQN::Equation::~Equation()
{
	for (int i = 0; i < Nodes.size(); i++)
	{
		delete Nodes[i]; Nodes[i] = 0;
	}
}

bool INTC::EQN::Equation::Evaluate(std::vector<std::string> stringList)
{
	for (int i = 0; i < Values.size(); i++)
	{
		Values[i]->Status = false;

		for (int j = 0; j < stringList.size(); j++)
		{
			Values[i]->Status = Values[i]->Status || stringList[j] == Values[i]->Name;
		}
	}

	return RootNode->Evaluate();
}

bool INTC::EQN::Equation::GenFromReversePolish(std::vector<std::string> reversePolish)
{
	std::vector<EquationNode *> stack;
	int rec = 0;

	{
		ROOT *root = new ROOT();
		stack.push_back(root);
		Nodes.push_back(root);
		RootNode = root;
	}

	for (int i = 0; i < (int)reversePolish.size(); i++)
	{
		std::string expr = reversePolish[i];
		EquationNode *node = 0;

		if (expr == "NOT")
		{
			node = new NOT();
		}
		else if (expr == "AND")
		{
			node = new AND();
		}
		else if (expr == "OR")
		{
			node = new OR();
		}
		else if (expr == "XOR")
		{
			node = new XOR();
		}
		else //VAL
		{
			node = new VAL();
			((VAL *)node)->Name = reversePolish[i];
			Values.push_back((VAL *)node);
		}

		Nodes.push_back(node);

		if (rec < 0) { return false; }
		stack.push_back(node); rec++;
		stack[rec - 1]->AddNode(node);
		while (rec >= 0 && stack[rec]->FullNodes()) { stack.pop_back(); rec--; }
	}

	if (rec != -1) { return false; }
	return true;
}


INTC::Network::~Network()
{
	for (int i = 0; i < NodeNetwork.size(); i++)
	{
		delete NodeNetwork[i]; NodeNetwork[i] = 0;
	}
}

void INTC::Network::Add(std::string name, std::string sub)
{
	Node *foundName = 0, *foundSub = 0;
	for (int i = 0; i < NodeNetwork.size(); i++)
	{
		if (NodeNetwork[i]->Name == name) { foundName = NodeNetwork[i]; }
		if (NodeNetwork[i]->Name == sub) { foundSub = NodeNetwork[i]; }
	}
	if (!foundName) { NodeNetwork.push_back(new INTC::Node(name)); foundName = NodeNetwork.back(); }
	if (foundName && !foundSub && sub.length()) { NodeNetwork.push_back(new INTC::Node(sub)); foundSub = NodeNetwork.back(); }
	if (foundName && foundSub) { foundName->Nodes.push_back(foundSub); }
}

std::vector<INTC::Node *> INTC::Network::Find(INTC::EQN::Equation &equation)
{
	std::vector<Node *> results; 

	for (int i = 0; i < (int)NodeNetwork.size(); i++)
	{
		if (equation.Evaluate(NodeNetwork[i]->GetSubNodeNames()))
		{
			results.push_back(NodeNetwork[i]);
		}
	}

	return results;
}

std::vector<INTC::Node *> INTC::Network::Find(std::vector<std::string> reversePolish)
{
	EQN::Equation equation;
	if (!equation.GenFromReversePolish(reversePolish))
	{
		std::cout << "ERROR parsing reversePolish\n";
		return {};
	}
	
	return Find(equation);
}


