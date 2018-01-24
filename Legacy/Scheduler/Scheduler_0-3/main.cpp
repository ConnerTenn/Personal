
#include <iostream>
#include "Element.h"
#include "Schedule.h"
#include "Display.h"

class TimeElement : public Element
{
private:
	int Val;
public:
	TimeElement(int val, Rect posBounds, std::string label, int count) : 
		Element(), Val(val)
	{
		Label = label;
		Rectangle = Rect( 1, 1 );//width & height
		//Width = 1;
		//Height = 1;
		PosBounds = posBounds;//{ { 0, 0 }, { 5, 9 } };
		Count = count;
	}

	TimeElement(TimeElement *element) :
		Element(element)
	{
		Val = element->Val;
	}

	ElementBase *Copy()
	{
		return new TimeElement(this);
	}

	int PlaceValid(Schedule *schedule)
	{
		int val = 0;
		val = schedule->Overlap((Element *)this).size() == 0;
		return val;
	}

	std::string PlaceValue(Pos pos, Schedule *schedule)
	{
		//int val = Value;
		//val = Value ? pos.X + pos.Y * (PosBounds.Right() + 1) : pos.Y + pos.X * (PosBounds.Bottom() + 1);
		//static int val = 0; 
		//return std::to_string(val++);
		//return std::to_string(val);
		return Label;
	}
};

class QueenElement : public Element
{
private:
	
public:
	QueenElement()
	{
		Label = "Queen";
	}

	QueenElement(QueenElement *element) :
		Element(element)
	{

	}

	ElementBase *Copy()
	{
		return new QueenElement(this);
	}

	int PlaceValid(Schedule *schedule)
	{
		int val = 0;
		//val = schedule->Overlap((Element *)this).size() == 0;

		std::vector<ElementBase *> queenElementList = schedule->FindWithLabel("Queen");
		

		return val;
	}

	std::string PlaceValue(Pos pos, Schedule *schedule)
	{
		//int val = Value;
		//val = Value ? pos.X + pos.Y * (PosBounds.Right() + 1) : pos.Y + pos.X * (PosBounds.Bottom() + 1);
		//static int val = 0; 
		//return std::to_string(val++);
		//return std::to_string(val);
		return "#";
	}
};

void main()
{
	Schedule schedule;

	std::vector<Element *> elementList =
	{
		new TimeElement(0, { { 0, 0 }, { 5, 9 } }, "A", 3),
		new TimeElement(1, { { 3, 3 }, { 10, 15 } }, "B", 15)
	};
	schedule.ElementList = elementList;

	schedule.Arrange3();


	schedule.Arrange();


	{/*Display*/}
	{
		Display display(20*3, 20*2);
		for (int i = 0; i < schedule.ScheduleList.size(); ++i)
		{
			ElementBase *element = schedule.ScheduleList[i];
			//display.Place(element->Value, element->Position.X * 3, element->Position.Y * 2);
			display.Place(element->Value, element->Rectangle.Pos1.X * 3, element->Rectangle.Pos1.Y * 2);
		}
		display.Print();
	}

	{/*Cleanup*/}
	{//move to deconstructor
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