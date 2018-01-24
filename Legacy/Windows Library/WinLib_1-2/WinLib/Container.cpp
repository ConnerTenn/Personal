
#include "Container.h"

Container::Container(int x, int y, int width, int height, Container *parent, Window *srcWindow)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
	Parent = parent;
	SrcWindow = srcWindow;

	Hdc = CreateCompatibleDC(SrcWindow->Ps.hdc);
	Hbm = CreateCompatibleBitmap(SrcWindow->Ps.hdc, Width, Height);

	SelectObject(Hdc, Hbm);
	Graphics = new Gdiplus::Graphics(Hdc);

	SolidBrush = new Gdiplus::SolidBrush(Gdiplus::Color(0, 0, 0, 0));
	Pen = new Gdiplus::Pen(Gdiplus::Color(0, 0, 0, 0));

	SetBkMode(Hdc, TRANSPARENT);

	UpdateTransformations();
}

Container::~Container()
{
	for (Container *container : ContainerList)
	{
		delete container;
	}

	Parent = 0;
	SrcWindow = 0;
	DeleteObject(Hdc);
	DeleteObject(Hbm);
	DeleteObject(Hfnt);
}

Container *Container::CreateContainer(int x, int y, int width, int height)
{
	Container *container = new Container(x, y, width, height, this, SrcWindow);
	ContainerList.push_back(container);
	return container;
}

void Container::UpdateTransformations()
{
	AbsX = X;
	AbsY = Y;
	if (Parent)
	{
		ScaleX = Parent->ScaleX;
		ScaleY = Parent->ScaleY;

		AbsX = (int)(AbsX * ScaleX);
		AbsY = (int)(AbsY * ScaleY);

		AbsX += Parent->AbsX;
		AbsY += Parent->AbsY;		
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
		StretchBlt(SrcWindow->HdcMem, AbsX, AbsY, (int)(ScaleX * Width), (int)(ScaleY * Height), Hdc, 0, 0, Width, Height, SRCCOPY);
	}
	for (Container *container : ContainerList)
	{
		container->Render();
	}
}



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

	DeleteObject(Hbm);
	Hbm = CreateCompatibleBitmap(SrcWindow->Ps.hdc, Width, Height);
	SelectObject(Hdc, Hbm);

	delete Graphics;
	Graphics = new Gdiplus::Graphics(Hdc);
}



void Container::FillRectangle(int x, int y, int width, int height, Colour colour)
{
	SolidBrush->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillRectangle(SolidBrush, x, y, width, height);
}

void Container::DrawRectangle(int x, int y, int width, int height, Colour colour, float size)
{
	Pen->SetColor(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B)); Pen->SetWidth(size);
	Graphics->DrawRectangle(Pen, x, y, width, height);
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

