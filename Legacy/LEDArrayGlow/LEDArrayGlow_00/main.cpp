
#include <WinLib.h>


typedef uint8_t u8;

Window *WindowPtr;
double Angle = 0;
const int WIDTH = 8, HEIGHT = 10;
u8 LED[WIDTH][HEIGHT][2][3] = { 0 }; // WIDTH, HEIGHT, Section, RGB
u8 LEDENA[WIDTH][HEIGHT] = { true };
uint16_t Delay = 0; bool DelayState = true;//true:keep changing colour
//uint8_t Count = 0;

inline float Transform(float val, int offset)
{
	return (1.0f - (float)cos(TAU * val - offset * TAU / 6.0f)) / 2.0f;
}

inline u8 ValueToR(u8 val)
{
	return (float(val) / 255.0 <= (1.0 / 3.0) ? u8(255 - val / (1.0 / 3.0)) : 0) + //First Decrease
		(float(val) / 255.0 > (2.0 / 3.0) && float(val) / 255.0 <= 1 ? u8(val / (1.0 / 3.0)) : 0); //Third Increase
}
inline u8 ValueToG(u8 val)
{
	return (float(val) / 255.0 <= (1.0 / 3.0) ? u8(val / (1.0 / 3.0)) : 0) +//First Increase
		(float(val) / 255.0 >= (1.0 / 3.0)  && float(val) / 255.0 < (2.0 / 3.0) ? u8(255 - val / (1.0 / 3.0)) : 0);//Second Increase
}
inline u8 ValueToB(u8 val)
{
	return (float(val) / 255.0 > (1.0 / 3.0) && float(val) / 255.0 <= (2.0 / 3.0) ? u8(val / (1.0 / 3.0)) : 0) +//Second Increase
		(float(val) / 255.0 >= (2.0 / 3.0) && float(val) / 255.0 <= 1 ? u8(255 - val / (1.0 / 3.0)) : 0);//Third Decrease
}

inline u8 GenerateNum(u8 i)
{
	switch (i)
	{
	case 0:
		return ValueToR(rand() % 255);
	case 1:
		return ValueToG(rand() % 255);
	case 2:
		return ValueToB(rand() % 255);
	}
}

void UpdateRGB()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			for (int i = 0; i < 3; i++)
			{
				//vector approach other vector values
				if (LEDENA[x][y])
				{
					float sum = 0; u8 divisor = 0;
					for (int yo = max(y - 1, 0); yo < min(y + 1, HEIGHT); yo++)
					{
						for (u8 xo = max(x - 1, 0); xo < min(x + 1, WIDTH); xo++)
						{
							divisor++;
							sum += LED[x + xo][y + yo][1][i];
						}
					}
					LED[x][y][1][i] += (u8)(ceil(sum / (float)divisor) - LED[x][y][1][i]);
				}

				//approach vector values
				if (LED[x][y][1][i] - LED[x][y][0][i] > 1) { LED[x][y][0][i] += 1; }
				else if (LED[x][y][1][i] - LED[x][y][0][i] < -1) { LED[x][y][0][i] -= 1; }
			}

			//LED[x][y][1][0] = ValueToR(Count); LED[x][y][0][0] = LED[x][y][1][0];
			//LED[x][y][1][1] = ValueToG(Count); LED[x][y][0][1] = LED[x][y][1][1];
			//LED[x][y][1][2] = ValueToB(Count); LED[x][y][0][2] = LED[x][y][1][2];
		}
	}
	if (Delay == 0)
	{
		Delay = rand() % 100;
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				LEDENA[x][y] = true;
			}
		}
		for (u8 i = 0; i < 4; i++)
		{
			u8 x = rand() % WIDTH, y = rand() % HEIGHT, val = rand() % 256;
			LED[x][y][1][0] = ValueToR(val);
			LED[x][y][1][1] = ValueToG(val);
			LED[x][y][1][2] = ValueToB(val);
			LEDENA[x][y] = false;
		}
	}
	Delay--;
}

