
#pragma once

#include "WinLib.h"


class TextArray
{
public:
	Int2 CharSize;
	Int2 Dimensions;
	bool Carry = true;
	std::vector<std::string> Text;
	Surface *TextSurface;
	Font TextFont;

	TextArray(TextArrayInfo *textArrayInfo);
	~TextArray();
	void Init(Window *parentWindow);

	void Draw();

	void Resize(Int2 dimensions);
	void WriteChar(Int2 pos, char character);
	void WriteString(Int2 pos, std::string text);
	char GetCharacter(Int2 pos);
	std::string GetString(Int2 pos, int length);
};


#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

class Console //switch to having to pass SurfaceInfo into ConsoleInfo
{
public:
	Int2 CharSize;
	Int2 Dimensions;
	std::vector<std::string> Text;
	int MaxBufferSize = 100;
	int ViewIndex = 0;//0 is last line at the lowest line, on screen.  positive is scrolling up.  Negative is scrolling down
	Surface *TextSurface;
	Font TextFont;
	bool Insert = true;
	Int2 Cursor;

	Console(ConsoleInfo *consoleInfo);
	~Console();
	void Init(Window *parentWindow);

	void Draw();
	void Draw(Surface *surface, Int2 pos);

	void Resize(Int2 dimensions);
	void Write(std::string text);
	void WriteChar(char text);
	void BackspaceChar();
	void MoveCursor(int direction);
	void Scroll(int scroll);
};

