
#include <WinLib.h>


typedef uint8_t u8;

Window *WindowPtr;
const int LWIDTH = 5, LHEIGHT = 5, LMUL = 4, WIDTH = (LWIDTH - 1) * LMUL + 1, HEIGHT = (LHEIGHT - 1) * LMUL + 1;
u8 LEADER[LWIDTH][LHEIGHT][3] = { 0 }; // LWIDTH, LHEIGHT, Colour, Colour target
u8 LED[WIDTH][HEIGHT][2] = { 0 }; //WIDTH, HEIGHT, Colour
u8 DrawMode = 0;
//uint8_t Count = 0;



uint16_t Rand()
{
	static uint16_t lfsr = 0xACE1u;
	static uint16_t bit = 0;

	bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
	return lfsr = (lfsr >> 1) | (bit << 15);
}

inline float Dist(u8 x1, u8 y1, u8 x2, u8 y2)
{
	return (float)sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

inline float Dist(float x1, float y1, float x2, float y2)
{
	return (float)sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

//dist between values, cycling around 255
inline short RGBDist(u8 current, u8 target)
{
	return ((256 + min(current, target)) - max(current, target)) * (target - current >= 0 ? 1 : -1);
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

/*inline bool IsLeader(int x, int y)
{
return (y % 2 == 1 ? false : ((x - (y%4==0 ? 0:1)) % 2 == 0 ? true : false));
}*/


void UpdateRGB()
{
	//update Leader values
	for (int y = 0; y < LHEIGHT; y++)
	{
		for (int x = 0; x < LHEIGHT; x++)
		{
			if (RGBDist(LEADER[x][y][0], LEADER[x][y][1]) > 0) { LEADER[x][y][0] += 1; }
			if (RGBDist(LEADER[x][y][0], LEADER[x][y][1]) < 0) { LEADER[x][y][0] -= 1; }

			//if (RGBDist(LEADER[x][y][2], LEADER[x][y][3]) > 0) { LEADER[x][y][2] += 1; }
			//if (RGBDist(LEADER[x][y][2], LEADER[x][y][3]) < 0) { LEADER[x][y][2] -= 1; }
		}
	}

	//update Leader targets
	for (int y = 0; y < LHEIGHT; y++)
	{
		for (int x = 0; x < LHEIGHT; x++)
		{
			//if (IsLeader(x, y))
			//{
			if (abs(LEADER[x][y][0] - LEADER[x][y][1]) <= 0)
			{
				if (!LEADER[x][y][2])
				{
					LEADER[x][y][1] = Rand() % 255;
					LEADER[x][y][2] = Rand() % 30 + 5000;
				}
				else
				{
					LEADER[x][y][2]--;
				}
			}

			//if (abs(LEADER[x][y][2] - LEADER[x][y][3]) <= 0) { LEADER[x][y][3] = Rand() % 255; }
			//}
		}
	}

	//Update LED values
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < HEIGHT; x++)
		{
			if (RGBDist(LED[x][y][0], LED[x][y][1]) > 0) { LED[x][y][0] += 1; }
			if (RGBDist(LED[x][y][0], LED[x][y][1]) < 0) { LED[x][y][0] -= 1; }

			//if (RGBDist(LEADER[x][y][2], LEADER[x][y][3]) > 0) { LEADER[x][y][2] += 1; }
			//if (RGBDist(LEADER[x][y][2], LEADER[x][y][3]) < 0) { LEADER[x][y][2] -= 1; }
		}
	}

	//Update LED targets
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < HEIGHT; x++)
		{
			float sum = 0, divisor = 0;
			for (int n = -1; n <= 1; n++)
			{
				for (int m = -1; m <= 1; m++)
				{
					int lx = (x / LMUL + n)*LMUL, ly = (y / LMUL + m)*LMUL;
					float weight = (float)(1.0 / Dist((u8)x, (u8)y, (u8)lx, (u8)ly));
					//calculate sum and divisor for interpolaation calculation
					sum += weight * LEADER[lx][ly][0];
					divisor += weight;
				}
			}

			//interpolation
			if (x % LMUL || y % LMUL)
			{
				//u8 val[4] = { u8(sum / divisor), u8(sum / divisor + 255.0 / 4.0), u8(sum / divisor + 2.0 * 255.0 / 4.0), u8(sum / divisor + 3.0 * 255.0 / 4.0) };
				float val = sum / divisor;
				int min[2] = { -1, 0 };

				//find val index with min distance from val to leader
				for (u8 j = 0; j < LWIDTH*LHEIGHT; j++)//val
				{
					int dist = 0;
					for (u8 n = 0; n < LWIDTH; n++)//leader
					{
						for (u8 m = 0; m < LHEIGHT; m++)
						{
							dist += abs(RGBDist(u8(val + j / (LWIDTH*LHEIGHT)), LEADER[n][m][0]));
						}
					}

					if (dist < min[0] || min[0] == -1)
					{
						min[0] = dist;
						min[1] = j;
					}
				}

				LED[x][y][1] = u8(val + min[1] / (LWIDTH*LHEIGHT));
			}
			else
			{
				//LED[x][y][1] = u8(leader[0].val * 0.6 + LED[x][y][1] * 0.4);
				float sum = 0; int count = 0;
				for (int n = -1; n <= 1; n++)
				{
					for (int m = -1; m <= 1; m++)
					{
						if (n && m && x + n >= 0 && x + n < WIDTH && y + m >= 0 && y + m < HEIGHT)
						{
							sum += (float)LED[x + n][y + m][0]; count++;
						}
					}
				}

				LED[x][y][1] = u8(sum / count);
				//LED[x][y][1] = leader[0].val;
			}
		}
	}
	/*for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < HEIGHT; x++)
		{
			struct { u8 pos[2]; u8 val; } leader[4];

			float sum = 0, divisor = 0;
			for (u8 j = 0; j < 4; j++)
			{
				leader[j].pos[0] = (j % 2 == 0 ? (x / LMUL) : (x / LMUL + 1));
				leader[j].pos[1] = (j < 2 ? (y / LMUL) : (y / LMUL + 1));
				leader[j].val = LEADER[leader[j].pos[0]][leader[j].pos[1]][0];
				leader[j].pos[0] *= LMUL; leader[j].pos[1] *= LMUL;

				float weight = (float)(1.0 / Dist(x, y, leader[j].pos[0], leader[j].pos[1]));
				//calculate sum and divisor for interpolaation calculation
				sum += weight * leader[j].val;
				divisor += weight;
			}

			//interpolation
			if (x % LMUL || y % LMUL)
			{
				u8 val[4] = { u8(sum / divisor), u8(sum / divisor + 255.0 / 4.0), u8(sum / divisor + 2.0 * 255.0 / 4.0), u8(sum / divisor + 3.0 * 255.0 / 4.0) };
				int min[2] = { -1, 0 };

				//find val index with min distance from val to leader
				for (u8 n = 0; n < 4; n++)//val
				{
					int dist = 0;
					for (u8 m = 0; m < 4; m++)//leader
					{
						dist += abs(RGBDist(val[n], leader[m].val));
					}

					if (dist < min[0] || min[0] == -1)
					{
						min[0] = dist;
						min[1] = n;
					}
				}

				LED[x][y][1] = val[min[1]];
			}
			else
			{
				//LED[x][y][1] = u8(leader[0].val * 0.6 + LED[x][y][1] * 0.4);
				float sum = 0; int count = 0;
				for (int n = -1; n <= 1; n++)
				{
					for (int m = -1; m <= 1; m++)
					{
						if (n && m && x + n >= 0 && x + n < WIDTH && y + m >= 0 && y + m < HEIGHT)
						{
							sum += (float)LED[x + n][y + m][0]; count++;
						}
					}
				}

				LED[x][y][1] = u8(sum / count);
				//LED[x][y][1] = leader[0].val;
			}
		}
	}*/

	/*
	for (int y = 0; y < LHEIGHT; y++)
	{
	for (int x = 0; x < LHEIGHT; x++)
	{
	u8 val = rand() % 255;
	LEADER[x][y][0][0] = ValueToR(val);
	LEADER[x][y][0][1] = ValueToG(val);
	LEADER[x][y][0][2] = ValueToB(val);
	}
	}
	*/
}

