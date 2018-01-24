
#pragma once
#include <string>
#include <iostream>

class Display
{
public:
	char **Buffer;
	int Width, Height;

	Display(int width, int height)
	{
		Width = width; Height = height;

		Buffer = new char*[height];
		for (int y = 0; y < Height; ++y)
		{
			Buffer[y] = new char[Width];
			for (int x = 0; x < Width; ++x)
			{
				Buffer[y][x] = '-';
			}
		}
	}

	~Display()
	{
		for (int y = 0; y < Height; ++y)
		{
			for (int x = 0; x < Width; ++x)
			{
				Buffer[y][x] = 0;
			}
			delete[] Buffer[y]; Buffer[y] = 0;
		}
		delete[] Buffer; Buffer = 0;
		Width = 0; Height = 0;
	}

	void Place(std::string text, int offX, int offY)
	{
		int x = offX, y = offY;
		if (x >= 0 && y >= 0 && x < Width && y < Height)
		{
			int i = 0;
			while (i < text.size() && x < Width && y < Height)
			{
				if (text[i] == '\n') { ++y; x = 0; }
				else { Buffer[y][x] = text[i]; ++x; ++i; }
			}
		}
	}

	void Print()
	{
		std::string out;
		for (int y = 0; y < Height; ++y)
		{
			for (int x = 0; x < Width; ++x)
			{
				out += Buffer[y][x];
			}
			out += '\n';
		}
		std::cout << out;
	}
};