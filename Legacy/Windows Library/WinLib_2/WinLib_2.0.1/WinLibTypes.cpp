
#include "WinLibTypes.h"


void Throw(std::string Message)
{
#ifdef _DEBUG
	DBOUT(Message);
#endif
	throw 0;
}

Int2::Int2() {}
Int2::Int2(int x, int y) : X(x), Y(y) {}
Int2::Int2(int pos[2]) : X(pos[0]), Y(pos[1]) {}
Int2::Int2(const Int2 &pos) : X(pos.X), Y(pos.Y) {}

int Int2::operator[](int i) { if (i == 0) { return X; } else if (i == 1) { return Y; } else { Throw("ERROR::Index out Of Range\n"); return 0; } }
Int2 Int2::operator+(Int2 other) { other.X = X + other.X; other.Y = Y + other.Y; return other; }
Int2 Int2::operator-(Int2 other) { other.X = X - other.X; other.Y = Y - other.Y; return other; }
Int2 Int2::operator*(Int2 other) { other.X = X * other.X; other.Y = Y * other.Y; return other; }
Int2 Int2::operator/(Int2 other) { other.X = X / other.X; other.Y = Y / other.Y; return other; }
Int2 Int2::operator+(int val) { Int2 temp = { X + val, Y + val }; return temp; }
Int2 Int2::operator-(int val) { Int2 temp = { X - val, Y - val }; return temp; }
Int2 Int2::operator*(int val) { Int2 temp = { X * val, Y * val }; return temp; }
Int2 Int2::operator/(int val) { Int2 temp = { X / val, Y / val }; return temp; }
bool Int2::operator==(Int2 other) { return X == other.X && Y == other.Y; }


Rect::Rect() {}
Rect::Rect(int x1, int y1, int x2, int y2) : Pos1(x1, y1), Pos2(x2, y2) {}
Rect::Rect(int pos[4]) : Pos1(pos[0], pos[1]), Pos2(pos[2], pos[3]) {}
Rect::Rect(Int2 pos1, Int2 pos2) : Pos1(pos1), Pos2(pos2) {}
Rect::Rect(const Rect &rect) : Pos1(rect.Pos1), Pos2(rect.Pos2) {}

bool Rect::Intersect(Int2 point)
{
	return point.X > Pos1.X && point.X < Pos2.X && point.Y > Pos1.Y && point.Y < Pos2.Y;
}

bool Rect::Intersect(Rect other)
{
	return other.Pos2.X > Pos1.X && other.Pos1.X < Pos2.X && other.Pos2.Y > Pos1.Y && other.Pos1.Y < Pos2.Y;
}

Rect Rect::operator+(Int2 pos) { return { Pos1 + pos, Pos2 + pos }; }
Rect Rect::operator-(Int2 pos) { return{ Pos1 - pos, Pos2 - pos }; }


Colour::Colour() {}

Colour::Colour(BYTE r, BYTE g, BYTE b, BYTE a)
{
	R = r; G = g; B = b; A = a;
}

Texture::Texture(std::string filename)
{
	BITMAP bmp;

	Hbm = (HBITMAP)LoadImage(NULL, TEXT(filename.c_str()), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(Hbm, sizeof(BITMAP), &bmp);
	Width = bmp.bmWidth;
	Height = bmp.bmHeight;
}


Texture::~Texture()
{
	DeleteObject(Hbm);
}

Font::Font() {};
Font::Font(Colour fontColour)
{
	FontColour = fontColour;
}

Font::Font(std::string typeface)
{
	Typeface = typeface;
}

Font::Font(std::string typeface, Colour fontColour)
{
	Typeface = typeface;
	FontColour = fontColour;
}

Font::Font(std::string typeface, float fontSize, Colour fontColour, BYTE style)
{
	Typeface = typeface;
	FontSize = fontSize;
	FontColour = fontColour;
	Style = style;
}

MessageData::MessageData() {}
MessageData::MessageData(CallbackData message)
{
	Message = message.Message;
	Name = std::to_string(message.Message);
	Data.push_back(message.WParam);
	Data.push_back(message.LParam);
}

bool MessageData::operator==(UINT message)
{
	return Name == std::to_string(message);
}

bool MessageData::operator==(MessageData message)
{
	return Name == message.Name;
}

WPARAM MessageData::WParam()
{
	return (WPARAM)Data[0];
}

LPARAM MessageData::LParam()
{
	return (LPARAM)Data[1];
}



