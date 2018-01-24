
#include "Element.h"


ElementBase::ElementBase()
{
}

ElementBase::ElementBase(Element *element, Pos pos, std::string value)
{
	Width = element->Width;
	Height = element->Height;
	Position = pos;
	Value = value;
}

bool ElementBase::Overlap(ElementBase *element)
{
	return false;//fix
}



Element::Element()
{
	PosBounds[0] = { 0, 0 };
	PosBounds[1] = { 0, 0 };
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

