
#pragma once


#include <string>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")

#undef DrawText
#define PI 3.14159265358979323
#define TAU (2.0 * PI)

typedef long long int64;

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
	int FontSize = 10;
	BYTE Style = 0;
	Colour FontColour = { 0, 0, 0, 255 };
	int HeightWidthRatio = 2;

	Font() {};
	Font(Colour fontColour)
	{
		FontColour = fontColour;
	}
	Font(std::string typeface, int fontSize, BYTE style, Colour fontColour, int heightWidthRatio = 2)
	{
		Typeface = typeface;
		FontSize = fontSize;
		Style = style;
		FontColour = fontColour;
		HeightWidthRatio = heightWidthRatio;
	}
};

struct Texture
{
	HBITMAP Hbm;
	int Width;
	int Height;

	Texture(std::string filename)
	{
		BITMAP bmp;

		Hbm = (HBITMAP)LoadImage(NULL, TEXT(filename.c_str()), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		GetObject(Hbm, sizeof(BITMAP), &bmp);
		Width = bmp.bmWidth;
		Height = bmp.bmHeight;
	}
	~Texture()
	{
		DeleteObject(Hbm);
	}
};


#define WL_0 0x30
#define WL_1 0x31
#define WL_2 0x32
#define WL_3 0x33
#define WL_4 0x34
#define WL_5 0x35
#define WL_6 0x36
#define WL_7 0x37
#define WL_8 0x38
#define WL_9 0x39

#define WL_A 0x41
#define WL_B 0x42
#define WL_C 0x43
#define WL_D 0x44
#define WL_E 0x45
#define WL_F 0x46
#define WL_G 0x47
#define WL_H 0x48
#define WL_I 0x49
#define WL_J 0x4A
#define WL_K 0x4B
#define WL_L 0x4C
#define WL_M 0x4D
#define WL_N 0x4E
#define WL_O 0x4F
#define WL_P 0x50
#define WL_Q 0x51
#define WL_R 0x52
#define WL_S 0x53
#define WL_T 0x54
#define WL_U 0x55
#define WL_V 0x56
#define WL_W 0x57
#define WL_X 0x58
#define WL_Y 0x59
#define WL_Z 0x5A

#define WL_SHIFT VK_SHIFT
#define WL_RETURN VK_RETURN
#define WL_BACKSPACE VK_BACK
#define WL_TAB VK_TAB


