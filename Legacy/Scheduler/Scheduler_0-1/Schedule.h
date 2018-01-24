
#pragma once
#include <vector>
#include <string>
#include <array>

struct ScheduleAttributes
{
	int Width;
	int Height;
	std::vector<void(*)(int x, int y, std::string &string)> AssignFunctionList;
};

class Schedule
{
private:
public:
	int Width;
	int Height;
	std::vector<std::vector<std::string>> ScheduleArray;
	std::vector<void(*)(int x, int y, std::string &string)> AssignFunctionList;

public:

public:
	void SetAttributes(ScheduleAttributes &attributes)
	{
		Width = attributes.Width;
		Height = attributes.Height;
		AssignFunctionList = attributes.AssignFunctionList;
	}

	Schedule(ScheduleAttributes &attributes)
	{
		SetAttributes(attributes);
	}

	void Init()
	{
		ScheduleArray.clear();

		ScheduleArray.resize(Height);
		for (int y = 0; y < ScheduleArray.size(); ++y)
		{
			ScheduleArray[y].resize(Width);
			for (int x = 0; x < ScheduleArray[y].size(); ++x)
			{
				ScheduleArray[y][x] = "";
			}
		}
	}

private:

public:
	void Arrange()
	{
		for (int i = 0; i < AssignFunctionList.size(); ++i) 
		{
			for (int y = 0; y < Height; ++y)
			{
				for (int x = 0; x < Width; ++x)
				{
					AssignFunctionList[i](x, y, ScheduleArray[y][x]);
				}
			}
		}
	}

	std::vector<std::vector<std::string>> GetScheduleArray()
	{
		return ScheduleArray;
	}
};