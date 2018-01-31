
#include "Parser.h"
#include "Interconnect.h"

void main()
{
	//PARSE::InputParser parser;
	//parser.Parse("Hello");
	/*INTC::Network.push_back(INTC::Node("A"));//0
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

	std::cout << "-------------------------\n";*/

	/*INTC::EQN::Equation equation;

	equation.GenFromReversePolish({ "AND", "VAL", "A", "OR", "VAL", "G", "VAL", "E" });

	std::cout << "equation: " << equation.Evaluate({ "E", "A" }) << "\n";*/
	
	//INTC::Network.push_back(INTC::Node("A"));
	INTC::EQN::Equation equation;


	bool run = true;
	while (run)
	{
		std::string line;

		std::cout << ">>";
		std::getline(std::cin, line);
		
		std::string command = line.substr(0, line.find(' '));
		line = line.substr(MIN(line.size(),command.size() + 1), line.size() - command.size()-1);

		//std::cout << command << "\n#" << line << "#\n";

		if (command == "end")
		{
			run = false;
		}
		else if (command == "add")
		{
			std::vector<std::string> words;
			words.push_back("");  int i = 0; while (i < line.size()) { if (line[i] == ' ') { words.push_back(""); } else { words.back() += line[i]; } i++; }
			
			bool exists = false;
			for (int i = 0; i < INTC::Network.size(); i++)
			{
				if (INTC::Network[i].Name == words[0])
				{
					exists = true;
				}
			}
			//INTC::Network.push_back(INTC::Node(word));
		}
		else if (command == "find")
		{
			std::vector<std::string> reversePolish;
			//{ int i = 0;  while (i < line.size()) { int find = line.find(' ', i); if (find != std::string::npos) { reversePolish.push_back(line.substr(i, find)); i = find + 1; } else { i = line.size(); } } }
			reversePolish.push_back("");  int i = 0; while (i < line.size()) { if (line[i] == ' ') { reversePolish.push_back(""); } else { reversePolish.back() += line[i]; } i++; }
			
			
			equation.GenFromReversePolish(reversePolish);

			for (int i = 0; i < INTC::Network.size(); i++)
			{
				if (equation.Evaluate(INTC::Network[i].GetSubNodeNames()))
				{
					std::cout << INTC::Network[i].Name << "\n";
				}
			}
		}
	}

	std::string out;
	std::getline(std::cin, out);
}


