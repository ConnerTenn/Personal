
#include "Elements.h"

TextArray::TextArray(TextArrayInfo *textArrayInfo)
{
	Dimensions = textArrayInfo->Dimensions;
	Carry = textArrayInfo->Carry;
	TextFont = textArrayInfo->TextFont;

	Init(textArrayInfo->ParentWindow);
}

TextArray::~TextArray()
{
	delete TextSurface;
}

void TextArray::Init(Window *parentWindow)
{
	CharSize = MeasureString(parentWindow, std::string("A"), TextFont); CharSize.X += 1;//make char size into an array
	int width = MeasureString(parentWindow, std::string(Dimensions.X, 'A'), TextFont).X + 1;

	SurfaceInfo surfaceInfo;
	surfaceInfo.Dimensions = { width, Dimensions.Y * CharSize.Y };
	surfaceInfo.ParentWindow = parentWindow;
	TextSurface = new Surface(&surfaceInfo);

	Text.resize(Dimensions.Y);
	for (int i = 0; i < Dimensions.Y; i++)
	{
		Text[i] = (std::string(Dimensions.X, ' '));
	}
}

void TextArray::Draw()
{
	TextSurface->Clear();
	for (int i = 0; i < Text.size(); i++)
	{
		TextSurface->DrawText(0, i*CharSize.Y, Text[i], TextFont);
	}
}

void TextArray::Resize(Int2 dimensions)
{
	std::string buffer = GetString({ 0,0 }, Dimensions.X * Dimensions.Y);
	
	Window *parentWindow = TextSurface->ParentWindow;
	delete TextSurface;
	Dimensions = dimensions;
	Text.clear();
	Init(parentWindow);

	WriteString({ 0,0 }, buffer);
}

void TextArray::WriteChar(Int2 pos, char character)
{
	//if (pos.X < Dimensions.X && pos.Y < Dimensions.Y)
	//{
	Text[pos.Y][pos.X] = character;
	//}
}

void TextArray::WriteString(Int2 pos, std::string text)
{
	while (text.length() > 0 && pos.Y < Dimensions.Y)
	{
		Text[pos.Y].replace(pos.X, min(Dimensions.X - (pos.X), text.length()), text, 0, min(Dimensions.X - (pos.X), text.length()));
		text.erase(0, min(Dimensions.X - (pos.X), text.length()));
		
		pos.Y++;
		pos.X = 0;
	}
}

char TextArray::GetCharacter(Int2 pos)
{
	return Text[pos.Y][pos.X];
}

std::string TextArray::GetString(Int2 pos, int length)
{
	std::string out;

	while (length > 0)
	{
		out += Text[pos.Y].substr(pos.X, min(Dimensions.X - pos.X, length));
		length -= min(Dimensions.X - pos.X, length);

		pos.Y++;
		pos.X = 0;
	}

	return out;
}


Console::Console(ConsoleInfo *consoleInfo)
{
	Dimensions = consoleInfo->Dimensions;
	TextFont = consoleInfo->TextFont;

	Init(consoleInfo->ParentWindow);
}

Console::~Console()
{
	delete TextSurface;
}

void Console::Init(Window *parentWindow)
{
	CharSize = MeasureString(parentWindow, std::string("A"), TextFont); CharSize.X += 1;//make char size into an array
	int width = MeasureString(parentWindow, std::string(Dimensions.X, 'A'), TextFont).X + 1;

	SurfaceInfo surfaceInfo;
	surfaceInfo.Dimensions = { width, Dimensions.Y * CharSize.Y };
	surfaceInfo.ParentWindow = parentWindow;
	TextSurface = new Surface(&surfaceInfo);
}

void Console::Draw()
{
	TextSurface->Clear();
	//Bottom Drawn line: Text.size() - ViewIndex
	//Top Drawn Line: max(0, (Text.size() - ViewIndex) - Dimensions.Y)

	int y = min((int)Text.size() - 1, Dimensions.Y);// +(min(0, ViewIndex));
	y = max(0, y + min(0, ViewIndex));
	for (int i = (int)Text.size() - max(0, ViewIndex) - 1; i >= max(0, ((int)Text.size() - max(0, ViewIndex) - 1) - Dimensions.Y); i--)
	{
		TextSurface->DrawText(0, y*CharSize.Y, Text[i], TextFont);

		y--;
	}

	//for (int i = max(ViewIndex - Dimensions.Y, 0), y=0; i < ViewIndex; i++, y++)
	//{
	//	TextSurface->DrawText(0, y*CharSize.Y, Text[i], TextFont);
	//}
}

void Console::Write(std::string text)
{

}


