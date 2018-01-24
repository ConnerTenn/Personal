
#include "Cmd.h"
#include "Commands.h"

bool Run = true;

void Exit(std::vector<std::string> args)
{
	Run = false;
}

std::vector<Command> CommandList =
{
	Command("Hello", Hello),
	Command("Test1", Test1),
	Command("Test2", Test2),
	Command("Exit", Exit)
};

void main()
{
	Cmd cmd(CommandList);

	while (Run)
	{
		cmd.Get(">");
	}

	std::cout << "\nPress Enter To Continue";
	std::string out;
	std::getline(std::cin, out);
}
