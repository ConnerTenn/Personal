
#pragma once
#include <iostream>
#include <string>
#include <vector>

struct Element
{
	int Width;
	int Height;
	std::string Name;
	int Count;
	int GetArea() { return Width * Height; }
};

class Scheduler
{
public:
	int Width;
	int Height;
	std::vector<std::vector<int>> Schedule;

public:
	Scheduler(int width, int height)
	{
		Width = width; Height = height;

		Schedule.resize(Height);
		for (int y = 0; y < Height; ++y)
		{
			Schedule[y].resize(Width);
			for (int x = 0; x < Width; ++x)
			{
				Schedule[y][x] = -1;
			}
		}
	}

	int GetArea() { return Width * Height; }

	bool ValidPlace(Element element, int x, int y)
	{
		if (element.Width + x <= Width &&
			element.Height + y <= Height)
		{
			for (int offY = 0; offY < element.Height; ++offY)
			{
				for (int offX = 0; offX < element.Width; offX++)
				{
					if (!(Schedule[y + offY][x + offX] == -1)) { return false; }
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	void Allocate(Element element, int x, int y, int value)
	{
		for (int offY = 0; offY < element.Height; ++offY)
		{
			for (int offX = 0; offX < element.Width; offX++)
			{
				Schedule[y + offY][x + offX] = value;
			}
		}
	}

	void FindElement(Element element, int value, int *pos)
	{
		for (int y = 0; y < Height; ++y)
		{
			for (int x = 0; x < Width; x++)
			{
				if (Schedule[y][x] == value)
				{
					pos[0] = x; pos[1] = y; return;
				}
			}
		}
	}

	void Arrange(std::vector<Element> elements)
	{
		int x = 0, y = 0, index = 0;

		while (index < elements.size() && index >= 0)
		{
			if (ValidPlace(elements[index], x, y))
			{
				//Allocate in Schedule 
				Allocate(elements[index], x, y, index);
				index++;
				x = 0; y = 0;
			}
			else
			{
				x++;
				if (x >= Width)
				{
					++y; x = 0;
				}
				if (y >= Height)
				{
					y = 0; ++index;

					/*if (index < elements.size() && index >= 0)
					{
					//get location of index and deallocate index
					int pos[2] = { 0, 0 }; FindElement(elements[index], index, pos);//error: index is -1
					Allocate(elements[index], pos[0], pos[1], -1);
					++x;
					}*/
				}
			}
		}
	}

	void Arrange2(std::vector<Element> elements)
	{
		int x = 0, y = 0, index = 0;

		while (y < Height)
		{
			if (ValidPlace(elements[index], x, y) && elements[index].Count)
			{
				Allocate(elements[index], x, y, index);
				elements[index].Count--;
				x++;
			}
			else
			{
				index++;
			}
			if (index >= elements.size())
			{
				index = 0;
				x++;
			}
			if (x >= Width)
			{
				y++;
				x = 0;
			}
		}
	}

	std::vector<std::vector<int>> GetSchedule() { return Schedule; };
};