//WindowPtr->AddMessage(MessageData({ WL_UPDATESURFACE, 0, 0 }), true);
void GraphicCallback(Window *window, MessageData message, void *data)
{
	if (message == WL_UPDATESURFACE)
	{
		window->WindowSurface->Clear();
		window->WindowSurface->DrawRectangle({ (int)(100.0*sin(Angle)) + 110, (int)(100.0*-cos(Angle)) + 110, (int)(100.0*sin(Angle)) + 120, (int)(100.0*-cos(Angle)) + 120 }, Colour(255, 255, 255));
		UpdateRGB();
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				int x1 = x * (400 / WIDTH);
				int y1 = 500 - y * (500 / HEIGHT) - (500 / HEIGHT);
				int x2 = x * (400 / WIDTH) + (400 / WIDTH);
				int y2 = (500 - y * (500 / HEIGHT));

				window->WindowSurface->FillRectangle({ x1, y1, x2, y2 }, Colour(LED[x][y][0][0], LED[x][y][0][1], LED[x][y][0][2]));
			}
		}
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				int x1 = x * (400 / WIDTH);
				int y1 = 500 - y * (500 / HEIGHT) - (500 / HEIGHT);
				int x2 = x * (400 / WIDTH) + (400 / WIDTH);
				int y2 = (500 - y * (500 / HEIGHT));

				if (x == WIDTH / 3 - 1 && (y == HEIGHT / 3 - 1 || y == HEIGHT - HEIGHT / 3) || x ==  WIDTH - WIDTH / 3 && (y == HEIGHT / 3 - 1 || y == HEIGHT - HEIGHT / 3))
				{
					window->WindowSurface->DrawRectangle({ x1, y1, x2, y2 }, Colour(0, 0, 0), 4);
				}
			}
		}
		for (uint8_t i = 0; i < 255; i++)
		{
			window->WindowSurface->FillRectangle({ 400 + i, 255 - ValueToR(i), 401 + i, 256 - ValueToR(i) }, Colour(255, 0, 0));
			window->WindowSurface->FillRectangle({ 400 + i, 255 - ValueToG(i)+1, 401 + i, 256 - ValueToG(i)+1 }, Colour(0, 255, 0));
			window->WindowSurface->FillRectangle({ 400 + i, 255 - ValueToB(i)+2, 401 + i, 256 - ValueToB(i)+2 }, Colour(0, 0, 255));
		}
		//window->WindowSurface->FillRectangle({ 400 + Count, 0, 401 + Count, 256 }, Colour(255, 255, 255));
		
		WindowPtr->Draw();
	}
	else if (message == WM_TIMER && message.WParam() == 1)
	{
		Angle = (Angle > TAU ? 0 : Angle + 0.3);
		WindowPtr->AddMessage(MessageData({ WL_UPDATESURFACE, 0, 0 }), true);
	}
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	WindowInfo windowInfo;

	windowInfo.Name = "LEDArrayGlow_000";
	windowInfo.Dimensions = { 800,500 };
	windowInfo.ClearColour = Colour(0, 0, 0);
	windowInfo.HInstance = hInstance;
	windowInfo.ICmdShow = iCmdShow;
	windowInfo.Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;//WS_POPUP;//
	windowInfo.Callback = GraphicCallback;
	windowInfo.CallbackPtr = 0;
	WindowPtr = new Window(&windowInfo);

	WindowPtr->Create();
	WindowPtr->CreateTimer(100, 0x01, -1);
	WindowPtr->AddMessage(MessageData({ WL_UPDATESURFACE, 0, 0 }), true);

	while (!WindowPtr->State.Quit)
	{
		WindowPtr->PreMsg();
		Window::GetMsg();
		WindowPtr->UpdateMsg();
	}

	delete WindowPtr; WindowPtr = 0;
}
