
#pragma once

#include <iostream>
#include <string>
#include <vector>

class Command
{
	void(*Function)(std::vector<std::string>);
	std::string Name;
public:
	Command(std::string name, void (*function)(std::vector<std::string>))
	{
		Name = name;
		Function = function;
	}
	bool operator== (std::string &name)
	{
		return Name == name ? true : false;
	}
	void Call(std::vector<std::string> args)
	{
		Function(args);
	}
};

class Cmd
{
	std::vector<Command> CommandList;
	std::string In;
	std::string Name;
	std::vector<std::string> Args;

public:
	Cmd(std::vector<Command> &commandList)
	{
		CommandList = commandList;
	}

	void Get()
	{
		std::cout << ">";
		std::getline(std::cin, In);
		
		{/*Parse Args*/}
		{
			Name = "";
			Args.clear();
			size_t pos = 0;
			//std::transform(In.begin(), In.end(), In.begin(), ::toupper);

			bool first = true;
			while ((pos = In.find(" ")) != std::string::npos)
			{
				if (first) { Name = In.substr(0, pos); first = false; }
				else { Args.push_back(In.substr(0, pos)); }
				
				In.erase(0, pos + 1);
			}
			if (first) { Name = In.substr(0, pos); first = false; }
			else { Args.push_back(In.substr(0, In.length())); }
		}

		for (int i = 0; i < CommandList.size(); i++)
		{
			Command *command = &CommandList[i];
			if (*command == Name)
			{
				command->Call(Args);
			}

		}
	}

};