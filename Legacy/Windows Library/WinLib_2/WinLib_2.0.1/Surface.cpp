
#include "Surface.h"

Int2 MeasureString(Surface *surface, std::string string, Font font)
{
	std::replace(string.begin(), string.end(), ' ', '-');
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
	//Graphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
	//Graphics->SetTextRenderingHint(Gdiplus::TextRenderingHintClearTypeGridFit);
	Graphics->SetTextRenderingHint(Gdiplus::TextRenderingHintSystemDefault);
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

Rect Surface::GetRect()
{
	return{ 0,0, Dimensions.X, Dimensions.Y };
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

void Surface::FillRectangle(Int2 pos1, Int2 pos2, Colour colour)
{
	FillRectangle(pos1.X, pos1.Y, pos2.X - pos1.X, pos2.Y - pos1.Y, colour);
}

void Surface::FillRectangle(Rect rect, Colour colour)
{
	FillRectangle(rect.Pos1.X, rect.Pos1.Y, rect.Pos2.X - rect.Pos1.X, rect.Pos2.Y - rect.Pos1.Y, colour);
}

void Surface::FillRectangles(std::vector<Rect> rects, Colour colour)
{
	SolidBrush->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Gdiplus::Rect *gdiRects = new Gdiplus::Rect[rects.size()];
	for (int i = 0; i < rects.size(); i++) { gdiRects[i] = { rects[i].Pos1.X, rects[i].Pos1.Y, rects[i].Pos2.X - rects[i].Pos1.X, rects[i].Pos2.Y - rects[i].Pos1.Y }; }
	Graphics->FillRectangles(SolidBrush, gdiRects, (int)rects.size());
	delete[] gdiRects;
}

void Surface::DrawRectangle(int x, int y, int width, int height, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawRectangle(Pen, x, y, width - 1, height - 1);
}

void Surface::DrawRectangle(Int2 pos1, Int2 pos2, Colour colour, float size)
{
	DrawRectangle(pos1.X, pos1.Y, pos2.X - pos1.X, pos2.Y - pos1.Y, colour, size);
}

void Surface::DrawRectangle(Rect rect, Colour colour, float size)
{
	DrawRectangle(rect.Pos1.X, rect.Pos1.Y, rect.Pos2.X - rect.Pos1.X, rect.Pos2.Y - rect.Pos1.Y, colour, size);
}

void Surface::DrawRectangles(std::vector<Rect> rects, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Gdiplus::Rect *gdiRects = new Gdiplus::Rect[rects.size()];
	for (int i = 0; i < rects.size(); i++) { gdiRects[i] = { rects[i].Pos1.X, rects[i].Pos1.Y, rects[i].Pos2.X - rects[i].Pos1.X, rects[i].Pos2.Y - rects[i].Pos1.Y }; }
	Graphics->DrawRectangles(Pen, gdiRects, (int)rects.size());
	delete[] gdiRects;
}

void Surface::FillEllipse(int x, int y, int width, int height, Colour colour)
{
	SolidBrush->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillEllipse(SolidBrush, x, y, width, height);
}

void Surface::FillEllipse(Int2 pos1, Int2 pos2, Colour colour)
{
	FillEllipse(pos1.X, pos1.Y, pos2.X - pos1.X, pos2.Y - pos1.Y, colour);
}

void Surface::FillEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle)
{
	SolidBrush->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillPie(SolidBrush, x, y, width, height, (Gdiplus::REAL)((startAngle / TAU * 360.0) - 90.0), (Gdiplus::REAL)(sweepAngle / TAU * 360.0));
}

void Surface::FillEllipse(Int2 pos1, Int2 pos2, Colour colour, double startAngle, double sweepAngle)
{
	FillEllipse(pos1.X, pos1.Y, pos2.X - pos1.X, pos2.Y - pos1.Y, colour, startAngle, sweepAngle);
}

void Surface::DrawEllipse(int x, int y, int width, int height, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawEllipse(Pen, x, y, width, height);
}

void Surface::DrawEllipse(Int2 pos1, Int2 pos2, Colour colour, float size)
{
	DrawEllipse(pos1.X, pos1.Y, pos2.X - pos1.X, pos2.Y - pos1.Y, colour, size);
}

void Surface::DrawEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawArc(Pen, x, y, width, height, (Gdiplus::REAL)((startAngle / TAU * 360.0) - 90.0), (Gdiplus::REAL)(sweepAngle / TAU * 360.0));
}

void Surface::DrawEllipse(Int2 pos1, Int2 pos2, Colour colour, double startAngle, double sweepAngle, float size)
{
	DrawEllipse(pos1.X, pos1.Y, pos2.X - pos1.X, pos2.Y - pos1.Y, colour, startAngle, sweepAngle, size);
}

void Surface::DrawLine(int x1, int y1, int x2, int y2, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawLine(Pen, x1, y1, x2, y2);
}

void Surface::DrawLine(Int2 pos1, Int2 pos2, Colour colour, float size)
{
	DrawLine(pos1.X, pos1.Y, pos2.X, pos2.Y, colour, size);
}

