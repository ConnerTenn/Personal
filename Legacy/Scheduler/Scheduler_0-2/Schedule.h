
#include <math.h>
#include <vector>
#include <string>
#include <array>

struct Pos
{
	int X;
	int Y;
};

struct Rect
{
	Pos Pos1;
	Pos Pos2;

	Rect(int x1, int y1, int x2, int y2)
	{
		Pos1 = { x1, y1 };
		Pos2 = { y1,y2 };
	}

	int Right() { return Pos1.X > Pos2.X ? Pos1.X : Pos2.X; }
	int Left() { return Pos1.X < Pos2.X ? Pos1.X : Pos2.X; }
	int Top() { return Pos1.Y < Pos2.Y ? Pos1.Y : Pos2.Y; }
	int Bottom() { return Pos1.Y > Pos2.Y ? Pos1.Y : Pos2.Y; }
	
	int Width() { return abs(Pos2.X - Pos1.X); }
	int Height() { return abs(Pos2.Y - Pos1.Y); }
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

	std::vector<ElementBase *> Overlap(ElementBase *element);
	std::vector<ElementBase *> RetrieveIntersectAt(Pos pos1, int width, int height);
	std::vector<ElementBase *> FindWithLabel(std::vector<std::string> label);
};
