
#include "globals.h"



inline float FDist(u8 x1, u8 y1, u8 x2, u8 y2)
{
	return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

//dist between values, cycling around 255
inline char RGBDist(u8 current, u8 target)
{
	return ((255 + (short)min(current, target)) - (short)max(current, target)) * ((short)current - (short)target >= 0 ? 1 : -1);
}


inline u8 ValueToR(u8 val)
{
	//return (val <= 85 ? 255 - val * 3 : 0) + //First Decrease
	//(val > 170 ? val * 3 : 0); //Third Increase
	return ((val <= 85) ? (255 - val * 3) : (val > 170 ? val * 3 : 0));
}
inline u8 ValueToG(u8 val)
{
	//return (val <= 85 ? val * 3 : 0) +//First Increase
	//(val >= 85 && val < 170 ? 255 - val * 3 : 0);//Second Increase
	return (val <= 85 ? val * 3 : (val < 170 ? 255 - val * 3 : 0));
}
inline u8 ValueToB(u8 val)
{
	//return (val > 85 && val <= 170 ? val * 3 : 0) +//Second Increase
	//(val >= 170 ? 255 - val * 3 : 0);//Third Decrease
	//return (val > 85 && val <= 170 ? val * 3 : (val >= 170 ? 255 - val * 3 : 0));
	return (val > 170 ? 255 - val * 3 : (val > 85 ? val * 3 : 0));
}

inline void UpdateRGB()
{
	if (Timer % 50 == 0)
	{
		/*u8 colour[3] = { 0 };
		while (!(colour[0] | colour[1] | colour[2]))
		{ 
			colour[0] = (u8)(Rand() % 2);
			colour[1] = (u8)(Rand() % 2);
			colour[2] = (u8)(Rand() % 2);
		}
		for (u8 x = 0; x < WIDTH; x++)
		{
			for (u8 y = 0; y < HEIGHT; y++)
			{
				for (u8 c = 0; c < 3; c++)
				{
					LED[x][y][c] = (x >= WIDTH/2 ? colour[2-c] : colour[c]);
				}
			}
		}*/
		/*for (u8 i = HEIGHT - 1; i > 0; i--)
		{
			for (u8 j = 0; j < i * 2 + 1; j++)
			{
				u8 x = min((j <= i ? j : i), WIDTH - 1);
				u8 y = (j > i ? i - (j - i): i);
				for (u8 c = 0; c < 3; c++)
				{
					LED[x][y][c] = LED[i-1][i-1][c];
				}
			}
		}
		
		u8 colour[3] = { 0 };
		while (!(colour[0] | colour[1] | colour[2]))
		{
			colour[0] = (u8)(Rand() % 2);
			colour[1] = (u8)(Rand() % 2);
			colour[2] = (u8)(Rand() % 2);
		}
		for (u8 c = 0; c < 3; c++)
		{
			LED[0][0][c] = colour[c];
		}*/
		
		
		/*for (u8 x = 0; x < WIDTH; x++)
		{
			for (u8 y = 0; y < HEIGHT; y++)
			{
				//for (u8 c = 0; c < 3; c++)
				//{
					LED[x][y][0] = 255 / 5 * (y+1);
					LED[x][y][2] = 255 / 5 * (HEIGHT - y);
				//}
			}
		}*/
		
		
		for (u8 x = 0; x < WIDTH; x++)
		{
			for (u8 y = 0; y < HEIGHT; y++)
			{
				u8 val = Rand() % 255;
				LED[x][y][0] = ValueToR(val);
				LED[x][y][1] = ValueToG(val);
				LED[x][y][2] = ValueToB(val);
			}
		}
	}
	
	Timer++;
}

inline void UpdateRGB2()
{
	for (u8 c = 0; c < 3; c++)
	{
		u8 y, x;
		for (y = 0; y < HEIGHT; y++)
		{
			for (x = 0; x < WIDTH; x++)
			{
				//don't calculate for primary Led
				if (!((x == 0 && (y == 0 || y == HEIGHT - 1)) || (x == WIDTH - 1 && (y == 0 || y == HEIGHT - 1))))
				{
					float sum = 0, divisor = 0;
					for (u8 j = 0; j < 4; j++)
					{
						float weight = (1.0f / FDist(x, y, LEDLeaderPos[j][0], LEDLeaderPos[j][1]));
						//calculate sum and divisor for interpolation calculation
						sum += weight * *LEDLeader[j][c];
						divisor += weight;
					}

					//interpolation
					LED[x][y][c] = u8(sum / divisor);
				}
			}
		}
		for (u8 j = 0; j < 4; j++)
		{
			if (*LEDLeader[j][c] - LEDLeaderTarget[j][c] > 0) { *LEDLeader[j][c] -= 1; }
			if (*LEDLeader[j][c] - LEDLeaderTarget[j][c] < 0) { *LEDLeader[j][c] += 1; }
		}
	}
	
	//Update each Primary LED
	for (u8 j = 0; j < 4; j++)
	{
		//Target Reached; set new targets
		if (abs(*LEDLeader[j][0] - LEDLeaderTarget[j][0]) <= 1 &&
		abs(*LEDLeader[j][1] - LEDLeaderTarget[j][1]) <= 1 &&
		abs(*LEDLeader[j][2] - LEDLeaderTarget[j][2]) <= 1)
		{
			u8 val = Rand() % 255;
			LEDLeaderTarget[j][0] = ValueToR(val);
			LEDLeaderTarget[j][1] = ValueToG(val);
			LEDLeaderTarget[j][2] = ValueToB(val);
		}
	}
}

//individual colours
__attribute__((optimize("unroll-loops")))
inline void UpdateRGB3()
{
	for (u8 xy = 0; xy < WIDTH * HEIGHT; xy++)
	{
		//if (LEDS[0][xy] - LEDTarget[0][xy] > 0) { LEDS[0][xy] -= 1; }
		//else if (LEDS[0][xy] - LEDTarget[0][xy] < 0) { LEDS[0][xy] += 1; }
		LEDS[0][xy] += (LEDS[0][xy] - LEDTarget[0][xy] > 0 ? -1 : 1);
		
		LED[0][xy][0] = ValueToR(LEDS[0][xy]); LED[0][xy][1] = ValueToG(LEDS[0][xy]); LED[0][xy][2] = ValueToB(LEDS[0][xy]);
	
		if (!Timer)
		{
			LEDTarget[0][xy] = Rand() % 256;
		}
	}
	Timer++;
}

//All 1 colour
__attribute__((optimize("unroll-loops")))
inline void UpdateRGB4()
{
	/*if (!Timer)
	{
		Target = Rand() % 256;
	}*/
	Target = (!Timer ? (Rand() % 256) : Target);
	GRGB += (!(Timer % 4) ? (GRGB - Target > 0 ? -1 : 1) : 0);
	LED[0][0][0] = ValueToR(GRGB); LED[0][0][1] = ValueToG(GRGB); LED[0][0][2] = ValueToB(GRGB);
	for (u8 xy = 1; xy < WIDTH * HEIGHT; xy++)
	{
		//if (LEDS[0][xy] - LEDTarget[0][xy] > 0) { LEDS[0][xy] -= 1; }
		//else if (LEDS[0][xy] - LEDTarget[0][xy] < 0) { LEDS[0][xy] += 1; }
		//LEDS[0][xy] += (LEDS[0][xy] - LEDTarget[0][xy] > 0 ? -1 : 1);
		
		LED[0][xy][0] = LED[0][0][0];
		LED[0][xy][1] = LED[0][0][1];
		LED[0][xy][2] = LED[0][0][2];
	}
	Timer++;
}

//All Fast colour
//__attribute__((optimize("unroll-loops")))





inline void Display()
{
	//SetPins('A', NLA | NEN, NEN); //NL low, NEN high
	//SetPins('A', NEN, 0x00);
	//SetPins('A', NLA, 0x00);
	
	for (u8 x = 0; x < WIDTH; x++)
	{
		
		//Last bit of register done first
		//Wait(1);
		SetPinsA(CLK, 0xFF);//remove these and expand it into a single assignment statement
		//Wait();
		SetPinsA(CLK, 0x00);
		/*
		for (u8 y = HEIGHT - 1; y < HEIGHT; y--)
		{
			//remove this loop
			for (u8 c = 3 - 1; c < 3; c--)
			{
				SetPinsA(SERIAL, LED[x][y][c] > Lume ? 0xFF : 0x00);
				
				//Wait();
				SetPinsA(CLK, 0xFF);
				//Wait();
				SetPinsA(SERIAL | CLK, 0x00);
				//Wait(4);
			}
		}*/
		///*
		for (u8 yc = HEIGHT * 3 - 1; yc < HEIGHT * 3; yc--)
		{
			//remove this loop
			SetPinsA(SERIAL, LED[x][0][yc] > Lume ? 0xFF : 0x00);
				
			//Wait();
			SetPinsA(CLK, 0xFF);
			//Wait();
			SetPinsA(SERIAL | CLK, 0x00);
			//Wait(4);
		}//*/
		
		//SetPinsA(COLS | NEN, COLS);
		
		//Latch Values
		//Wait(10);
		//SetPinsA(NLA, NLA); //NL to high
		//Wait();
		//SetPinsA(NLA, 0x00); //NL to low
		//Wait(10);

		//SetPinsA(COLS | NEN, COLS ^ (COL0 << x));
		
		//SetPins('A', NEN, 0x00);
		//Wait(10);
		//SetPins('A', NEN, NEN);
		
		SetPinsA(COLS | NLA | NEN, COLS | NLA | NEN);
		SetPinsA(COLS | NLA, COLS ^ (COL0 << x));
	}
	//Wait(300);
	//while (Timer < 30)
	//{
	//SetPins('A', NEN, NEN);
	
	//PORTC = ~PORTC;
	//}
	Lume+=256/16;
}

inline void Display2Y(const u8 xc, const u8 xn, const u8 yc, const u8 lume)
{
	PORTA = CLK | (PORTA = (COLS ^ (COL0 << xc)) | (LED[xn][0][yc] >= lume ? SERIAL : 0x00));//activate serial, then activate clock
	//PORTA = (COLS ^ (COL0 << x)) | (LED[x][0][yc] > Lume ? SERIAL : 0x00);
	//PORTA = CLK | PORTA;
	//PORTA = (COLS ^ (COL0 << x));
}

inline void Display2X(const u8 xc, const u8 xn, const u8 lume)
{
	//SetPinsA(CLK, 0xFF);
	//Wait();
	//SetPinsA(CLK, 0x00);
	PORTA = (COLS ^ (COL0 << xc)) | CLK;
	//PORTA = (COLS ^ (COL0 << xc));
	
	/*for (u8 yc = HEIGHT * 3 - 1; yc < HEIGHT * 3; yc--)
	{
		//SetPinsA(SERIAL, LED[x][0][yc] > Lume ? 0xFF : 0x00);
		
		//SetPinsA(CLK, 0xFF);
		//SetPinsA(SERIAL | CLK, 0x00);
		
		
		PORTA = CLK | (PORTA = (COLS ^ (COL0 << x)) | (LED[x][0][yc] > Lume ? SERIAL : 0x00));//activate serial, then activate clock
		PORTA = (COLS ^ (COL0 << x));
	}*/
	Display2Y(xc, xn, 14, lume);
	Display2Y(xc, xn, 13, lume);
	Display2Y(xc, xn, 12, lume);
	Display2Y(xc, xn, 11, lume);
	Display2Y(xc, xn, 10, lume);
	Display2Y(xc, xn, 9, lume);
	Display2Y(xc, xn, 8, lume);
	Display2Y(xc, xn, 7, lume);
	Display2Y(xc, xn, 6, lume);
	Display2Y(xc, xn, 5, lume);
	Display2Y(xc, xn, 4, lume);
	Display2Y(xc, xn, 3, lume);
	Display2Y(xc, xn, 2, lume);
	Display2Y(xc, xn, 1, lume);
	Display2Y(xc, xn, 0, lume);
	
	
	
	//SetPinsA(COLS | NLA, COLS | NLA);
	//SetPinsA(COLS | NLA, COLS ^ (COL0 << x));
	PORTA = COLS | NLA | NEN;
	PORTA = COLS ^ (COL0 << xn);
}

__attribute__((optimize("unroll-loops")))
inline void Display2()
{
	for (u8 lume = 0; lume < 250; lume += 13)
	{
	//do
	//{
		//PORTA = (COLS ^ (COL0 << 3)) | CLK;
		Display2X(3, 0, lume);
		Display2X(0, 1, lume);
		Display2X(1, 2, lume);
		Display2X(2, 3, lume);
	
		//Lume+=256/16;
	}
	//}
	//while (Lume);
	PORTA = COLS;
}

__attribute__((optimize("unroll-loops")))
inline void Display3()
{
	
	
	//Last bit of register done first
	PORTA = CLK;
		
	for (u8 y = HEIGHT - 1; y < HEIGHT; y--)
	{
		for (u8 c = 4; c; c>>=1)
		{
		//remove this loop
			PORTA = CLK | (PORTA = COLS | (FRGB & c ? SERIAL : 0x00));//activate serial, then activate clock
				
		}
	}
		
	PORTA = COLS | NLA | NEN;
	PORTA = 0;
}

inline void UpdateRGB5()
{
	if (!WTimer)
	{
		do { FRGB = (Rand() % 7) + 1; /*1-7 inclusive*/ } while (FRGB == FRGBL);
		FRGBL = FRGB;
		
		Display3();
	}
	WTimer = (WTimer < 50000 ? WTimer + 1 : 0);
}

inline void SetTimer()
{
	//cli();

	// Compare Match Interrupt Enable for Timer1
	TIMSK0 |= (1<<OCIE0A);
	// set timer1 counter initial value to 0
	TCNT0 = 0x00;
	// lets turn on 16 bit timer1 also
	TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00);
	//set compare register
	OCR0A = 0x7D;


	// enable interrupts
	//sei();
}

