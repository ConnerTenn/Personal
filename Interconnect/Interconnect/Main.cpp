
#include "Parser.h"
#include "Interconnect.h"

void main()
{
	INTC::Network network;

	//PARSE::InputParser parser;
	//parser.Parse("Hello");
	/*network.NodeNetwork.push_back(INTC::Node("A"));//0
	network.NodeNetwork.push_back(INTC::Node("B"));
	network.NodeNetwork.push_back(INTC::Node("C"));//2
	network.NodeNetwork.push_back(INTC::Node("D"));
	network.NodeNetwork.push_back(INTC::Node("E"));//4
	network.NodeNetwork.push_back(INTC::Node("F"));
	network.NodeNetwork.push_back(INTC::Node("GE"));//6
	network.NodeNetwork[0].Nodes.push_back(&network.NodeNetwork[1]);
	network.NodeNetwork[0].Nodes.push_back(&network.NodeNetwork[2]);
	network.NodeNetwork[0].Nodes.push_back(&network.NodeNetwork[3]);
	network.NodeNetwork[1].Nodes.push_back(&network.NodeNetwork[0]);
	network.NodeNetwork[1].Nodes.push_back(&network.NodeNetwork[4]);
	network.NodeNetwork[4].Nodes.push_back(&network.NodeNetwork[0]);
	network.NodeNetwork[4].Nodes.push_back(&network.NodeNetwork[6]);
	network.NodeNetwork[5].Nodes.push_back(&network.NodeNetwork[1]);
	network.NodeNetwork[5].Nodes.push_back(&network.NodeNetwork[3]);

	for (int i = 0; i < (int)network.NodeNetwork.size(); i++)
	{
		std::cout << network.NodeNetwork[i].Name << "\n";
		for (int j = 0; j < (int)network.NodeNetwork[i].Nodes.size(); j++)
		{
			std::cout << "  " << network.NodeNetwork[i].Nodes[j]->Name << "\n";
		}
	}

	std::cout << "-------------------------\n";*/

	/*INTC::EQN::Equation equation;

	equation.GenFromReversePolish({ "AND", "VAL", "A", "OR", "VAL", "G", "VAL", "E" });

	std::cout << "equation: " << equation.Evaluate({ "E", "A" }) << "\n";*/

	//INTC::Network.push_back(INTC::Node("A"));
	
	bool run = true;
	while (run)
	{
		std::string line;

		std::cout << ">>";
		std::getline(std::cin, line);

		std::string command = line.substr(0, line.find(' '));
		line = line.substr(MIN(line.size(), command.size() + 1), line.size() - command.size() - 1);

		//std::cout << command << "\n#" << line << "#\n";

		if (command == "end" || command == "exit")
		{
			run = false;
		}
		else if (command == "add")
		{
			std::vector<std::string> words;
			bool space = true; int i = 0; while (i < line.size()) { if (line[i] == ' ') { space = true; } else { if (space) { words.push_back(""); space = false; } words.back() += line[i]; } i++; }

			network.Add(words[0], (words.size() > 1 ? words[1] : ""));
		}
		else if (command == "find")
		{
			std::vector<std::string> reversePolish;
			bool space = true; int i = 0; while (i < line.size()) { if (line[i] == ' ') { space = true; } else { if (space) { reversePolish.push_back(""); space = false; } reversePolish.back() += line[i]; } i++; }


			std::vector<INTC::Node *> nodes = network.Find(reversePolish);

			for (int i = 0; i < (int)nodes.size(); i++)
			{
				std::cout << nodes[i]->Name << "\n";
			}
		}
		else if (command == "list")
		{
			for (int i = 0; i < (int)network.NodeNetwork.size(); i++)
			{
				std::cout << network.NodeNetwork[i]->Name << "\n";
				for (int j = 0; j < (int)network.NodeNetwork[i]->Nodes.size(); j++)
				{
					std::cout << "  " << network.NodeNetwork[i]->Nodes[j]->Name << "\n";
				}
			}
		}
	}

}


