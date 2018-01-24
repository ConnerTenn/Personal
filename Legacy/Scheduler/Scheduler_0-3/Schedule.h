
#include <math.h>
#include <vector>
#include <string>
#include <array>

struct Pos
{
	int X = 0;
	int Y = 0;
	
	Pos() {}
	Pos(int x, int y) { X = x; Y = y; }
};

struct Rect
{
	Pos Pos1;
	Pos Pos2;

	Rect() {}
	Rect(int x1, int y1, int x2, int y2)
	{
		Pos1 = { x1, y1 };
		Pos2 = { x2, y2 };
	}
	Rect(Pos pos1, Pos pos2) : Rect(pos1.X, pos1.Y, pos2.X, pos2.Y) {}
	Rect(Pos pos, int width, int height) : Rect(pos.X, pos.Y, pos.X + width, pos.Y + height) {}
	Rect(int width, int height) : Rect(0, 0, width - 1, height - 1) {}
	
	void operator=(Pos pos)//optimize
	{
		Pos2 = { pos.X + Width(), pos.Y + Height() };
		Pos1 = pos;
	}

	inline int Right() { return Pos1.X > Pos2.X ? Pos1.X : Pos2.X; }
	inline int Left() { return Pos1.X < Pos2.X ? Pos1.X : Pos2.X; }
	inline int Top() { return Pos1.Y < Pos2.Y ? Pos1.Y : Pos2.Y; }
	inline int Bottom() { return Pos1.Y > Pos2.Y ? Pos1.Y : Pos2.Y; }
	
	inline int Width() { return abs(Pos2.X - Pos1.X); }
	inline int Height() { return abs(Pos2.Y - Pos1.Y); }

	bool Overlap(Rect other)
	{
		if (Right() < other.Left() ||
			Left() > other.Right() ||
			Top() > other.Bottom() ||
			Bottom() < other.Top())
		{ return false;	}
		return true;
	}

	static bool Overlap(Rect rectA, Rect rectB)
	{
		if (rectA.Right() < rectB.Left() ||
			rectA.Left() > rectB.Right() ||
			rectA.Top() > rectB.Bottom() ||
			rectA.Bottom() < rectB.Top())
		{ return false; }
		return true;
	}
};

class Schedule;

#pragma once

#include "Element.h"



class Schedule
{
//private:
public:
	//int Width;
	//int Height;
	//std::vector<std::vector<std::string>> ScheduleArray;
	std::vector<Element *> ElementList;
	std::vector<ElementBase *> ScheduleList;
	//std::vector<void(*)(int x, int y, std::string &string)> AssignFunctionList;

public:

public:
	Schedule();
	~Schedule();

private:

public:
	void Arrange();
	void Arrange2();
	void Arrange3();

	std::vector<ElementBase *> Overlap(ElementBase *element);
	//overlap with list of elements
	std::vector<ElementBase *> RetrieveIntersectAt(Pos pos1, int width, int height);
	std::vector<ElementBase *> FindWithLabel(std::string label);
};
