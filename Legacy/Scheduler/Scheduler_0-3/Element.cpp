
#include "Element.h"


ElementBase::ElementBase()
{
}

ElementBase::ElementBase(Element *element, Pos pos, std::string value)
{
	Rectangle = element->Rectangle;
	Value = value;
}

ElementBase::ElementBase(ElementBase * element)
{
	Label = element->Label;
	Rectangle = element->Rectangle;
	Value = element->Value;
}

ElementBase *ElementBase::Copy()
{
	return new ElementBase(this);
}

bool ElementBase::Overlap(ElementBase *element)
{
	/*if (Rectangle.Right() <= element->Rectangle.Left() ||
		Rectangle.Left() >= element->Rectangle.Right() ||
		Rectangle.Top() >= element->Rectangle.Bottom() ||
		Rectangle.Bottom() <= element->Rectangle.Top()
		)
	{
		return false;
	}
	return true;*/

	return Rectangle.Overlap(element->Rectangle);
}

std::vector<ElementBase *> ElementBase::Overlap(std::vector<ElementBase *> elementList)
{
	std::vector<ElementBase *> overlapList;

	for (int i = 0; i < elementList.size(); i++)
	{
		if (Overlap(overlapList[i]))
		{
			overlapList.push_back(elementList[i]);
		}
	}
	return overlapList;
}



Element::Element()
{

}

Element::Element(Element *element) : 
	ElementBase(element)
{
	PosBounds = element->PosBounds;
	Count = element->Count;
}

ElementBase *Element::Copy()
{
	return new Element(this);
}

int Element::PlaceValid(Schedule *schedule)
{
	return true;
	//	return schedule->Overlap().size() == 0;
}

std::string Element::PlaceValue(Pos pos, Schedule *schedule)
{
	return "-";
}

