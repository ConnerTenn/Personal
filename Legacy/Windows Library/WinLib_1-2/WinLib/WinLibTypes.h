
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

struct Texture
{
	Gdiplus::Image *Image;
	Texture(std::string filename)		
	{
		Image = new Gdiplus::Image(std::wstring(std::wstring(filename.begin(), filename.end()).c_str()).c_str());
	}
	~Texture()
	{
		delete Image; Image = 0;
	}
};

struct Texture2
{
	HDC Hdc;
	HBITMAP Hbm;
	int Width;
	int Height;

	//Gdiplus::Image *Image;
	Texture2(std::string filename, PAINTSTRUCT *ps)
	{
		Gdiplus::Image *Image = new Gdiplus::Image(std::wstring(std::wstring(filename.begin(), filename.end()).c_str()).c_str());

		Width = Image->GetWidth();
		Height = Image->GetHeight();

		Hdc = CreateCompatibleDC(ps->hdc);
		Hbm = CreateCompatibleBitmap(ps->hdc, Width, Height);

		SelectObject(Hdc, Hbm);
		Gdiplus::Graphics *graphics = new Gdiplus::Graphics(Hdc);

		graphics->DrawImage(Image, 0, 0, Width, Height);

		delete graphics; graphics = 0;
	}
	~Texture2()
	{
		DeleteObject(Hdc);
		DeleteObject(Hbm);
	}
};

struct Texture3
{
	HBITMAP Hbm;
	int Width;
	int Height;

	Texture3(std::string filename)
	{
		BITMAP bmp;

		Hbm = (HBITMAP)LoadImage(NULL, TEXT(filename.c_str()), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		GetObject(Hbm, sizeof(BITMAP), &bmp);
		Width = bmp.bmWidth;
		Height = bmp.bmHeight;
	}
	~Texture3()
	{
		DeleteObject(Hbm);
	}
};



