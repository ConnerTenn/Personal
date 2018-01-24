
#include "Container.h"

Container::Container(int x, int y, int width, int height, Container *parent, Window *srcWindow, int frameNum)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
	FrameNum = frameNum < 1 ? MessageBox(srcWindow->Hwnd, "Container::FrameNum cannot be less than 1;\nSetting value to 1.", "ERROR", MB_OK), 1 : frameNum;
	Parent = parent;
	SrcWindow = srcWindow;

	/*Hdc = new HDC[FrameNum];
	for (int i = 0; i < FrameNum; i++)
	{
		Hdc[i] = CreateCompatibleDC(SrcWindow->Ps.hdc);
	}
	Hbm = new HBITMAP[FrameNum];
	for (int i = 0; i < FrameNum; i++)
	{
		Hbm[i] = CreateCompatibleBitmap(SrcWindow->Ps.hdc, Width, Height);
	}

	for (int i = 0; i < FrameNum; i++)
	{
		SetBkMode(Hdc[i], TRANSPARENT);
		SetStretchBltMode(Hdc[i], COLORONCOLOR);
	}*/

	Hdc = new HDC[FrameNum];
	Hbm = new HBITMAP[FrameNum];
	for (int i = 0; i < FrameNum; i++)
	{
		Hdc[i] = CreateCompatibleDC(SrcWindow->Ps.hdc);
		Hbm[i] = CreateCompatibleBitmap(SrcWindow->Ps.hdc, Width, Height);

		SetBkMode(Hdc[i], TRANSPARENT);
		SetStretchBltMode(Hdc[i], COLORONCOLOR);
	}
	
	SelectObject(Hdc[CurrentFrame], Hbm[CurrentFrame]);
	Graphics = new Gdiplus::Graphics(Hdc[CurrentFrame]);

	SolidBrush = new Gdiplus::SolidBrush(Gdiplus::Color(0, 0, 0, 0));
	Pen = new Gdiplus::Pen(Gdiplus::Color(0, 0, 0, 0));

	HdcDisplay = CreateCompatibleDC(SrcWindow->Ps.hdc);
	HbmDisplay = CreateCompatibleBitmap(SrcWindow->Ps.hdc, Width, Height);
	SelectObject(HdcDisplay, HbmDisplay);

	SetBkMode(HdcDisplay, TRANSPARENT);
	SetStretchBltMode(HdcDisplay, COLORONCOLOR);

	UpdateTransformations();
}

Container::~Container()
{
	for (Container *container : ContainerList)
	{
		delete container;
	}

	delete Graphics;
	delete SolidBrush;
	delete Pen;
	Parent = 0;
	SrcWindow = 0;
	for (int i = 0; i < FrameNum; i++)
	{
		DeleteObject(Hdc[i]);
		DeleteObject(Hbm[i]);
	}
	DeleteObject(HbmDisplay);
	DeleteObject(Hfnt);
}

//###

Container *Container::CreateContainer(int x, int y, int width, int height, int frameNum)
{
	Container *container = new Container(x, y, width, height, this, SrcWindow, frameNum);
	ContainerList.push_back(container);
	return container;
}

void Container::Remove()
{
	if (Parent)
	{
		for (Container *container : ContainerList)
		{
			container->Parent = Parent;
			Parent->ContainerList.push_back(container);
		}
		Parent->ContainerList.erase(std::remove(Parent->ContainerList.begin(), Parent->ContainerList.end(), this), Parent->ContainerList.end());
	}
	else
	{
		for (Container *container : ContainerList)
		{
			container->Parent = NULL;
			SrcWindow->ContainerList.push_back(container);
		}
		SrcWindow->ContainerList.erase(std::remove(SrcWindow->ContainerList.begin(), SrcWindow->ContainerList.end(), this), SrcWindow->ContainerList.end());
	}
	ContainerList.clear();
	this->~Container();
}

void Container::Delete()
{
	if (Parent)
	{
		Parent->ContainerList.erase(std::remove(Parent->ContainerList.begin(), Parent->ContainerList.end(), this), Parent->ContainerList.end());
	}
	else
	{
		SrcWindow->ContainerList.erase(std::remove(SrcWindow->ContainerList.begin(), SrcWindow->ContainerList.end(), this), SrcWindow->ContainerList.end());
	}
	this->~Container();
}

void Container::UpdateTransformations()
{
	AbsX = X;
	AbsY = Y;
	if (Parent)
	{
		AbsScaleX = ScaleX * Parent->AbsScaleX;
		AbsScaleY = ScaleY * Parent->AbsScaleY;

		AbsX = (int)(AbsX * AbsScaleX);
		AbsY = (int)(AbsY * AbsScaleY);

		AbsX += Parent->AbsX;
		AbsY += Parent->AbsY;		
	}
	else
	{
		AbsScaleX = ScaleX;
		AbsScaleY = ScaleY;
	}
	for (Container *container : ContainerList)
	{
		container->UpdateTransformations();
	}
}


