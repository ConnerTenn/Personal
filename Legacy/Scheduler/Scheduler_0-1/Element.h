
#pragma once

struct ElementAttributes
{
	int Width;
	int Height;
	bool(*ValidPlace)(int x, int y);
};

class Element
{
	int Width;
	int Height;
	bool (*ValidPlace)(int x, int y);

	Element(ElementAttributes attributes)
	{
		Width = attributes.Width;
		Height = attributes.Height;
		ValidPlace = attributes.ValidPlace;
	}
};