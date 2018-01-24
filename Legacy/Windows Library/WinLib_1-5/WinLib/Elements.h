
class TextBox;
#pragma once

#include "WinLib.h"
#include <vector>

inline char FromVKCode(BYTE character, bool shift);
inline BYTE charVKCode(BYTE character);

class TextBox
{
private:
	//const std::string ValidCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .,'\"!?{}[]()-_=+*/\\";
	//unsigned char CharacterMap[48][2] = { { 'A', 'a' },{ 'B', 'b' },{ 'C', 'c' },{ 'D', 'd' },{ 'E', 'e' },{ 'F', 'f' },{ 'G', 'g' },{ 'H', 'h' },{ 'I', 'i' },{ 'J', 'j' },{ 'K', 'k' },{ 'L','l' },{ 'M', 'm' },{ 'N', 'n' },{ 'O', 'o' },{ 'P', 'p' },{ 'Q', 'q' },{ 'R', 'r' },{ 'S', 's' },{ 'T', 't' },{ 'U', 'u' },{ 'V', 'v' },{ 'W', 'w' },{ 'X', 'x' },{ 'Y', 'y' },{ 'Z', 'z' },{ '1', '1' },{ '2','2' },{ '3','3' },{ '4','4' },{ '5','5' },{ '6','6' },{ '7','7' },{ '8','8' },{ '9','9' },{ '0','0' },{ (char)192, '`' },{ (char)189, '-' },{ (char)187, '=' },{ (char)219, '[' },{ (char)221, ']' },{ (char)186, ';' },{ (char)222, '\'' },{ (char)220, '\\' },{ (char)226, '\\' },{ (char)188,',' },{ (char)190,'.' },{ (char)191,'/' } };
	//std::vector<std::vector<BYTE>> CharacterMap = { 
	//	{ 'A', 'a' },{ 'B', 'b' },{ 'C', 'c' },{ 'D', 'd' },{ 'E', 'e' },{ 'F', 'f' },{ 'G', 'g' },{ 'H', 'h' },{ 'I', 'i' },{ 'J', 'j' },{ 'K', 'k' },{ 'L','l' },{ 'M', 'm' },{ 'N', 'n' },{ 'O', 'o' },{ 'P', 'p' },{ 'Q', 'q' },{ 'R', 'r' },{ 'S', 's' },{ 'T', 't' },{ 'U', 'u' },{ 'V', 'v' },{ 'W', 'w' },{ 'X', 'x' },{ 'Y', 'y' },{ 'Z', 'z' },
	//	{ '1', '1' },{ '2','2' },{ '3','3' },{ '4','4' },{ '5','5' },{ '6','6' },{ '7','7' },{ '8','8' },{ '9','9' },{ '0','0' },
	//	{ 192, '`' },{ 189, '-' },{ 187, '=' },{ 219, '[' },{ 221, ']' },{ 186, ';' },{ 222, '\'' },{ 220, '\\' },{ 226, '\\' },{ 188,',' },{ 190,'.' },{ 191,'/' } };
	//unsigned char CharacterMapShift[48][2] = { { 'A', 'A' },{ 'B', 'B' },{ 'C', 'C' },{ 'D', 'D' },{ 'E', 'E' },{ 'F', 'F' },{ 'G', 'G' },{ 'H', 'H' },{ 'I', 'I' },{ 'J', 'J' },{ 'K', 'K' },{ 'L','L' },{ 'M', 'M' },{ 'N', 'N' },{ 'O', 'O' },{ 'P', 'P' },{ 'Q', 'Q' },{ 'R', 'R' },{ 'S', 'S' },{ 'T', 'T' },{ 'U', 'U' },{ 'V', 'V' },{ 'W', 'W' },{ 'X', 'X' },{ 'Y', 'Y' },{ 'Z', 'Z' },{ '1', '!' },{ '2','@' },{ '3','#' },{ '4','$' },{ '5','%' },{ '6','^' },{ '7','&' },{ '8','*' },{ '9','(' },{ '0',')' },{ (char)192, '~' },{ (char)189, '_' },{ (char)187, '+' },{ (char)219, '{' },{ (char)221, '}' },{ (char)186, ':' },{ (char)222, '\"' },{ (char)220, '|' },{ (char)226, '|' },{ (char)188,'<' },{ (char)190,'>' },{ (char)191,'?' } };
	//std::vector<std::vector<char>> CharacterMapShift = { { 'A', 'A' },{ 'B', 'B' },{ 'C', 'C' },{ 'D', 'D' },{ 'E', 'E' },{ 'F', 'F' },{ 'G', 'G' },{ 'H', 'H' },{ 'I', 'I' },{ 'J', 'J' },{ 'K', 'K' },{ 'L','L' },{ 'M', 'M' },{ 'N', 'N' },{ 'O', 'O' },{ 'P', 'P' },{ 'Q', 'Q' },{ 'R', 'R' },{ 'S', 'S' },{ 'T', 'T' },{ 'U', 'U' },{ 'V', 'V' },{ 'W', 'W' },{ 'X', 'X' },{ 'Y', 'Y' },{ 'Z', 'Z' },{ '1', '!' },{ '2','@' },{ '3','#' },{ '4','$' },{ '5','%' },{ '6','^' },{ '7','&' },{ '8','*' },{ '9','(' },{ '0',')' },{ (char)192, '~' },{ (char)189, '_' },{ (char)187, '+' },{ (char)219, '{' },{ (char)221, '}' },{ (char)186, ':' },{ (char)222, '\"' },{ (char)220, '|' },{ (char)226, '|' },{ (char)188,'<' },{ (char)190,'>' },{ (char)191,'?' } };
	unsigned char CharacterMap[49][2] = { { 'A', 'a' },{ 'B', 'b' },{ 'C', 'c' },{ 'D', 'd' },{ 'E', 'e' },{ 'F', 'f' },{ 'G', 'g' },{ 'H', 'h' },{ 'I', 'i' },{ 'J', 'j' },{ 'K', 'k' },{ 'L','l' },{ 'M', 'm' },{ 'N', 'n' },{ 'O', 'o' },{ 'P', 'p' },{ 'Q', 'q' },{ 'R', 'r' },{ 'S', 's' },{ 'T', 't' },{ 'U', 'u' },{ 'V', 'v' },{ 'W', 'w' },{ 'X', 'x' },{ 'Y', 'y' },{ 'Z', 'z' },{ '1', '1' },{ '2','2' },{ '3','3' },{ '4','4' },{ '5','5' },{ '6','6' },{ '7','7' },{ '8','8' },{ '9','9' },{ '0','0' },{ ' ',' ' },{ (unsigned char)192, '`' },{ (unsigned char)189, '-' },{ (unsigned char)187, '=' },{ (unsigned char)219, '[' },{ (unsigned char)221, ']' },{ (unsigned char)186, ';' },{ (unsigned char)222, '\'' },{ (unsigned char)220, '\\' },{ (unsigned char)226, '\\' },{ (unsigned char)188,',' },{ (unsigned char)190,'.' },{ (unsigned char)191,'/' } };
	unsigned char CharacterMapShift[49][2] = { { 'A', 'A' },{ 'B', 'B' },{ 'C', 'C' },{ 'D', 'D' },{ 'E', 'E' },{ 'F', 'F' },{ 'G', 'G' },{ 'H', 'H' },{ 'I', 'I' },{ 'J', 'J' },{ 'K', 'K' },{ 'L','L' },{ 'M', 'M' },{ 'N', 'N' },{ 'O', 'O' },{ 'P', 'P' },{ 'Q', 'Q' },{ 'R', 'R' },{ 'S', 'S' },{ 'T', 'T' },{ 'U', 'U' },{ 'V', 'V' },{ 'W', 'W' },{ 'X', 'X' },{ 'Y', 'Y' },{ 'Z', 'Z' },{ '1', '!' },{ '2','@' },{ '3','#' },{ '4','$' },{ '5','%' },{ '6','^' },{ '7','&' },{ '8','*' },{ '9','(' },{ '0',')' },{ ' ',' ' },{ (unsigned char)192, '~' },{ (unsigned char)189, '_' },{ (unsigned char)187, '+' },{ (unsigned char)219, '{' },{ (unsigned char)221, '}' },{ (unsigned char)186, ':' },{ (unsigned char)222, '\"' },{ (unsigned char)220, '|' },{ (unsigned char)226, '|' },{ (unsigned char)188,'<' },{ (unsigned char)190,'>' },{ (unsigned char)191,'?' } };
	Container *Surface;
	Container *ParentContainer;
	Window *ParentWindow;
	Window *SrcWindow;
	int X, Y;
	int Width, Height;

public:
	std::string Text;

public:
	TextBox(int x, int y, int width, int height, Container *parentContainer, Window *srcWindow);
	TextBox(int x, int y, int width, int height, Window *parentWindow);
	~TextBox();
	void Update();
	void Render();
};


