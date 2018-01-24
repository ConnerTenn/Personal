
#include "Scheduler.h"
#include "Display.h"

void main()
{
	std::vector<Element> Elements =
	{
		{ 2, 1, "H", 1 },
		{ 50, 50, "N", 1 },
		{ 2, 2, "A", 1 },
		{ 1, 4, "B", 1 },
		{ 3, 2, "C", 1 },
		{ 2, 2, "D", 1 },
		{ 2, 3, "E", 1 },
		{ 5, 2, "F", 1 },
	};

	Scheduler scheduler(5, 8);
	scheduler.Arrange2(Elements);

	std::vector<std::vector<std::string>> grid;
	grid.resize(scheduler.Height);
	for (int y = 0; y < scheduler.Height; ++y)
	{
		for (int x = 0; x < scheduler.Width; ++x)
		{
			grid[y].push_back(std::to_string(scheduler.Schedule[y][x]) != "-1" ? std::to_string(scheduler.Schedule[y][x]) : "-");
		}
	}
	std::cout << "\n";
	DisplayGird(grid);
	std::cout << "\n";

	for (int y = 0; y < scheduler.Height; ++y)
	{
		for (int x = 0; x < scheduler.Width; ++x)
		{
			std::cout << (scheduler.Schedule[y][x] == -1 ? "-" : std::to_string(scheduler.Schedule[y][x])) << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\nPress Enter To Continue:"; std::string out; std::getline(std::cin, out);
}

