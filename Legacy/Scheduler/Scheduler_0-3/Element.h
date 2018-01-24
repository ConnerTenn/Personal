
class ElementBase;
class Element;

#pragma once

#include "Schedule.h"
#include <iostream>
#include <vector>
/*
struct ElementAttributes
{
	int Width;
	int Height;
	//bool (*ValidPlace)(int x, int y);
	int Count
};

class Element
{
public:
	int Width;
	int Height;
	//bool (*ValidPlace)(int x, int y);
	Pos(*PlacePos)(int i);
	std::string(*PlaceValue)(int x, int y);
	int Count;

	Element(ElementAttributes attributes)
	{
		Width = attributes.Width;
		Height = attributes.Height;
		//ValidPlace = attributes.ValidPlace;
		Count = attributes.Count;
	}
};
*/

//create base that element inherits from

class ElementBase
{
	//friend std::vector<ElementBase *> Schedule::Overlap();
public:
	Rect Rectangle;
	//int Height = 0;
	//int Width = 0;
	//Pos Position;
	std::string Label = "";
//private:
	std::string Value = "";
	ElementBase();
	ElementBase(ElementBase *element);
	ElementBase(Element *element, Pos pos, std::string value);
	virtual ElementBase *Copy();

public:
	bool Overlap(ElementBase *element);
	std::vector<ElementBase *> Overlap(std::vector<ElementBase *> elementList);
};

class Element : public ElementBase
{
public:
	Rect PosBounds;// = { { 0, 0 }, { 0, 0 } };
	int Count = 0;
	//int CurrentSubElement = 0;

	Element();
	Element(Element *element);
	virtual ElementBase *Copy();
	
	virtual int PlaceValid(Schedule *schedule);
	virtual std::string PlaceValue(Pos pos, Schedule *schedule);

};




