
#include "Elements.h"

TextBox::TextBox(int x, int y, int width, int height, Container *parentContainer, Window *srcWindow, Font typeface, int maxCharacters)
{
	ParentContainer = parentContainer;
	SrcWindow = srcWindow;
	X = x; Y = y; Width = width; Height = height;

	Surface = ParentContainer->CreateContainer(X, Y, Width, Height);

	Typeface = new Font(typeface);
	MaxCharacters = maxCharacters;
	//CalculateCharacterSize();
	//CursorHeight = CharacterSizeMap['a'][1];
}

TextBox::TextBox(int x, int y, int width, int height, Window *parentWindow, Font typeface, int maxCharacters)
{
	ParentWindow = parentWindow;
	SrcWindow = parentWindow;
	X = x; Y = y; Width = width; Height = height;

	Surface = ParentWindow->CreateContainer(X, Y, Width, Height);

	Typeface = new Font(typeface);
	MaxCharacters = maxCharacters;
	//CalculateStringLength();
	//CalculateCharacterSize();
	//CursorHeight = CharacterSizeMap['a'][1];
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
		Key *keyState;
		keyState = SrcWindow->Input->KeyState;

		if (Text.size() < MaxCharacters || MaxCharacters == -1)
		{
			for (int i = 0; i < 49; i++)
			{
				if (!keyState[WL_SHIFT].Pressed)
				{
					if (keyState[SrcWindow->Input->CharacterMap[i][0]].Press || keyState[SrcWindow->Input->CharacterMap[i][0]].Flip)
					{
						//Text.push_back(SrcWindow->Input->CharacterMap[i][1]);
						Text.insert(CursorIndex + 1, 1, SrcWindow->Input->CharacterMap[i][1]);
						//CursorX += CharacterSizeMap[SrcWindow->Input->CharacterMap[i][0]][0] - 3;
						CursorIndex += 1;
					}
				}
				else
				{
					if (keyState[SrcWindow->Input->CharacterMapShift[i][0]].Press || keyState[SrcWindow->Input->CharacterMapShift[i][0]].Flip)
					{
						//Text.push_back(SrcWindow->Input->CharacterMapShift[i][1]);
						Text.insert(CursorIndex + 1, 1, SrcWindow->Input->CharacterMapShift[i][1]);
						//CursorX += CharacterSizeMap[SrcWindow->Input->CharacterMapShift[i][0]][0] - 3;
						CursorIndex += 1;
					}
				}
			}
			if ((keyState[WL_RETURN].Press || keyState[WL_RETURN].Flip) && EnableNewLines)
			{
				Text.push_back('\n');
				CursorIndex += 1;
				//CursorX = 0;
				//CursorY += CharacterSizeMap[SrcWindow->Input->CharacterMap['a'][0]][1];
			}
		}
		if (keyState[WL_BACKSPACE].Press || keyState[WL_BACKSPACE].Flip)
		{
			if (CursorIndex >= 0) { Text.erase(CursorIndex, 1); CursorIndex -= 1;}
		}
		if (keyState[WL_LEFT].Press || keyState[WL_LEFT].Flip)
		{
			if (CursorIndex >= 0) { CursorIndex -= 1; }
		}
		if (keyState[WL_RIGHT].Press || keyState[WL_RIGHT].Flip)
		{
			if (CursorIndex < (int)Text.size() - 1) { CursorIndex += 1; }
		}

		CalculateCursorPos();

		keyState = 0;
	}
}

void TextBox::Render()
{
	Surface->Clear();
	Surface->FillRectangle(0, 0, Width, Height, Colour(255, 255, 255));
	Surface->DrawText(2, 0, Text, *Typeface);
	if (Surface->State.Focus)
	{
		Surface->DrawRectangle(1, 1, Width-1, Height-1, Colour(0, 122, 204), 2);
	}
	else
	{
		Surface->DrawRectangle(1, 1, Width-1, Height-1, Colour(200, 200, 200), 2);
	}
	if (Surface->State.Focus) { Surface->DrawLine(CursorX, CursorY, CursorX, CursorY + CursorHeight, Colour(0, 0, 0)); }
}

//###

