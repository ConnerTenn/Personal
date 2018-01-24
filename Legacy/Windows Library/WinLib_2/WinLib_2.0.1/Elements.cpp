
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

	Text.push_back("");
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

	//switch to measue string
	int x = MeasureString(TextSurface->ParentWindow, Text[Cursor.Y].substr(0, Cursor.X), TextFont).X;
	TextSurface->DrawLine(x, Cursor.Y * CharSize.Y, x, Cursor.Y * CharSize.Y + CharSize.Y, TextFont.FontColour);

	//for (int i = max(ViewIndex - Dimensions.Y, 0), y=0; i < ViewIndex; i++, y++)
	//{
	//	TextSurface->DrawText(0, y*CharSize.Y, Text[i], TextFont);
	//}
}

void Console::Draw(Surface *surface, Int2 pos)
{
	Draw();

	//surface->CopySurface({ { pos.X, pos.Y },{ TextSurface->Dimensions.X + pos.X, TextSurface->Dimensions.Y + pos.Y } }, TextSurface, { { 0,0 },{ TextSurface->Dimensions.X, TextSurface->Dimensions.Y } });
	surface->CopySurface(TextSurface->GetRect() + pos, TextSurface, TextSurface->GetRect());
}

void Console::Resize(Int2 dimensions)
{
	Window *parentWindow = TextSurface->ParentWindow;
	delete TextSurface;
	Dimensions = dimensions;
	Init(parentWindow);
}

void Console::Write(std::string text)
{
	//retrieve the string before the cursor and after the cursor
	//strings are set to empty if cursor is outside of the Y pos bounds
	std::string currentLineBegin = Text[Cursor.Y].size() == 0 ? "" : Text[Cursor.Y].substr(0, Cursor.X);
	std::string currentLineEnd = Text[Cursor.Y].size() == 0 ? "": Text[Cursor.Y].substr(Cursor.X, Text[Cursor.Y].size() - Cursor.X);

	//erase the current line from the vector
	Text.erase(Text.begin() + Cursor.Y);

	int found = 0, previous = 0;

	//process for each new line character
	while (found != std::string::npos && found != text.size())
	{
		found = (int)text.find('\n', previous);

		if (found == -1) { found = (int)text.size(); }
		//do calculation with found string
		{			
			std::string line;
			//add the beginning of the line to the string if this is the beginning of the new text
			if (previous == 0)
			{
				line += currentLineBegin;
			}

			//add each line of text to the new line
			line += text.substr(previous, found - previous);
			Cursor.X = (int)line.size();

			//add the end of the line to the string if this is the end of the new text
			if (found == text.size())
			{
				line += currentLineEnd;
			}
			
			//insert line into the vector
			Text.insert(Text.begin() + Cursor.Y, line);

			if (Text.size() > MaxBufferSize)
			{
				Text.erase(Text.begin());
				Cursor.Y--;
			}
		}

		//increment the cursor Y pos every time a new line is found
		if (found != text.size())
		{
			Cursor.Y++; Cursor.X = 0;
		}

		previous = found + 1;
	}
	//Cursor.X = previous > found ? 0 : found;

	TextSurface->ParentWindow->AddMessage(MessageData({ WL_UPDATESURFACE, 0, 0 }), true);
}

void Console::WriteChar(char text)
{
	if (text == '\n')
	{
		std::string currentLineBegin = Text[Cursor.Y].substr(0, Cursor.X);
		std::string currentLineEnd = Text[Cursor.Y].size() == 0 ? "" : Text[Cursor.Y].substr(Cursor.X, Text[Cursor.Y].size() - Cursor.X);
		//Text.insert(Text.begin() + Cursor.Y, "");
		//Cursor.Y++; Cursor.X = 0;
		Text[Cursor.Y] = currentLineBegin;
		Cursor.Y++; Cursor.X = 0;
		Text.insert(Text.begin() + Cursor.Y, currentLineEnd);

		if (Text.size() > MaxBufferSize)
		{
			Text.erase(Text.begin());
			Cursor.Y--;
		}
	}
	else
	{
		Text[Cursor.Y].insert(Text[Cursor.Y].begin() + Cursor.X, text);
		Cursor.X++;
	}
	TextSurface->ParentWindow->MessageList.push_back(MessageData({ WL_UPDATESURFACE, 0, 0 }));
}

void Console::BackspaceChar()
{
	if (Cursor.X == 0)
	{
		if (Cursor.Y > 0)
		{
			Cursor.X = (int)Text[Cursor.Y - 1].size();
			Text[Cursor.Y - 1] += Text[Cursor.Y];
			Text.erase(Text.begin() + Cursor.Y);
			Cursor.Y--;
		}
	}
	else
	{
		Text[Cursor.Y].erase(Text[Cursor.Y].begin() + Cursor.X - 1);
		Cursor.X--;
	}
	TextSurface->ParentWindow->MessageList.push_back(MessageData({ WL_UPDATESURFACE, 0, 0 }));
}

void Console::MoveCursor(int direction)
{
	//int x;
	switch (direction)
	{
	case UP:
		//x = MeasureString(TextSurface->ParentWindow, Text[Cursor.Y].substr(0, Cursor.X), TextFont).X;
		Cursor.Y--; if (Cursor.Y < 0) { Cursor.Y = 0; }
		//Cursor.X += x - MeasureString(TextSurface->ParentWindow, Text[Cursor.Y].substr(0, Cursor.X), TextFont).X;
		Cursor.X = min((int)Text[Cursor.Y].size(), Cursor.X);
		break;
	case RIGHT:
		if (Cursor.X + 1 > Text[Cursor.Y].size()) 
		{
			if (Cursor.Y + 1 >= Text.size()) 
			{ 
				Cursor.Y = (int)Text.size() - 1; 
			} 
			else 
			{ 
				Cursor.Y++; Cursor.X = 0;
			} 
		}
		else
		{
			Cursor.X++;
		}
		break;
	case DOWN:
		//x = MeasureString(TextSurface->ParentWindow, Text[Cursor.Y].substr(0, Cursor.X), TextFont).X;
		Cursor.Y++; if (Cursor.Y >= Text.size()) { Cursor.Y = (int)Text.size() - 1; }
		//Cursor.X += x - MeasureString(TextSurface->ParentWindow, Text[Cursor.Y].substr(0, Cursor.X), TextFont).X;
		Cursor.X = min((int)Text[Cursor.Y].size(), Cursor.X);
		break;
	case LEFT:
		if (Cursor.X - 1 < 0) 
		{
			if (Cursor.Y - 1 < 0) 
			{ 
				Cursor.Y = 0; Cursor.X = 0;
			}
			else 
			{ 
				Cursor.Y--; Cursor.X = (int)Text[Cursor.Y].size(); 
			} 
		}
		else
		{
			Cursor.X--;
		}
		break;
	default:
		return;
	}

	TextSurface->ParentWindow->MessageList.push_back(MessageData({ WL_UPDATESURFACE, 0, 0 }));
}
