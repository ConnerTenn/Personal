
#include "Interconnect.h"

using namespace INTC;


std::vector<std::string> Node::GetSubNodeNames()
{
	std::vector<std::string> list;
	for (int i = 0; i < Nodes.size(); i++)
	{
		list.push_back(Nodes[i]->Name);
	}
	return list;
}

//std::vector<Node> Network = {};

/*
//#######################
//#  Equation Elements  #
//#######################

bool EQN::EquationNode::Evaluate()
{
	return false;
}

bool EQN::EquationNode::AddNode(EquationNode *node)
{
	return false;
}

bool EQN::EquationNode::FullNodes()
{
	return true;
}


bool EQN::ROOT::Evaluate()
{
	return Node1->Evaluate();
}

bool EQN::ROOT::AddNode(EquationNode *node)
{
	if (!Node1) { Node1 = node; return true; }
	return false;
}

bool EQN::ROOT::FullNodes()
{
	return !!Node1;
}


bool EQN::NOT::Evaluate()
{
	return !Node1->Evaluate();
};

bool EQN::NOT::AddNode(EquationNode *node)
{
	if (!Node1) { Node1 = node; return true; }
	return false;
}

bool EQN::NOT::FullNodes()
{
	return !!Node1;
}


bool EQN::AND::Evaluate()
{
	return Node1->Evaluate() && Node2->Evaluate();
}

bool EQN::AND::AddNode(EquationNode *node)
{
	if (!Node1) { Node1 = node; return true; }
	if (!Node2) { Node2 = node; return true; }
	return false;
}

bool EQN::AND::FullNodes()
{
	return Node1 && Node2;
}


bool EQN::OR::Evaluate()
{
	return Node1->Evaluate() || Node2->Evaluate();
};

bool EQN::OR::AddNode(EquationNode *node)
{
	if (!Node1) { Node1 = node; return true; }
	if (!Node2) { Node2 = node; return true; }
	return false;
}

bool EQN::OR::FullNodes()
{
	return Node1 && Node2;
}


bool EQN::XOR::Evaluate()
{
	return Node1->Evaluate() != Node2->Evaluate();
};

bool EQN::XOR::AddNode(EquationNode *node)
{
	if (!Node1) { Node1 = node; return true; }
	if (!Node2) { Node2 = node; return true; }
	return false;
}

bool EQN::XOR::FullNodes()
{
	return Node1 && Node2;
}


bool EQN::VAL::Evaluate()
{
	return Status;
}

bool EQN::VAL::AddNode(EquationNode *node)
{
	return false;
}

bool EQN::VAL::FullNodes()
{
	return true;
}

//##############
//#  Equation  #
//##############

EQN::Equation::~Equation()
{
	DeleteNodes();
}

void EQN::Equation::DeleteNodes()
{
	for (int i = 0; i < Nodes.size(); i++)
	{
		delete Nodes[i]; Nodes[i] = 0;
	}
	Nodes = {};
	Values = {};
	RootNode = 0;
}


bool EQN::Equation::Evaluate(std::vector<std::string> stringList)
{
	//Set each value element to true if the value element name matches a name in stringList
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

bool EQN::Equation::GenFromReversePolish(std::vector<std::string> reversePolish)
{
	DeleteNodes();

	std::vector<EquationNode *> stack;
	int rec = 0;

	{
		//Init with root node to ensure similar entry point
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
		else //If not a known operator, add VAL
		{
			node = new VAL();
			((VAL *)node)->Name = reversePolish[i];
			Values.push_back((VAL *)node);
		}

		Nodes.push_back(node);

		if (rec < 0) { return false; } //Extra nodes were added than expected
		stack.push_back(node); rec++; //add node to stack (rec is length - 1. Initially is 0 when root node exists)
		stack[rec - 1]->AddNode(node); //adds current node to previous
		while (rec >= 0 && stack[rec]->FullNodes()) { stack.pop_back(); rec--; } //Remove items from stack if their nodes are full
	}

	if (rec != -1) { return false; }
	return true;
}*/