void TextBox::CalculateCursorPos()
{
	/*Gdiplus::Font fnt(std::wstring(Typeface->Typeface.begin(), Typeface->Typeface.end()).c_str(), (Gdiplus::REAL)Typeface->FontSize, (INT)Typeface->Style);
	Gdiplus::RectF rect;
	Surface->Graphics->MeasureString(std::wstring(Text.begin(), Text.end()).c_str(), Text.size(), &fnt, Gdiplus::PointF(10,0), &rect);
	CursorX = rect.Width;
	CursorHeight = rect.Height;//*/
	/*
	Gdiplus::RectF layout((Gdiplus::REAL)X, (Gdiplus::REAL)Y, (Gdiplus::REAL)Width, (Gdiplus::REAL)Height);
	Gdiplus::CharacterRange range((INT)0, (INT)1);
	//MeasureFormat.SetMeasurableCharacterRanges(1, &range);
	Gdiplus::StringFormat fmt;
	fmt.SetMeasurableCharacterRanges(1, &range);
	Gdiplus::Region region;
	Gdiplus::Font fnt(std::wstring(Typeface->Typeface.begin(), Typeface->Typeface.end()).c_str(), (Gdiplus::REAL)Typeface->FontSize, (INT)Typeface->Style);
	Gdiplus::RectF rec;
	for (int i = 0; i < 255; ++i)
	{
		WCHAR a = i;
		Surface->Graphics->MeasureCharacterRanges(&a, -1, &fnt, layout, &fmt, 1, &region);
		
		region.GetBounds(&rec, Surface->Graphics);

		CharacterSizeMap[i][0] = (int)rec.Width;
		CharacterSizeMap[i][1] = (int)rec.Height;
	}
	*/
	if (CursorIndex >= 0)
	{
		//CursorIndex = (int)Text.size() - 1;
		//Gdiplus::RectF layout((Gdiplus::REAL)X, (Gdiplus::REAL)Y, (Gdiplus::REAL)Width, (Gdiplus::REAL)Height);
		//Gdiplus::RectF layout((Gdiplus::REAL)0, (Gdiplus::REAL)0, (Gdiplus::REAL)Width, (Gdiplus::REAL)Height);
		Gdiplus::RectF layout((Gdiplus::REAL)0, (Gdiplus::REAL)0, (Gdiplus::REAL)(Text.size() * CursorHeight), (Gdiplus::REAL)(Text.size() * CursorHeight));
		Gdiplus::CharacterRange range((INT)CursorIndex, (INT)1);
		//MeasureFormat.SetMeasurableCharacterRanges(1, &range);
		Gdiplus::StringFormat fmt;
		fmt.SetMeasurableCharacterRanges(1, &range);
		fmt.SetFormatFlags(Gdiplus::StringFormatFlagsMeasureTrailingSpaces);
		//fmt.SetFormatFlags(Gdiplus::StringFormatFlagsNoWrap);
		Gdiplus::Region region;
		Gdiplus::Font fnt(std::wstring(Typeface->Typeface.begin(), Typeface->Typeface.end()).c_str(), (Gdiplus::REAL)Typeface->FontSize, (INT)Typeface->Style);
		Gdiplus::RectF rec;

		Surface->Graphics->MeasureCharacterRanges(std::wstring(Text.begin(), Text.end()).c_str(), -1, &fnt, layout, &fmt, 1, &region);

		region.GetBounds(&rec, Surface->Graphics);
		if (Text.at(CursorIndex) == '\n')
		{
			CursorX = 3;
			CursorY = (int)(rec.Y + rec.Height);
			CursorHeight = (int)(rec.Height);
			CursorWidth = 2;
		}
		else
		{
			CursorX = (int)(rec.X + rec.Width + 1);
			CursorY = (int)(rec.Y);
			CursorHeight = (int)(rec.Height);
			CursorWidth = (int)(rec.Width);
		}
	}
	else
	{
		//Gdiplus::RectF layout((Gdiplus::REAL)X, (Gdiplus::REAL)Y, (Gdiplus::REAL)Width, (Gdiplus::REAL)Height);
		Gdiplus::RectF layout((Gdiplus::REAL)0, (Gdiplus::REAL)0, (Gdiplus::REAL)Width, (Gdiplus::REAL)Height);
		Gdiplus::CharacterRange range((INT)0, (INT)1);
		//MeasureFormat.SetMeasurableCharacterRanges(1, &range);
		Gdiplus::StringFormat fmt;
		fmt.SetMeasurableCharacterRanges(1, &range);
		fmt.SetFormatFlags(Gdiplus::StringFormatFlagsMeasureTrailingSpaces);
		Gdiplus::Region region;
		Gdiplus::Font fnt(std::wstring(Typeface->Typeface.begin(), Typeface->Typeface.end()).c_str(), (Gdiplus::REAL)Typeface->FontSize, (INT)Typeface->Style);
		Gdiplus::RectF rec;

		WCHAR a = '1';
		Surface->Graphics->MeasureCharacterRanges(&a, -1, &fnt, layout, &fmt, 1, &region);
		
		region.GetBounds(&rec, Surface->Graphics);
		
		CursorX = 3;
		CursorY = (int)(rec.Y);
		CursorHeight = (int)(rec.Height);
		CursorWidth = 2;
	}
}

//----------------------------
