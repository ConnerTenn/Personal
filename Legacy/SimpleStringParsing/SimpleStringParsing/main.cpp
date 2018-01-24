
#include <fstream>
#include <string>
#include <iostream>
#include <vector>


void main()
{
	std::cout << "Begin\n";

	std::ifstream file;
	file.open("DATA.txt");
	std::string line;
	
	std::vector<std::string> input;

	std::string delimiter = " ";

	int index = 0;
	while (std::getline(file, line))
	{
		if (line.length() > 0)
		{
			input.push_back(line.substr(index, line.find(delimiter) + index));
		}
	}

	for (int i = 0; i < input.size(); i++)
	{
		//std::cout << "\"" << input[i] << "\"" << "\n";
	}

	std::string out = "Press Enter To Continue:"; std::cout << out;
	std::getline(std::cin, out);

}
