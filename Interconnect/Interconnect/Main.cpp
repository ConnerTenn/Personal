
#include "Parser.h"
#include "Interconnect.h"

void main()
{
	//PARSE::InputParser parser;
	//parser.Parse("Hello");
	INTC::Network.push_back(INTC::Node("A"));//0
	INTC::Network.push_back(INTC::Node("B"));
	INTC::Network.push_back(INTC::Node("C"));//2
	INTC::Network.push_back(INTC::Node("D"));
	INTC::Network.push_back(INTC::Node("E"));//4
	INTC::Network.push_back(INTC::Node("F"));
	INTC::Network.push_back(INTC::Node("GE"));//6
	INTC::Network[0].Nodes.push_back(&INTC::Network[1]);
	INTC::Network[0].Nodes.push_back(&INTC::Network[2]);
	INTC::Network[0].Nodes.push_back(&INTC::Network[3]);
	INTC::Network[1].Nodes.push_back(&INTC::Network[0]);
	INTC::Network[1].Nodes.push_back(&INTC::Network[4]);
	INTC::Network[4].Nodes.push_back(&INTC::Network[0]);
	INTC::Network[4].Nodes.push_back(&INTC::Network[6]);
	INTC::Network[5].Nodes.push_back(&INTC::Network[1]);
	INTC::Network[5].Nodes.push_back(&INTC::Network[3]);

	for (int i = 0; i < (int)INTC::Network.size(); i++)
	{
		std::cout << INTC::Network[i].Name << "\n";
		for (int j = 0; j < (int)INTC::Network[i].Nodes.size(); j++)
		{
			std::cout << "  " << INTC::Network[i].Nodes[j]->Name << "\n";
		}
	}

	std::cout << "-------------------------\n";

	INTC::EQN::Equation equation;

	equation.GenFromReversePolish({ "AND", "VAL", "A", "OR", "VAL", "G", "VAL", "E" });

	std::cout << "equation: " << equation.Evaluate({ "E", "A" }) << "\n";

	std::string out;
	std::getline(std::cin, out);
}


