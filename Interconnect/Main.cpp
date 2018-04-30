
#include "Parser.h"
#include "Interconnect.h"

int main()
{
	

	bool run = true;
	while (run)
	{
		std::string line;

		std::cout << ">>";
		std::getline(std::cin, line);

		std::string command = line.substr(0, line.find(' '));
		line = line.substr(MIN(line.size(), command.size() + 1), line.size() - command.size() - 1);

		//std::cout << command << "\n#" << line << "#\n";

		if (command == "\end" || command == "\exit")
		{
			run = false;
		}
		
		
	}

	return 0;
}