ISR(TIMER0_COMPA_vect) // timer compare interrupt service routine
{
	TIMSK0 = TIMSK0 & !(1<<OCIE0A);
	ModeEnable = 0;
	//DoWait = false;
	//Timer++;
	//PORTB = ~PORTB;
}

ISR(PCINT2_vect)
{
	if ((PINC & 0x80) && (ModeEnable == 0)) { ModeEnable = 1; }
	if (ModeEnable == 2) { SetTimer(); }
	//ModeSwitch = (ModeSwitch ? ModeSwitch : 1);
}


int main()
{
	DDRA = 0xFF;
	DDRB = 0xFF;//Last pin is input
	DDRC = 0x7F;
	
	PORTA = COLS;
	PORTB = 0x00;
	PORTC = 0x20;
	//u16 a = 0, b = 20, c = 1;
	//u64 a = 0, b = 0, c = 0;
	
	//LED[3][1][2] = 0xFF;
	//LED[3][2][2] = 0xFF;
	
	//SetPinsA(COLS, COLS);
	
	//SetTimer();
	PCMSK2 |= (1 << PCINT23);
	PCICR |= (1 << PCIE2);
	sei();
	
	while(1)
	{
		switch (Mode)
		{
		case 0:
			UpdateRGB4();
			Display2();
			break;
		case 1:
			UpdateRGB3();
			Display2();
			break;
		case 2:
			UpdateRGB5();
			//Wait();
		}
		/*if (ModeEnable) 
		{ 
			if (ModeEnable == 1) 
			{
				Mode = (Mode > 2 ? 0 : Mode + 1);
				for (u8 x = 0; x < WIDTH; x++)
				{
					for (u8 y = 0; y < HEIGHT; y++)
					{
						for (u8 c = 0; c < 3; c++)
						{
							LED[x][y][c] = 0;
						}
						LEDS[x][y] = 0;
						LEDTarget[x][y] = 0;
					}
				}
				Target = 0; GRGB = 0; FRGB = 0;
				Timer = 0; WTimer = 0;
			} 
			ModeEnable = (ModeEnable < 10 ? ModeEnable + 1 : 0); 
		}*/
		if (ModeEnable == 1)
		{
			Mode = (Mode + 1 > 2 ? 0 : Mode + 1); ModeEnable = 2;
			Timer = 0; WTimer = 0;
		}
	}
}