void Container::DrawImage(int x, int y, int width, int height,  Texture3 *texture)
{
	//Graphics->DrawImage(texture->Image, x, y, width, height);
	
	/*//StretchBlt(Hdc, AbsX, AbsY, (int)(ScaleX * Width), (int)(ScaleY * Height), texture->Image, 0, 0, Width, Height, SRCCOPY);

	//Gdiplus::Bitmap* img;
	//HBITMAP temp;
	//Gdiplus::Color color;
	//img->GetHBITMAP(color, &temp);
	//int width = sourceImg->GetWidth();
	//int height = sourceImg->GetHeight();
	//Gdiplus::Bitmap* Result;
	//result = new Bitmap(width, height, PixelFormat32bppRGB);

	//Gdiplus::Bitmap* bitmap = dynamic_cast<Gdiplus::Bitmap*>(texture->Image);
	//*bitmap = *texture->Image;
	//HBITMAP map = dynamic_cast<HBITMAP>(bitmap);
	//bitmap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &map);
	//HBITMAP map = (HBITMAP)LoadImage(NULL, "Falvie.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//std::string filename = "Shiuk.bmp";
	//Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(std::wstring(std::wstring(filename.begin(), filename.end()).c_str()).c_str());
	HBITMAP map = LoadBitmap(NULL, "Falvie.bmp");
	//HDC dc = CreateCompatibleDC(Hdc);
	//SelectObject(dc, map);
	
	BITMAP bmp = {};
	//GetObject(map, sizeof(bmp), &bmp);
	//StretchBlt(Hdc, x, y, width, height, dc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	// prepare BITMAPINFO
	BITMAPINFO bminfo = {};
	bminfo.bmiHeader.biSize = sizeof(BITMAPINFO);
	bminfo.bmiHeader.biWidth = bmp.bmWidth;
	bminfo.bmiHeader.biHeight = bmp.bmHeight;
	bminfo.bmiHeader.biBitCount = bmp.bmBitsPixel;
	bminfo.bmiHeader.biCompression = BI_RGB;
	bminfo.bmiHeader.biPlanes = bmp.bmPlanes;
	bminfo.bmiHeader.biSizeImage = bmp.bmWidthBytes*bmp.bmHeight * 4; // 4 stands for 32bpp
	
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	//bmi.bmiHeader.biWidth = texture->Image->GetWidth();
	//bmi.bmiHeader.biHeight = -texture->Image->GetHeight();
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 0;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = 0;// sizeof(texture->Image);

	BITMAP mp = LoadBitmap(NULL, "Falvie.bmp");;
	Gdiplus::Graphics *grp = Gdiplus::Graphics::FromImage(&mp);
	grp->DrawImage(texture->Image, 0, 0, 100, 100);

	BITMAPINFO minfo = {};
	bminfo.bmiHeader.biSize = sizeof(BITMAPINFO);
	bminfo.bmiHeader.biWidth = mp.bmWidth;
	bminfo.bmiHeader.biHeight = mp.bmHeight;
	bminfo.bmiHeader.biBitCount = mp.bmBitsPixel;
	bminfo.bmiHeader.biCompression = BI_RGB;
	bminfo.bmiHeader.biPlanes = mp.bmPlanes;
	bminfo.bmiHeader.biSizeImage = mp.bmWidthBytes*bmp.bmHeight * 4; // 4 stands for 32bpp

	StretchDIBits(Hdc, x, y, width, height, 0, 0, bmp.bmWidth, bmp.bmHeight, mp.bmBits, &minfo, 0, SRCCOPY);*/

	//HBITMAP hbmScreen = (HBITMAP)LoadImage(NULL, "Falvie.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//HBITMAP hbmScreen = LoadBitmap(NULL, "Falvie.bmp");
	/*HBITMAP hbmScreen = CreateCompatibleBitmap(Hdc, 0, 0);
	BITMAP bmpScreen;

	GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

	BITMAPINFOHEADER bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bmpScreen.bmWidth;
	bi.biHeight = bmpScreen.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

	// Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
	// call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
	// have greater overhead than HeapAlloc.
	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	char *lpbitmap = (char *)GlobalLock(hDIB);

	// Gets the "bits" from the bitmap and copies them into a buffer 
	// which is pointed to by lpbitmap.
	GetDIBits(Hdc, hbmScreen, 0, (UINT)bmpScreen.bmHeight, lpbitmap, (BITMAPINFO *)&bi, DIB_RGB_COLORS);
	//StretchDIBits(Hdc, x, y, width, height, 0, 0, bmpScreen.bmWidth, bmpScreen.bmHeight, bmpScreen.bmBits, (BITMAPINFO *)&bi, 0, SRCCOPY);*/
	
	//HDC hdc;
	//HBITMAP hbm;

	//hdc = CreateCompatibleDC(Hdc);
	//hbm = CreateCompatibleBitmap(Hdc, width, height);

	//SelectObject(hdc, hbm);
	//Gdiplus::Graphics *graphics = new Gdiplus::Graphics(hdc);

	//graphics->DrawImage(texture->Image, 0, 0, width, height);

	//Graphics->SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
	//Graphics->DrawImage(texture->Image, x, y, width, height);
	//HBITMAP hbm = (HBITMAP)LoadImage(NULL, "Falvie.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//BITMAP bmp;

	HDC hdc = CreateCompatibleDC(Hdc);
	SelectObject(hdc, texture->Hbm);

	//GetObject(hbm, sizeof(BITMAP), &bmp);
	SetStretchBltMode(Hdc, COLORONCOLOR);
	//StretchBlt(Hdc, x, y, width, height, texture->Hdc, 0, 0, texture->Width, texture->Height, SRCCOPY);
	//StretchBlt(Hdc, x, y, width, height, hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	StretchBlt(Hdc, x, y, width, height, hdc, 0, 0, texture->Width, texture->Height, SRCCOPY);
	//StretchBlt(Hdc, x, y, width, height, texture->Hdc, 0, 0, texture->Width, texture->Height, SRCCOPY);
	DeleteObject(hdc);
}

void Container::DrawText(int x, int y, std::string text, Font font)
{
	Hfnt = CreateFont(font.FontSize, font.FontSize / font.HeightWidthRatio, 0, 0, (font.Style & 0b0001) == 0b0001 ? FW_BOLD : FW_NORMAL, font.Style & 0b0010, font.Style & 0b0100, font.Style & 0b1000, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, TEXT(font.Typeface.c_str()));
	SelectObject(Hdc, Hfnt);
	
	SetTextColor(Hdc, RGB(0, 255, 0));
	
	RECT rc = { x, y, (LONG)Width, (LONG)Height };
	DrawTextA(Hdc, text.c_str(), -1, &rc, DT_LEFT);

	DeleteObject(Hfnt);
	SelectObject(Hdc, Hdc);
}