void Container::Render()
{
	if (Show)
	{
		//StretchBlt(SrcWindow->Hdc, AbsX, AbsY, (int)(ScaleX * Width), (int)(ScaleY * Height), Hdc[CurrentFrame], 0, 0, Width, Height, SRCCOPY);
		//TransparentBlt(SrcWindow->Hdc, AbsX, AbsY, (int)(ScaleX * Width), (int)(ScaleY * Height), Hdc, 0, 0, Width, Height, SRCCOPY);
		StretchBlt(HdcDisplay, 0, 0, Width, Height, Hdc[CurrentFrame], 0, 0, Width, Height, SRCCOPY);
		for (Container *container : ContainerList)
		{
			container->Render();
		}
		if (Parent)
		{
			StretchBlt(Parent->HdcDisplay, X, Y, (int)(AbsScaleX * Width), (int)(AbsScaleY * Height), HdcDisplay, 0, 0, Width, Height, SRCCOPY);
		}
		else
		{
			StretchBlt(SrcWindow->Hdc, AbsX, AbsY, (int)(AbsScaleX * Width), (int)(AbsScaleY * Height), HdcDisplay, 0, 0, Width, Height, SRCCOPY);
		}
	}
}

void Container::UpdateMsg()
{
	//if (Parent) { Show = Parent->Show; }
	//Message Code
	InputHandler *input = SrcWindow->Input;
	if (input->MouseState.LClick && Show)
	{
		if (input->MouseState.X >= AbsX && input->MouseState.X <= AbsX + Width && input->MouseState.Y >= AbsY && input->MouseState.Y <= AbsY + Height)
		{
			SrcWindow->Focus = this;
		}
	}

	for (Container *container : ContainerList)
	{
		container->UpdateMsg();
	}
}
//###

void Container::Translate(int x, int y)
{
	X += x;
	Y += y;
	UpdateTransformations();
}

void Container::SetPos(int x, int y)
{
	X = x;
	Y = y;
	UpdateTransformations();
}

void Container::Scale(double x, double y)
{
	ScaleX = x;
	ScaleY = y;
	UpdateTransformations();
}

void Container::Resize(int width, int height)
{
	Width = width;
	Height = height;

	for (int i = 0; i < FrameNum; i++)
	{
		DeleteObject(Hbm[i]);
		Hbm[i] = CreateCompatibleBitmap(SrcWindow->Ps.hdc, Width, Height);
	}
	SelectObject(Hdc[CurrentFrame], Hbm[CurrentFrame]);

	delete Graphics;
	Graphics = new Gdiplus::Graphics(Hdc[CurrentFrame]);

	DeleteObject(HbmDisplay);
	HbmDisplay = CreateCompatibleBitmap(SrcWindow->Ps.hdc, Width, Height);
	SelectObject(HdcDisplay, HbmDisplay);
}

void Container::SetCurrentFrame(int currentFrame)
{
	CurrentFrame = currentFrame;
	SelectObject(Hdc[CurrentFrame], Hbm[CurrentFrame]);
	delete Graphics;
	Graphics = new Gdiplus::Graphics(Hdc[CurrentFrame]);
}

void Container::SetShow(bool show)
{
	Show = show;
	for (Container *container : ContainerList)
	{
		container->SetShow(Show);
	}

}

//###

void Container::Clear()
{
	Graphics->Clear(Gdiplus::Color(0, 0, 0));
}

void Container::FillRectangle(int x, int y, int width, int height, Colour colour)
{
	SolidBrush->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillRectangle(SolidBrush, x, y, width, height);
}

void Container::DrawRectangle(int x, int y, int width, int height, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawRectangle(Pen, x, y, width - 1, height - 1);
}

void Container::FillEllipse(int x, int y, int width, int height, Colour colour)
{
	SolidBrush->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillEllipse(SolidBrush, x, y, width, height);
}

void Container::FillEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle)
{
	SolidBrush->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillPie(SolidBrush, x, y, width, height, (Gdiplus::REAL)((startAngle / TAU * 360.0) - 90.0), (Gdiplus::REAL)(sweepAngle/TAU * 360.0));
}

void Container::DrawEllipse(int x, int y, int width, int height, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawEllipse(Pen, x, y, width, height);
}

void Container::DrawEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawArc(Pen, x, y, width, height, (Gdiplus::REAL)((startAngle / TAU * 360.0) - 90.0), (Gdiplus::REAL)(sweepAngle / TAU * 360.0));
}

void Container::DrawLine(int x1, int y1, int x2, int y2, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawLine(Pen, x1, y1, x2, y2);
}

void Container::DrawImage(int x, int y, int width, int height,  Texture *texture)
{
	HDC hdc = CreateCompatibleDC(Hdc[CurrentFrame]);
	SelectObject(hdc, texture->Hbm);
	//SetStretchBltMode(Hdc[CurrentFrame], COLORONCOLOR);
	StretchBlt(Hdc[CurrentFrame], x, y, width, height, hdc, 0, 0, texture->Width, texture->Height, SRCCOPY);
	DeleteObject(hdc);
}

void Container::DrawText(int x, int y, std::string text, Font font)
{
	Typeface = new Gdiplus::Font(std::wstring(font.Typeface.begin(), font.Typeface.end()).c_str(), (Gdiplus::REAL)font.FontSize, (INT)font.Style);
	SolidBrush->SetColor(Gdiplus::Color(font.FontColour.A, font.FontColour.R, font.FontColour.G, font.FontColour.B));
	Graphics->DrawString(std::wstring(text.begin(), text.end()).c_str(), (INT)text.length(), Typeface, Gdiplus::PointF((Gdiplus::REAL)x, (Gdiplus::REAL)y), SolidBrush);
	delete Typeface; Typeface = 0;
}

