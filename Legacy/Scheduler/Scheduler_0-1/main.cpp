
#include <iostream>
#include "Schedule.h"
#include "Display.h"

void PlaceTime(int x, int y, std::string &string)
{
	if (x == 0)
	{
		string = std::to_string(x + y);
	}
	else
	{
		string = "-";
	}
}

void PlaceTitle(int x, int y, std::string &string)
{
	if (y == 0)
	{
		string = "T";
	}
}

void main()
{
	std::vector<void(*)(int x, int y, std::string &string)> functionList = 
	{
		PlaceTime,
		PlaceTitle
	};

	ScheduleAttributes attributes; memset(&attributes, 0, sizeof(attributes));
	attributes.Width = 10;
	attributes.Height = 10;
	attributes.AssignFunctionList = functionList;

	Schedule schedule(attributes);
	schedule.Init();
	schedule.Arrange();

	DisplayGird(schedule.GetScheduleArray());

	std::cout << "\nPress Enter To Continue:";
	std::string out;
	std::getline(std::cin, out);
}