
#include "Surface.h"

Int2 MeasureString(Surface *surface, std::string string, Font font)
{
	Gdiplus::Font gdiFont(std::wstring(font.Typeface.begin(), font.Typeface.end()).c_str(), (Gdiplus::REAL)font.FontSize, (INT)font.Style);
	Gdiplus::RectF box;
	surface->Graphics->MeasureString(std::wstring(string.begin(), string.end()).c_str(), (int)string.length(), &gdiFont, Gdiplus::PointF(0, 0), Gdiplus::StringFormat::GenericTypographic(), &box);

	return { (int)box.Width, (int)box.Height };
	
}

Int2 MeasureString(Window *parentWindow, std::string string, Font font)
{
	return MeasureString(parentWindow->WindowSurface, string, font);
}

Surface::Surface(SurfaceInfo *surfaceInfo)
{
	ParentWindow = surfaceInfo->ParentWindow;
	Dimensions = surfaceInfo->Dimensions;
	ClearColour = surfaceInfo->ClearColour;

	Hdc = CreateCompatibleDC(ParentWindow->Ps.hdc);
	Hbm = CreateCompatibleBitmap(ParentWindow->Ps.hdc, Dimensions.X, Dimensions.Y);
	SelectObject(Hdc, Hbm);

	Graphics = new Gdiplus::Graphics(Hdc);

	SolidBrush = new Gdiplus::SolidBrush(Gdiplus::Color(0, 0, 0, 0));
	Pen = new Gdiplus::Pen(Gdiplus::Color(0, 0, 0, 0));

	SetBkMode(Hdc, TRANSPARENT);
	SetStretchBltMode(Hdc, COLORONCOLOR);
	Graphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
}

Surface::~Surface()
{
	ParentWindow = 0;
	delete Graphics;
	delete SolidBrush;
	delete Pen;
	delete Typeface;
	DeleteObject(Hdc);
	DeleteObject(Hbm);
}

void Surface::Resize(Int2 dimensions)
{
	Dimensions = dimensions;

	DeleteObject(Hbm);
	Hbm = CreateCompatibleBitmap(ParentWindow->Ps.hdc, Dimensions.X, Dimensions.Y);
	SelectObject(Hdc, Hbm);
}

void Surface::Clear()
{
	Graphics->Clear(Gdiplus::Color(ClearColour.R, ClearColour.G, ClearColour.B));
}

void Surface::FillRectangle(int x, int y, int width, int height, Colour colour)
{
	SolidBrush->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillRectangle(SolidBrush, x, y, width, height);
}

void Surface::DrawRectangle(int x, int y, int width, int height, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawRectangle(Pen, x, y, width - 1, height - 1);
}

void Surface::FillEllipse(int x, int y, int width, int height, Colour colour)
{
	SolidBrush->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillEllipse(SolidBrush, x, y, width, height);
}

void Surface::FillEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle)
{
	SolidBrush->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillPie(SolidBrush, x, y, width, height, (Gdiplus::REAL)((startAngle / TAU * 360.0) - 90.0), (Gdiplus::REAL)(sweepAngle / TAU * 360.0));
}

void Surface::DrawEllipse(int x, int y, int width, int height, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawEllipse(Pen, x, y, width, height);
}

void Surface::DrawEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawArc(Pen, x, y, width, height, (Gdiplus::REAL)((startAngle / TAU * 360.0) - 90.0), (Gdiplus::REAL)(sweepAngle / TAU * 360.0));
}

void Surface::DrawLine(int x1, int y1, int x2, int y2, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawLine(Pen, x1, y1, x2, y2);
}

void Surface::DrawImage(int x, int y, int width, int height, Texture *texture)
{
	HDC hdc = CreateCompatibleDC(Hdc);
	SelectObject(hdc, texture->Hbm);
	//SetStretchBltMode(Hdc[CurrentFrame], COLORONCOLOR);
	StretchBlt(Hdc, x, y, width, height, hdc, 0, 0, texture->Width, texture->Height, SRCCOPY);
	DeleteObject(hdc);
}

void Surface::DrawText(int x, int y, std::string text, Font font)
{
	Typeface = new Gdiplus::Font(std::wstring(font.Typeface.begin(), font.Typeface.end()).c_str(), (Gdiplus::REAL)font.FontSize, (INT)font.Style);
	SolidBrush->SetColor(Gdiplus::Color(font.FontColour.A, font.FontColour.R, font.FontColour.G, font.FontColour.B));
	Graphics->DrawString(std::wstring(text.begin(), text.end()).c_str(), (INT)text.length(), Typeface, Gdiplus::PointF((Gdiplus::REAL)x, (Gdiplus::REAL)y), Gdiplus::StringFormat::GenericTypographic(), SolidBrush);
	delete Typeface; Typeface = 0;
}

void Surface::CopySurface(Rect destRect, Surface *other, Rect otherRect)
{
	StretchBlt(Hdc, destRect.Pos1.X, destRect.Pos1.Y, destRect.Pos2.X - destRect.Pos1.X, destRect.Pos2.Y - destRect.Pos1.Y, other->Hdc, otherRect.Pos1.X, otherRect.Pos1.Y, otherRect.Pos2.X - otherRect.Pos1.X, otherRect.Pos2.Y - otherRect.Pos1.Y, SRCCOPY);
}


