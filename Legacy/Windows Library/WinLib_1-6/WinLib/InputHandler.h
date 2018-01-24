
class InputHandler;
#pragma once


#include "WinLibTypes.h"
#include "WinLib.h"
#include <windows.h>

struct Key
{
	bool Pressed = false;
	bool Hold = false;
	bool Press = false;

	double FlipDelay = 500;
	double FlipCounter = FlipDelay;
	bool Flip = false;
};

struct Mouse
{
	int X = 0, Y = 0;
	bool LPressed = false;
	bool RPressed = false;
	bool MPressed = false;
	bool Click = false;
	bool DoubleClick = false;

	double DoubleClickDelay = 300;
	double SecondPressCounter = 0;
};


class InputHandler
{
private:
	Window *ParentWindow;
public:
	unsigned char CharacterMap[49][2] = { { 'A', 'a' },{ 'B', 'b' },{ 'C', 'c' },{ 'D', 'd' },{ 'E', 'e' },{ 'F', 'f' },{ 'G', 'g' },{ 'H', 'h' },{ 'I', 'i' },{ 'J', 'j' },{ 'K', 'k' },{ 'L','l' },{ 'M', 'm' },{ 'N', 'n' },{ 'O', 'o' },{ 'P', 'p' },{ 'Q', 'q' },{ 'R', 'r' },{ 'S', 's' },{ 'T', 't' },{ 'U', 'u' },{ 'V', 'v' },{ 'W', 'w' },{ 'X', 'x' },{ 'Y', 'y' },{ 'Z', 'z' },{ '1', '1' },{ '2','2' },{ '3','3' },{ '4','4' },{ '5','5' },{ '6','6' },{ '7','7' },{ '8','8' },{ '9','9' },{ '0','0' },{ ' ',' ' },{ (unsigned char)192, '`' },{ (unsigned char)189, '-' },{ (unsigned char)187, '=' },{ (unsigned char)219, '[' },{ (unsigned char)221, ']' },{ (unsigned char)186, ';' },{ (unsigned char)222, '\'' },{ (unsigned char)220, '\\' },{ (unsigned char)226, '\\' },{ (unsigned char)188,',' },{ (unsigned char)190,'.' },{ (unsigned char)191,'/' } };
	unsigned char CharacterMapShift[49][2] = { { 'A', 'A' },{ 'B', 'B' },{ 'C', 'C' },{ 'D', 'D' },{ 'E', 'E' },{ 'F', 'F' },{ 'G', 'G' },{ 'H', 'H' },{ 'I', 'I' },{ 'J', 'J' },{ 'K', 'K' },{ 'L','L' },{ 'M', 'M' },{ 'N', 'N' },{ 'O', 'O' },{ 'P', 'P' },{ 'Q', 'Q' },{ 'R', 'R' },{ 'S', 'S' },{ 'T', 'T' },{ 'U', 'U' },{ 'V', 'V' },{ 'W', 'W' },{ 'X', 'X' },{ 'Y', 'Y' },{ 'Z', 'Z' },{ '1', '!' },{ '2','@' },{ '3','#' },{ '4','$' },{ '5','%' },{ '6','^' },{ '7','&' },{ '8','*' },{ '9','(' },{ '0',')' },{ ' ',' ' },{ (unsigned char)192, '~' },{ (unsigned char)189, '_' },{ (unsigned char)187, '+' },{ (unsigned char)219, '{' },{ (unsigned char)221, '}' },{ (unsigned char)186, ':' },{ (unsigned char)222, '\"' },{ (unsigned char)220, '|' },{ (unsigned char)226, '|' },{ (unsigned char)188,'<' },{ (unsigned char)190,'>' },{ (unsigned char)191,'?' } };
	Key KeyState[255];
	Mouse MouseState;
	InputHandler(Window *parentWindow);
	void Update();
};

