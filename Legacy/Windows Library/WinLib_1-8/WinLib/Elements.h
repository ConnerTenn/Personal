
class TextBox;
#pragma once

#include "WinLib.h"
#include <vector>

class TextBox
{
private:
	//int CharacterSizeMap[255][2];
	Container *Surface;
	Container *ParentContainer;
	Window *ParentWindow;
	Window *SrcWindow;
	int X, Y;
	int Width, Height;
	int CursorX = 4, CursorY = 0, CursorWidth = 0, CursorHeight = 0;
	int CursorIndex = -1;
	int MaxCharacters = -1;

public:
	std::string Text;
	Font *Typeface;
	bool EnableNewLines = false;

public:
	TextBox(int x, int y, int width, int height, Container *parentContainer, Window *srcWindow, Font typeface = Font(), int maxCharacters = -1);
	TextBox(int x, int y, int width, int height, Window *parentWindow, Font typeface = Font(), int maxCharacters = -1);
	~TextBox();
	void Update();
	void Render();

private:
	void CalculateCursorPos();
};


