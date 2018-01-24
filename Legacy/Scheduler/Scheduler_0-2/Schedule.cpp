
#include "Schedule.h"


Schedule::Schedule()
{
}

Schedule::~Schedule()
{
}

void Schedule::Arrange()
{
	/*
	for (int i = 0; i < ElementList.size(); i++)
	{
		Element *element = ElementList[i];
		for (int y = element->PosBounds[0].Y; y <= element->PosBounds[1].Y; y++)
		{
			for (int x = element->PosBounds[0].X; x <= element->PosBounds[1].X; x++)
			{
				if (element->Count && element->PlaceValid(this))
				{
					ScheduleList.push_back(new ElementBase(element, { x, y }, element->PlaceValue({ x, y }, this)));
					element->Count--;
				}
			}
		}
	}
	*/

	//*
	int elementIndex = 0;
	Element *element = 0;
	int x = 0, y = 0;

	bool resetPos = true;

	while (elementIndex < ElementList.size())
	{
		if (resetPos)
		{
			element = ElementList[elementIndex];
			x = element->PosBounds[0].X; y = element->PosBounds[0].Y;
			resetPos = false;
		}

		//if there are still more duplicate elements to place
		if (element->Count)
		{
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
				if (x > element->PosBounds[1].X)
				{
					x = element->PosBounds[0].X;
					y++;
				}
				if (y > element->PosBounds[1].Y)
				{
					++elementIndex; resetPos = true;
				}
			}
		}
		else
		{
			++elementIndex;
		}
	}
	//*/
}


std::vector<ElementBase *> Schedule::Overlap(ElementBase *element)
{
	return {};
	std::vector<ElementBase *> overlapList;
	for (int i = 0; i < ElementList.size(); i++)
	{
		if (element->Overlap(ElementList[i]))
		{
			overlapList.push_back(ElementList[i]);
		}
	}
	return overlapList;
}