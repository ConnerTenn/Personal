
#include <WinLib.h>


typedef uint8_t u8;

Window *WindowPtr;
double Angle = 0;
const int WIDTH = 16, HEIGHT = 20;
u8 LED[WIDTH][HEIGHT][2] = { 0 }; // WIDTH, HEIGHT, Section, RGB
u8 *LEDLeader[4][2] = { {&LED[1][1][0], &LED[1][1][1] },{ &LED[WIDTH - 2][1][0], &LED[WIDTH - 2][1][1] },{ &LED[1][HEIGHT - 2][0], &LED[1][HEIGHT - 2][1] },{ &LED[WIDTH - 2][HEIGHT - 2][0], &LED[WIDTH - 2][HEIGHT - 2][1] } };
u8 const LEDLeaderPos[4][2] = { {1, 1}, {WIDTH - 2, 1}, {1, HEIGHT - 2}, {WIDTH - 2, HEIGHT - 2} };
uint16_t Delay = 0; bool DelayState = true;//true:keep changing colour
//uint8_t Count = 0;

inline float Dist(u8 x1, u8 y1, u8 x2, u8 y2)
{
	return (float)sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

inline u8 RGBDist(u8 current, u8 target)
{
	return ((255 + min(current, target)) - max(current, target)) * (current - target >= 0 ? 1 : -1);
}

inline float Interpolate(float maxV, float minV, float val)
{
	//return (float)((-1.0 / (maxV - minV)) * val + 1 + (1.0 / (maxV - minV))*minV);
	return (float)((-1.0 / (maxV + minV)) * val + 1);
}

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


void UpdateRGB()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			//vector approach other vector values
			/*float sum = 0; u8 divisor = 0;
			for (int yo = max(y - 1, 0); yo < min(y + 1, HEIGHT); yo++)
			{
				for (u8 xo = max(x - 1, 0); xo < min(x + 1, WIDTH); xo++)
				{
					//divisor++;
					//sum += LED[x + xo][y + yo][1][i];
				}
			}*/
			//LED[x][y][1][i] += (u8)(ceil(sum / (float)divisor) - LED[x][y][1][i]);
			/*if (!(x == 1 && (y == 1 || y == HEIGHT - 2) || x == WIDTH - 2 && (y == 1 || y == HEIGHT - 2)))
			{
				float maxDist = Dist(x, y, LEDLeaderPos[0][0], LEDLeaderPos[0][1]);
				float minDist = Dist(x, y, LEDLeaderPos[0][0], LEDLeaderPos[0][1]);
				for (int i = 0; i < 4; i++)
				{
					maxDist = max(maxDist, Dist(x, y, LEDLeaderPos[i][0], LEDLeaderPos[i][1]));
					minDist = min(maxDist, Dist(x, y, LEDLeaderPos[i][0], LEDLeaderPos[i][1]));
				}
				float sum = 0;
				for (int i = 0; i < 4; i++)
				{
					sum += *LEDLeader[i][0] * Interpolate(maxDist, minDist, Dist(x, y, LEDLeaderPos[i][0], LEDLeaderPos[i][1]));
				}
				LED[x][y][1] = (u8)(sum/3.0);
			}*/
			if (!(x == 1 && (y == 1 || y == HEIGHT - 2) || x == WIDTH - 2 && (y == 1 || y == HEIGHT - 2)) && y == 1)
			{
				float weight[4], sum = 0, divisor = 0;
				for (int i = 0; i < 2; i++)
				{
					weight[i] = (float)(1.0 / Dist(x, y, LEDLeaderPos[i][0], LEDLeaderPos[i][1]));
				}
				for (int i = 0; i < 2; i++)
				{
					sum += weight[i] * *LEDLeader[i][0];
					divisor += weight[i];
				}

				LED[x][y][1] = u8(sum / divisor);
				LED[x][y][0] = LED[x][y][1];
			}
				

			//approach vector values
			//if (LED[x][y][1] - LED[x][y][0] > 0) { LED[x][y][0] += 1; }
			//else if (LED[x][y][1] - LED[x][y][0] < 0) { LED[x][y][0] -= 1; }
			
			int current = LED[x][y][0], target = LED[x][y][1];
			if (target - current)
			{
				if (abs(target - current) < (255 + min(current, target)) - max(current, target))
				{
					LED[x][y][0] += (target - current > 0 ? 1 : -1);
				}
				else
				{
					LED[x][y][0] += (current - target > 0 ? 1 : -1);
				}
			}
		}
	}
	//if (Delay == 0)
	//{
		//Delay = rand() % 100;
		
	if (LED[1][1][1] - LED[1][1][0] == 0) { LED[1][1][1] = rand() % 255; }
	if (LED[WIDTH - 2][1][1] - LED[WIDTH - 2][1][0] == 0) { LED[WIDTH - 2][1][1] = rand() % 255; }
	if (LED[1][HEIGHT - 2][1] - LED[1][HEIGHT - 2][0] == 0) { LED[1][HEIGHT - 2][1] = rand() % 255; }
	if (LED[WIDTH - 2][HEIGHT - 2][1] - LED[WIDTH - 2][HEIGHT - 2][0] == 0) { LED[WIDTH - 2][HEIGHT - 2][1] = rand() % 255; }
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

				window->WindowSurface->FillRectangle({ x1, y1, x2, y2 }, Colour(ValueToR(LED[x][y][0]), ValueToG(LED[x][y][0]), ValueToB(LED[x][y][0])));
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
		}
		DrawGraphLine(window, LED[1][1][0], LED[1][1][1], 1);
		DrawGraphLine(window, LED[WIDTH - 2][1][0], LED[WIDTH - 2][1][1], 2);
		//DrawGraphLine(window, LED[1][HEIGHT - 2][0], LED[1][HEIGHT - 2][1], 3);
		//DrawGraphLine(window, LED[WIDTH - 2][HEIGHT - 2][0], LED[WIDTH - 2][HEIGHT - 2][1], 4);
		
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
	WindowPtr->CreateTimer(50, 0x01, -1);
	WindowPtr->AddMessage(MessageData({ WL_UPDATESURFACE, 0, 0 }), true);

	while (!WindowPtr->State.Quit)
	{
		WindowPtr->PreMsg();
		Window::GetMsg();
		WindowPtr->UpdateMsg();
	}

	delete WindowPtr; WindowPtr = 0;
}