/*void DrawGraphLine(Window *window, int current, int target, int val)
{
window->WindowSurface->FillRectangle({ 400 + current, 0, 401 + current, 280 }, Colour(255, 255, 255));
window->WindowSurface->FillRectangle({ 400 + target, 0, 401 + target, 260 }, Colour(255, 255, 255));
window->WindowSurface->DrawLine({ 400 + current, 280 }, { 400 + target, 260 }, Colour(255, 255, 255));
window->WindowSurface->DrawText({ 400 + current, 275 }, std::to_string(val), Font(Colour(255, 255, 255)));
}*/

/*void DrawLEDTargets(Window *window)
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
}*/

void DrawRGB(Window *window)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int width = (400 / (WIDTH));
			int height = (400 / HEIGHT);

			int x1 = x * width;
			int y1 = y * height;
			int x2 = x1 + width - (DrawMode == 2 ? 0 : 4);
			int y2 = y1 + height - (DrawMode == 2 ? 0 : 4);

			//indicates the leader nodes.
			//every other row starting at y=0. Every other column, but shifted by 1 on every other used row.
			//int weight = (y % 2 == 1 ? 1 : ((x - (y%4==0 ? 0:1)) % 2 == 0 ? 3 : 1));

			//window->WindowSurface->FillRectangle({ x1, y1, x2, y2 }, Colour(LEADER[x][y][0], LEADER[x][y][1], LEADER[x][y][2]));
			window->WindowSurface->FillRectangle({ x1,y1 }, { x2,y2 }, Colour(ValueToR(LED[x][y][0]), ValueToG(LED[x][y][0]), ValueToB(LED[x][y][0])));
			if (DrawMode == 0)
			{
				if (!(x % LMUL) && !(y % LMUL)) { window->WindowSurface->DrawRectangle({ x1 - 1,y1 - 1 }, { x2 + 1,y2 + 1 }, Colour(ValueToR(LEADER[x / LMUL][y / LMUL][0]), ValueToG(LEADER[x / LMUL][y / LMUL][0]), ValueToB(LEADER[x / LMUL][y / LMUL][0])), 3.0); window->WindowSurface->DrawRectangle({ x1 - 3, y1 - 3 }, { x2 + 3, y2 + 3 }, Colour(255, 255, 255), 1.0); }
				window->WindowSurface->DrawRectangle({ x1,y1 }, { x2,y2 }, Colour(255, 255, 255), 1.0);
			}
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
		DrawRGB(window);

		for (uint8_t i = 0; i < 255; i++)
		{
			window->WindowSurface->FillRectangle({ 400 + i, 255 - ValueToR(i), 401 + i, 256 - ValueToR(i) }, Colour(255, 0, 0));
			window->WindowSurface->FillRectangle({ 400 + i, 255 - ValueToG(i) + 1, 401 + i, 256 - ValueToG(i) + 1 }, Colour(0, 255, 0));
			window->WindowSurface->FillRectangle({ 400 + i, 255 - ValueToB(i) + 2, 401 + i, 256 - ValueToB(i) + 2 }, Colour(0, 0, 255));
			window->WindowSurface->FillRectangle({ 400 + i, 260, 401 + i, 280 }, Colour(ValueToR(i), ValueToG(i), ValueToB(i)));
		}

		//DrawLEDTargets(window);

		WindowPtr->Draw();
	}
	else if (message == WM_KEYDOWN)
	{
		if (message.WParam() == WL_T)
		{
			DrawMode++;
			if (DrawMode > 2) { DrawMode = 0; }
		}
	}
	else if (message == WM_TIMER && message.WParam() == 1)
	{
		//Angle = (Angle > TAU ? 0 : Angle + 0.3);
		WindowPtr->AddMessage(MessageData({ WL_UPDATESURFACE, 0, 0 }), true);
	}
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	/*for (int j = 0; j < 4; j++)
	{
	for (int c = 0; c < 3; c++)
	{
	LEDLeader[j][c] = &(LEADER[LEDLeaderPos[j][0]][LEDLeaderPos[j][1]][c]);
	}
	}*/
	for (int y = 0; y < LHEIGHT; y++)
	{
		for (int x = 0; x < LWIDTH; x++)
		{
			LEADER[x][y][0] = LEADER[x][y][1] = rand() % 255;
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
