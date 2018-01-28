
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

std::vector<INTC::Node> INTC::Network = {};

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


bool  INTC::EQN::EquationNode::Evaluate()
{
	return false;
}

bool INTC::EQN::AND::Evaluate()
{
	return Node1->Evaluate() && Node2->Evaluate();
}

bool INTC::EQN::OR::Evaluate()
{
	return Node1->Evaluate() || Node2->Evaluate();
};

bool INTC::EQN::NOT::Evaluate()
{
	return !Node1->Evaluate();
};

bool INTC::EQN::Value::Evaluate()
{
	return Status;
}

bool INTC::EQN::Equation::Evaluate(std::vector<std::string> stringList)
{
	for (int i = 0; i < Values.size(); i++)
	{
		Values[i]->Status = Values[i]->Status || stringList[i] == Values[i]->Name;
	}

	return RootNode->Evaluate();
}