//#########################
//#  Equation 2 Elements  #
//#########################

std::vector<Node *> EQN::EquationNode::Evaluate(Network *network)
{
	return {};
}


std::vector<Node *> EQN::ROOT::Evaluate(Network *network)
{
	return Node1->Evaluate(network);
}

std::vector<Node *> EQN::ADD::Evaluate(Network *network)
{
	/*std::vector<Node *> parentNodes = Parent->Evaluate(network);
	std::vector<Node *> childNodes = Child->Evaluate(network);

	//go through each parent node
	for (int i = 0; i < parentNodes.size(); i++)
	{
		//go through each child node
		for (int j = 0; j < childNodes.size(); j++)
		{
			//add each child node to each parent node
			network->Add(parentNodes[i]->Name, childNodes[j]->Name);
		}
	}

	return childNodes;*/
	return {};
}

std::vector<Node *> EQN::SUB::Evaluate(Network *network)
{
	/*std::vector<Node *> subNodes = Parent->Evaluate(network);

	//go through each parent node
	for (int i = 0; i < parentNodes.size(); i++)
	{
		//go through each child node
		for (int j = 0; j < childNodes.size(); j++)
		{
			//add each child node to each parent node
			network->Add(parentNodes[i]->Name, childNodes[j]->Name);
		}
	}

	return childNodes;*/
	return {};
}

//################
//#  Equation 2  #
//################

EQN::Equation::~Equation()
{
	DeleteNodes();
}

void EQN::Equation::DeleteNodes()
{
	for (int i = 0; i < Nodes.size(); i++)
	{
		delete Nodes[i]; Nodes[i] = 0;
	}
	Nodes = {};
	//Values = {};
	RootNode = 0;
}


std::vector<Node *> EQN::Equation::Evaluate(Network *network)
{
	return RootNode->Evaluate(network);
}


//#############
//#  Network  #
//#############

Network::~Network()
{
	for (int i = 0; i < NodeNetwork.size(); i++)
	{
		delete NodeNetwork[i]; NodeNetwork[i] = 0;
	}
}

void Network::Add(std::string name, std::string sub)
{
	Node *foundName = 0, *foundSub = 0;
	//search for if elements are already in the network
	for (int i = 0; i < NodeNetwork.size(); i++)
	{
		if (NodeNetwork[i]->Name == name) { foundName = NodeNetwork[i]; }
		if (NodeNetwork[i]->Name == sub) { foundSub = NodeNetwork[i]; }
	}
	//Add elements to to the network if they didnt already exist (allocates new memory)
	if (!foundName) { NodeNetwork.push_back(new Node(name)); foundName = NodeNetwork.back(); }
	if (!foundSub && sub.length()) { NodeNetwork.push_back(new Node(sub)); foundSub = NodeNetwork.back(); }
	//add sub element to parent
	if (foundSub) { foundName->Nodes.push_back(foundSub); }
}

/*
std::vector<Node *> Network::Find(EQN::Equation &equation)
{
	std::vector<Node *> results;

	//check every (root) node
	for (int i = 0; i < (int)NodeNetwork.size(); i++)
	{
		//finds which nodes have sub nodes that match the equation conditions
		if (equation.Evaluate(NodeNetwork[i]->GetSubNodeNames()))
		{
			results.push_back(NodeNetwork[i]);
		}
	}

	return results;
}

//Wrapper for Previous Find function. Allows parameter to be reversePolish
std::vector<Node *> Network::Find(std::vector<std::string> reversePolish)
{
	EQN::Equation equation;
	if (!equation.GenFromReversePolish(reversePolish))
	{
		std::cout << "ERROR parsing reversePolish\n";
		return {};
	}

	return Find(equation);
	//Equation gets destroyed and all memory released
}*/