void Surface::DrawLines(std::vector<Int2> &points, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Gdiplus::Point *gdiPoints = new Gdiplus::Point[points.size()];
	for (int i = 0; i < points.size(); i++) { gdiPoints[i] = { points[i].X, points[i].Y }; }
	Graphics->DrawLines(Pen, gdiPoints, (INT)points.size());
	delete[] gdiPoints;
}

void Surface::DrawPolygon(std::vector<Int2> &points, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Gdiplus::Point *gdiPoints = new Gdiplus::Point[points.size()];
	for (int i = 0; i < points.size(); i++) { gdiPoints[i] = { points[i].X, points[i].Y }; }
	Graphics->DrawPolygon(Pen, gdiPoints, (INT)points.size());
	delete[] gdiPoints;
}

void Surface::DrawImage(int x, int y, int width, int height, Texture *texture)
{
	HDC hdc = CreateCompatibleDC(Hdc);
	SelectObject(hdc, texture->Hbm);
	//SetStretchBltMode(Hdc[CurrentFrame], COLORONCOLOR);
	StretchBlt(Hdc, x, y, width, height, hdc, 0, 0, texture->Width, texture->Height, SRCCOPY);
	DeleteObject(hdc);
}

void Surface::DrawImage(Int2 pos1, Int2 pos2, Texture *texture)
{
	DrawImage(pos1.X, pos1.Y, pos2.X - pos1.X, pos2.X - pos1.X, texture);
}

void Surface::DrawText(int x, int y, std::string text, Font font)
{
	Typeface = new Gdiplus::Font(std::wstring(font.Typeface.begin(), font.Typeface.end()).c_str(), (Gdiplus::REAL)font.FontSize, (INT)font.Style);
	SolidBrush->SetColor(Gdiplus::Color(font.FontColour.A, font.FontColour.R, font.FontColour.G, font.FontColour.B));
	Graphics->DrawString(std::wstring(text.begin(), text.end()).c_str(), (INT)text.length(), Typeface, Gdiplus::PointF((Gdiplus::REAL)x, (Gdiplus::REAL)y), Gdiplus::StringFormat::GenericTypographic(), SolidBrush);
	delete Typeface; Typeface = 0;
}

void Surface::DrawText(Int2 pos, std::string text, Font font)
{
	DrawText(pos.X, pos.Y, text, font);
}

void Surface::CopySurface(Rect destRect, Surface *src, Rect srcRect)
{
	StretchBlt(Hdc, destRect.Pos1.X, destRect.Pos1.Y, destRect.Pos2.X - destRect.Pos1.X, destRect.Pos2.Y - destRect.Pos1.Y, src->Hdc, srcRect.Pos1.X, srcRect.Pos1.Y, srcRect.Pos2.X - srcRect.Pos1.X, srcRect.Pos2.Y - srcRect.Pos1.Y, SRCCOPY);
}


void Surface::SetClip(Int2 pos1, Int2 pos2)
{
	Graphics->SetClip(Gdiplus::Rect(pos1.X, pos1.Y, pos2.X - pos1.X, pos2.Y - pos1.Y), Gdiplus::CombineModeReplace);
}

void Surface::ResetClip()
{
	Graphics->ResetClip();
}


void Surface::DrawPath(std::vector<Int2> &points, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Gdiplus::GraphicsPath path;
	for (int i = 0; i < points.size() - 1; i += 2) { path.StartFigure(); path.AddLine((Gdiplus::REAL)points[i].X, (Gdiplus::REAL)points[i].Y, (Gdiplus::REAL)points[i + 1].X, (Gdiplus::REAL)points[i + 1].Y); }
	Graphics->DrawPath(Pen, &path);
}

void Surface::StartFigure()
{
	Path.StartFigure();
}

void Surface::ClearPath()
{
	Path.Reset();
}

void Surface::AddLine(Int2 pos1, Int2 pos2)
{
	Path.AddLine((Gdiplus::REAL)pos1.X, (Gdiplus::REAL)pos1.Y, (Gdiplus::REAL)pos2.X, (Gdiplus::REAL)pos2.Y);
}

void Surface::AddEllipse(Int2 pos, Int2 dimensions)
{
	Path.AddEllipse(Gdiplus::REAL(pos.X), Gdiplus::REAL(pos.Y), Gdiplus::REAL(dimensions.X), Gdiplus::REAL(dimensions.Y));
}

void Surface::AddString(Int2 pos, std::string text, Font font)
{
	Gdiplus::FontFamily *typeface = new Gdiplus::FontFamily(std::wstring(font.Typeface.begin(), font.Typeface.end()).c_str());
	Path.AddString(std::wstring(text.begin(), text.end()).c_str(), (INT)text.length(), typeface, (INT)font.Style, (Gdiplus::REAL)font.FontSize, Gdiplus::RectF((Gdiplus::REAL)pos.X, (Gdiplus::REAL)pos.Y, (Gdiplus::REAL)Dimensions.X, (Gdiplus::REAL)Dimensions.Y), Gdiplus::StringFormat::GenericTypographic());
}

void Surface::DrawPath(Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawPath(Pen, &Path);
}


