
#include "Elements.h"

char FromVKCode(BYTE character, bool shift)
{
	if (character >= 'A' && character <= 'Z')
	{
		if (shift)
		{
			return tolower(character);
		}
		return character;
	}
}

BYTE ToVKCode(char character)
{
	if (character >= 'a' && character <= 'z' || character >= 'A' && character <= 'Z')
	{
		return toupper(character);
	}
	switch (character)
	{
	case '+':
		return VK_OEM_PLUS;
	case ',':
		return VK_OEM_COMMA;
	case '-':
		return VK_OEM_MINUS;
	case '.':
		return VK_OEM_PERIOD;
	}
	return character;
}

//###

TextBox::TextBox(int x, int y, int width, int height, Container *parentContainer, Window *srcWindow)
{
	ParentContainer = parentContainer;
	SrcWindow = srcWindow;
	X = x; Y = y; Width = width; Height = height;

	Surface = ParentContainer->CreateContainer(X, Y, Width, Height);
}

TextBox::TextBox(int x, int y, int width, int height, Window *parentWindow)
{
	ParentWindow = parentWindow;
	SrcWindow = parentWindow;
	X = x; Y = y; Width = width; Height = height;

	Surface = ParentWindow->CreateContainer(X, Y, Width, Height);
}

TextBox::~TextBox()
{
	Surface->Delete();
	Surface = 0;
	ParentContainer = 0;
	ParentWindow = 0;
	SrcWindow = 0;
}

//###

void TextBox::Update()
{
	if (Surface->State.Focus)
	{
		/*Key *keyState;
		keyState = SrcWindow->Input->KeyState;
		
		for (char character : ValidCharacters)
		{
			int VKCode = (int)ToVKCode(character);
			if (keyState[VKCode].Press || keyState[VKCode].Flip)
			{
				if (keyState[WL_SHIFT].Pressed)
				{
					Text.push_back(character);
				}
				else
				{
					Text.push_back(tolower(character));
				}
			}
		}
		if (keyState[(int)ToVKCode(WL_TAB)].Press || keyState[(int)ToVKCode(WL_TAB)].Flip)
		{
			Text.push_back('\t');
		}
		if (keyState[(int)ToVKCode(WL_RETURN)].Press || keyState[(int)ToVKCode(WL_RETURN)].Flip)
		{
			Text.push_back('\n');
		}
		if (keyState[(int)ToVKCode(WL_BACKSPACE)].Press || keyState[(int)ToVKCode(WL_BACKSPACE)].Flip)
		{
			if (Text.length() > 0) { Text.pop_back(); }
		}
		keyState = 0;*/
		Key *keyState;
		keyState = SrcWindow->Input->KeyState;

		for (int i = 0; i < 49; i++)
		{
			if (!keyState[WL_SHIFT].Pressed)
			{
				if (keyState[CharacterMap[i][0]].Press || keyState[CharacterMap[i][0]].Flip)
				{
					Text.push_back(CharacterMap[i][1]);
				}
			}
			else
			{
				if (keyState[CharacterMapShift[i][0]].Press || keyState[CharacterMapShift[i][0]].Flip)
				{
					Text.push_back(CharacterMapShift[i][1]);
				}
			}
		}
		if (keyState[(int)ToVKCode(WL_RETURN)].Press || keyState[(int)ToVKCode(WL_RETURN)].Flip)
		{
			Text.push_back('\n');
		}
		if (keyState[(int)ToVKCode(WL_BACKSPACE)].Press || keyState[(int)ToVKCode(WL_BACKSPACE)].Flip)
		{
			Text.pop_back();
		}

		keyState = 0;
	}
}

void TextBox::Render()
{
	Surface->Clear();
	Surface->FillRectangle(0, 0, Width, Height, Colour(255, 255, 255));
	Surface->DrawText(2, 0, Text, Font());
	if (Surface->State.Focus)
	{
		Surface->DrawRectangle(1, 1, Width-1, Height-1, Colour(0, 122, 204), 2);
	}
	else
	{
		Surface->DrawRectangle(1, 1, Width-1, Height-1, Colour(200, 200, 200), 2);
	}
}

//----------------------------
