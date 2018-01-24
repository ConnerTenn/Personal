
#pragma once


#include <string>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")

#undef DrawText
#define PI 3.14159265358979323
#define TAU (2.0 * PI)

struct Colour
{
	BYTE R = 0, G = 0, B = 0, A = 255;
	Colour(BYTE r, BYTE g, BYTE b, BYTE a = 255)
	{
		R = r; G = g; B = b; A = a;
	}
};

#define WL_BOLD			0b0001
#define WL_ITALIC		0b0010
#define WL_UNDERLINE	0b0100
#define WL_STRIKEOUT	0b1000

struct Font
{
	std::string Typeface = "Consolas";
	int FontSize = 15;
	BYTE Style = 0;
	int HeightWidthRatio = 2;

	Font() {};
	Font(std::string typeface, int fontSize, BYTE style, int heightWidthRatio = 2)
	{
		Typeface = typeface;
		FontSize = fontSize;
		Style = style;
		HeightWidthRatio = heightWidthRatio;
	}
};

