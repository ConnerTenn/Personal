
#include <WinLib.h>


typedef uint8_t u8;

Window *WindowPtr;
const int WIDTH = 16, HEIGHT = 20;
u8 LED[WIDTH][HEIGHT][3] = { 0 }; // WIDTH, HEIGHT, RGB
u8 *LEDLeader[4][3] = { 0 };// = { {&LED[1][1][0], &LED[1][1][1] },{ &LED[WIDTH - 2][1][0], &LED[WIDTH - 2][1][1] },{ &LED[1][HEIGHT - 2][0], &LED[1][HEIGHT - 2][1] },{ &LED[WIDTH - 2][HEIGHT - 2][0], &LED[WIDTH - 2][HEIGHT - 2][1] } };
u8 const LEDLeaderPos[4][2] = { { 0, 0 },{ WIDTH - 1, 0 },{ 0, HEIGHT - 1 },{ WIDTH - 1, HEIGHT - 1 } };
u8 LEDLeaderTarget[4][3] = { 0 };
//uint8_t Count = 0;

inline float Dist(u8 x1, u8 y1, u8 x2, u8 y2)
{
	return (float)sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

//dist between values, cycling around 255
inline u8 RGBDist(u8 current, u8 target)
{
	return ((255 + min(current, target)) - max(current, target)) * (current - target >= 0 ? 1 : -1);
}

inline u8 ValueToR(u8 val)
{
	return (val <= 85 ? 255 - val * 3 : 0) + //First Decrease
		(val > 170 ? val * 3 : 0); //Third Increase
	//return (float(val) / 255.0 <= (1.0 / 3.0) ? u8(255 - val / (1.0 / 3.0)) : 0) + //First Decrease
	//	(float(val) / 255.0 > (2.0 / 3.0) && float(val) / 255.0 <= 1 ? u8(val / (1.0 / 3.0)) : 0); //Third Increase
}
inline u8 ValueToG(u8 val)
{
	return (val <= 85 ? val * 3 : 0) +//First Increase
		(val >= 85 && val < 170 ? 255 - val * 3 : 0);//Second Increase
	//return (float(val) / 255.0 <= (1.0 / 3.0) ? u8(val / (1.0 / 3.0)) : 0) +//First Increase
	//	(float(val) / 255.0 >= (1.0 / 3.0)  && float(val) / 255.0 < (2.0 / 3.0) ? u8(255 - val / (1.0 / 3.0)) : 0);//Second Increase
}
inline u8 ValueToB(u8 val)
{
	return (val > 85 && val <= 170 ? val * 3 : 0) +//Second Increase
		(val >= 170 ? 255 - val * 3 : 0);//Third Decrease
	//return (float(val) / 255.0 > (1.0 / 3.0) && float(val) / 255.0 <= (2.0 / 3.0) ? u8(val / (1.0 / 3.0)) : 0) +//Second Increase
	//	(float(val) / 255.0 >= (2.0 / 3.0) && float(val) / 255.0 <= 1 ? u8(255 - val / (1.0 / 3.0)) : 0);//Third Decrease
}


void UpdateRGB()
{
	for (u8 c = 0; c < 3; c++)
	{
		for (u8 y = 0; y < HEIGHT; y++)
		{
			for (u8 x = 0; x < WIDTH; x++)
			{			
				//don't calculate for primary Leds
				if (!(x == 0 && (y == 0 || y == HEIGHT - 1) || x == WIDTH - 1 && (y == 0 || y == HEIGHT - 1)))
				{
					float sum = 0, divisor = 0;
					for (u8 j = 0; j < 4; j++)
					{
						float weight = (float)(1.0 / Dist(x, y, LEDLeaderPos[j][0], LEDLeaderPos[j][1]));
						//calculate sum and divisor for interpolaation calculation
						sum += weight * *LEDLeader[j][c];
						divisor += weight;
					}

					//interpolation
					LED[x][y][c] = u8(sum / divisor);
				}
			}
		}
		for (int j = 0; j < 4; j++)
		{
			if (LEDLeaderTarget[j][c] - *LEDLeader[j][c] > 1) { (*LEDLeader[j][c]) += 2; }
			else if (LEDLeaderTarget[j][c] - *LEDLeader[j][c] < -1) { (*LEDLeader[j][c]) -= 2; }
		}
	}
	
	//Update each Primary LED
	for (int j = 0; j < 4; j++)
	{
		//Target Reached; set new targets
		if (abs(*LEDLeader[j][0] - LEDLeaderTarget[j][0]) <= 1 &&
			abs(*LEDLeader[j][1] - LEDLeaderTarget[j][1]) <= 1 &&
			abs(*LEDLeader[j][2] - LEDLeaderTarget[j][2]) <= 1)
		{
			u8 val = rand() % 255;
			LEDLeaderTarget[j][0] = ValueToR(val);
			LEDLeaderTarget[j][1] = ValueToG(val);
			LEDLeaderTarget[j][2] = ValueToB(val);
		}
	}
	//}
	//Delay--;
}

void DrawGraphLine(Window *window, int current, int target, int val)
{
	window->WindowSurface->FillRectangle({ 400 + current, 0, 401 + current, 280 }, Colour(255, 255, 255));
	window->WindowSurface->FillRectangle({ 400 + target, 0, 401 + target, 260 }, Colour(255, 255, 255));
	window->WindowSurface->DrawLine({ 400 + current, 280 }, { 400 + target, 260 }, Colour(255, 255, 255));
	window->WindowSurface->DrawText({ 400 + current, 275 }, std::to_string(val), Font(Colour(255, 255, 255)));
}

void DrawLEDTargets(Window *window)
{
	for (int j = 0; j < 4; j++)
	{
		for (int c = 0; c < 3; c++)
		{
			for (int y = 0; y < 255; y++)
			{
				window->WindowSurface->FillRectangle({ 100 * j + 400 + 30 * c, 300 + 255 - y, 100 * j + 420 + 30 * c, 301 + 255 - y }, Colour(c == 0 ? y : 0, c == 1 ? y : 0, c == 2 ? y : 0));
			}
		}
	}

	for (int j = 0; j < 4; j++)
	{
		for (int c = 0; c < 3; c++)
		{
			window->WindowSurface->DrawLine({ 100 * j + 400 + 30 * c, 300 + 255 - *LEDLeader[j][c] }, { 100 * j + 420 + 30 * c, 300 + 255 - *LEDLeader[j][c] }, Colour(255, 255, 255));
			window->WindowSurface->DrawText({ 100 * j + 400 + 30 * c, 300 + 255 - *LEDLeader[j][c] }, std::to_string(j), Font(Colour(255, 255, 255)));
			window->WindowSurface->DrawLine({ 100 * j + 400 + 30 * c, 300 + 255 - LEDLeaderTarget[j][c] }, { 100 * j + 420 + 30 * c, 300 + 255 - LEDLeaderTarget[j][c] }, Colour(255, 255, 255));
			window->WindowSurface->DrawText({ 100 * j + 400 + 30 * c, 300 + 255 - LEDLeaderTarget[j][c] }, std::to_string(j) + "*", Font(Colour(255, 255, 255)));
		}
	}
}

//WindowPtr->AddMessage(MessageData({ WL_UPDATESURFACE, 0, 0 }), true);
void GraphicCallback(Window *window, MessageData message, void *data)
{
	if (message == WL_UPDATESURFACE)
	{
		window->WindowSurface->Clear();
		//window->WindowSurface->DrawRectangle({ (int)(100.0*sin(Angle)) + 110, (int)(100.0*-cos(Angle)) + 110, (int)(100.0*sin(Angle)) + 120, (int)(100.0*-cos(Angle)) + 120 }, Colour(255, 255, 255));
		UpdateRGB();
		for (int y = 0; y < HEIGHT; y++)
		{
			for (int x = 0; x < WIDTH; x++)
			{
				int x1 = x * (400 / WIDTH);
				int y1 = y * (500 / HEIGHT); //500 - y * (500 / HEIGHT) - (500 / HEIGHT);
				int x2 = x1 + (400 / WIDTH); //x * (400 / WIDTH) + (400 / WIDTH);
				int y2 = y1 + (500 / HEIGHT); //(500 - y * (500 / HEIGHT));

				window->WindowSurface->FillRectangle({ x1, y1, x2, y2 }, Colour(LED[x][y][0], LED[x][y][1], LED[x][y][2]));
			}
		}
		/*for (int y = 0; y < HEIGHT; y++)
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
		}*/
		for (uint8_t i = 0; i < 255; i++)
		{
			window->WindowSurface->FillRectangle({ 400 + i, 255 - ValueToR(i), 401 + i, 256 - ValueToR(i) }, Colour(255, 0, 0));
			window->WindowSurface->FillRectangle({ 400 + i, 255 - ValueToG(i)+1, 401 + i, 256 - ValueToG(i)+1 }, Colour(0, 255, 0));
			window->WindowSurface->FillRectangle({ 400 + i, 255 - ValueToB(i)+2, 401 + i, 256 - ValueToB(i)+2 }, Colour(0, 0, 255));
			window->WindowSurface->FillRectangle({ 400 + i, 260, 401 + i, 280}, Colour(ValueToR(i), ValueToG(i), ValueToB(i)));
		}
		//DrawGraphLine(window, LED[1][1][0], LED[1][1][1], 1);
		//DrawGraphLine(window, LED[WIDTH - 2][1][0], LED[WIDTH - 2][1][1], 2);
		//DrawGraphLine(window, LED[1][HEIGHT - 2][0], LED[1][HEIGHT - 2][1], 3);
		//DrawGraphLine(window, LED[WIDTH - 2][HEIGHT - 2][0], LED[WIDTH - 2][HEIGHT - 2][1], 4);
		DrawLEDTargets(window);
		
		WindowPtr->Draw();
	}
	else if (message == WM_TIMER && message.WParam() == 1)
	{
		WindowPtr->AddMessage(MessageData({ WL_UPDATESURFACE, 0, 0 }), true);
	}
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	for (int j = 0; j < 4; j++)
	{
		for (int c = 0; c < 3; c++)
		{
			LEDLeader[j][c] = &(LED[LEDLeaderPos[j][0]][LEDLeaderPos[j][1]][c]);
		}
	}

	WindowInfo windowInfo;

	windowInfo.Name = "LEDArrayGlow_000";
	windowInfo.Dimensions = { 800,600 };
	windowInfo.ClearColour = Colour(0, 0, 0);
	windowInfo.HInstance = hInstance;
	windowInfo.ICmdShow = iCmdShow;
	windowInfo.Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;//WS_POPUP;//
	windowInfo.Callback = GraphicCallback;
	windowInfo.CallbackPtr = 0;
	WindowPtr = new Window(&windowInfo);

	WindowPtr->Create();
	WindowPtr->CreateTimer(5, 0x01, -1);
	WindowPtr->AddMessage(MessageData({ WL_UPDATESURFACE, 0, 0 }), true);

	while (!WindowPtr->State.Quit)
	{
		WindowPtr->PreMsg();
		Window::GetMsg();
		WindowPtr->UpdateMsg();
	}

	delete WindowPtr; WindowPtr = 0;
}
