
#include <iostream>
#include "Element.h"
#include "Schedule.h"
#include "Display.h"

class TimeElement : public Element
{
public:
	TimeElement()
	{
		Width = 1;
		Height = 1;
		PosBounds[0] = { 0, 0 };
		PosBounds[1] = { 3, 9 };
		Count = 26;
	}

	int PlaceValid(Schedule *schedule)
	{
		return schedule->Overlap((Element *)this).size() == 0;
		//return true;
	}

	std::string PlaceValue(Pos pos, Schedule *schedule)
	{
		int val = pos.X + pos.Y * (PosBounds[1].X + 1);
		return std::to_string(val);
	}
};

void main()
{
	Schedule schedule;

	std::vector<Element *> elementList =
	{
		new TimeElement()
	};
	schedule.ElementList = elementList;

	schedule.Arrange();


	{/*Display*/}
	{
		Display display(20, 20);
		for (int i = 0; i < schedule.ScheduleList.size(); ++i)
		{
			ElementBase *element = schedule.ScheduleList[i];
			display.Place(element->Value, element->Position.X * 3, element->Position.Y * 2);
		}
		display.Print();
	}

	{/*Cleanup*/}
	{
		for (int i = 0; i < schedule.ElementList.size(); i++)
		{
			delete schedule.ElementList[i];
		}
		for (int i = 0; i < schedule.ScheduleList.size(); i++)
		{
			delete schedule.ScheduleList[i];
		}
	}

	{/*Exit*/}
	{
		std::cout << "\nPress Enter To Continue:";
		std::string out;
		std::getline(std::cin, out);
	}
}