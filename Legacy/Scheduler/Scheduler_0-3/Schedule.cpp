
#include "Schedule.h"


Schedule::Schedule()
{
}

Schedule::~Schedule()
{
}

void Schedule::Arrange()
{
	int elementIndex = 0;
	Element *element = 0;
	int x = 0, y = 0;

	bool resetPos = true;

	while (elementIndex < ElementList.size())
	{
		if (resetPos)
		{
			element = ElementList[elementIndex];
			x = element->PosBounds.Left(); y = element->PosBounds.Top();
			resetPos = false;
		}

		//if there are still more duplicate elements to place
		if (element->Count)
		{
			element->Rectangle = Pos( x, y );//pos
			if (element->PlaceValid(this))
			{
				//check within bounds
				ScheduleList.push_back(new ElementBase(element, { x, y }, element->PlaceValue({ x, y }, this)));
				element->Count--;

				//reset pos back to start of bounds
				//x = element->PosBounds[0].X; y = element->PosBounds[0].Y;
				resetPos = true;
			}
			else
			{
				//modify pos
				x++;
				if (x > element->PosBounds.Right())
				{
					x = element->PosBounds.Left();
					y++;
				}
				if (y > element->PosBounds.Bottom())
				{
					++elementIndex; resetPos = true;
				}
			}
		}
		else
		{
			++elementIndex;
			resetPos = true;
		}
	}
}

void Schedule::Arrange2()
{
	//element = 0
	//subElement = 0
	//position = 0,0

	/*
	//loop
		//if not placed all elements
			//if not placed all sub elements
				//place subelement at pos
				//if fail place
					//modify pos
	*/

	//loop
		//state: place
			//if place valid
				//state = increment sub element
			//if place not valid
				//state = modify pos
		//state: increment sub element
			//increment sub element
			//if sub element out of range
				//state = increment element
		//state: increment element
			//increment element
			//if element out of range
				//found solution; end
		//state: modify pos
			//modify pos
			//if pos out of range
				//state = backtrack sub element
		//state: backtrack sub element
			//backtrack sub element
			//recover pos from backtrack sub element
			//if sub element out of range
				//state = backtrack element
		//state: backtrack element
			//backtrack element
			//recover sub element from backtrack element
			//recover pos from backtrack sub element
			//if element out of range
				//no soloution; end
	
	int state = 0;
	int returnState = 0;
	int elementIndex = 0;
	int subElementIndex = 0;
	Pos position = { 0, 0 };

	Element *element = 0;
	element = ElementList[elementIndex];

	bool run = true;
	while (run)
	{
		if (state == 0)//place
		{
			if (element->PlaceValid(this))
			{
				//ScheduleList.push_back(new ElementBase(element, position, element->PlaceValue({ x, y }, this)));
				//element->Count--;
			}
			else
			{

			}
		}
		else if (state == 1)//increment sub element
		{

		}
		else if (state == 2)//increment element
		{

		}
		else if (state == 3)//modify pos
		{

		}
		else if (state == 4)//backtrack sub element
		{

		}
		else if (state == 5)//backtrack element
		{

		}
	}
}

void Schedule::Arrange3()
{
	//Expand sub elements
	std::vector<ElementBase *> elementList;
	for (int i = 0; i < ElementList.size(); i++)
	{
		for (int j = 0; j < ElementList[i]->Count; j++)
		{
			elementList.push_back(ElementList[i]->Copy());
		}
	}


	for (int i = 0; i < elementList.size(); i++)
	{
		delete elementList[i];
	}
}

std::vector<ElementBase *> Schedule::Overlap(ElementBase *element)
{
	//return {};
	std::vector<ElementBase *> overlapList;

	for (int i = 0; i < ScheduleList.size(); i++)
	{
		//if (element != ElementList[i] && element->Overlap(ElementList[i]))
		if (element->Overlap(ScheduleList[i]))
		{
			overlapList.push_back(ScheduleList[i]);
		}
	}
	return overlapList;
}

std::vector<ElementBase *> Schedule::RetrieveIntersectAt(Pos pos1, int width, int height)
{
	std::vector<ElementBase *> overlapList;

	for (int i = 0; i < ScheduleList.size(); i++)
	{
		//if (element != ElementList[i] && element->Overlap(ElementList[i]))
		//if (element->Overlap(ScheduleList[i]))
		if (ScheduleList[i]->Rectangle.Overlap({pos1, width, height}))
		{
			overlapList.push_back(ScheduleList[i]);
		}
	}
	return overlapList;
}

std::vector<ElementBase *> Schedule::FindWithLabel(std::string label)
{
	std::vector<ElementBase *> returnList;

	for (int i = 0; i < ScheduleList.size(); i++)
	{
		if (ScheduleList[i]->Label == label) { returnList.push_back(ScheduleList[i]); }
	}

	return returnList;
}

