
#include "globals.h"



/*


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
}
inline u8 ValueToG(u8 val)
{
	return (val <= 85 ? val * 3 : 0) +//First Increase
	(val >= 85 && val < 170 ? 255 - val * 3 : 0);//Second Increase
}
inline u8 ValueToB(u8 val)
{
	return (val > 85 && val <= 170 ? val * 3 : 0) +//Second Increase
	(val >= 170 ? 255 - val * 3 : 0);//Third Decrease
}

inline void UpdateRGB()
{
	for (u8 c = 0; c < 3; c++)
	{
		for (u8 y = 0; y < HEIGHT; y++)
		{
			for (u8 x = 0; x < WIDTH; x++)
			{
				//don't calculate for primary Led
				if (!((x == 0 && (y == 0 || y == HEIGHT - 1)) || (x == WIDTH - 1 && (y == 0 || y == HEIGHT - 1))))
				{
					float sum = 0, divisor = 0;
					for (u8 j = 0; j < 4; j++)
					{
						float weight = (float)(1.0 / Dist(x, y, LEDLeaderPos[j][0], LEDLeaderPos[j][1]));
						//calculate sum and divisor for interpolation calculation
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
			if (RGBDist(LEDLeaderTarget[j][c], LEDLeaderTarget[j][c]) > 0) { *LEDLeader[j][c] += 1; }
			if (RGBDist(LEDLeaderTarget[j][c], LEDLeaderTarget[j][c]) < 0) { *LEDLeader[j][c] -= 1; }
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
			u8 val = Rand() % 255;
			LEDLeaderTarget[j][0] = ValueToR(val);
			LEDLeaderTarget[j][1] = ValueToG(val);
			LEDLeaderTarget[j][2] = ValueToB(val);
		}
	}
}
*/

void Display()
{
	//SetPins('A', NLA | NEN, NEN); //NL low, NEN high
	//SetPins('A', NEN, 0x00);
	//SetPins('A', NLA, 0x00);
	
	for (u8 x = 0; x < WIDTH; x++)
	{
		
		//Last bit of register done first
		//Wait(1);
		SetPinsA(CLK | SERIAL, 0xFF);
		//Wait();
		SetPinsA(SERIAL | CLK, 0x00);
		
		for (u8 y = HEIGHT - 1; y < HEIGHT; y--)
		{
			//remove this loop
			for (u8 c = 3 - 1; c < 3; c--)
			{
				SetPinsA(SERIAL, LED[x][y][c] ? 0xFF : 0x00);
				
				//Wait();
				SetPinsA(CLK, 0xFF);
				//Wait();
				SetPinsA(SERIAL | CLK, 0x00);
				//Wait(4);
			}
		}
		/*
		for (u8 yc = HEIGHT * 3 - 1; yc < HEIGHT * 3; yc--)
		{
			//remove this loop
			SetPinsA(SERIAL, LED[x][0][yc] ? 0xFF : 0x00);
				
			//Wait();
			SetPinsA(CLK, 0xFF);
			//Wait();
			SetPinsA(SERIAL | CLK, 0x00);
			//Wait(4);
		}*/
		
		SetPinsA(COLS | NEN, COLS);
		
		//Latch Values
		//Wait(10);
		SetPinsA(NLA, NLA); //NL to high
		//Wait();
		SetPinsA(NLA, 0x00); //NL to low
		//Wait(10);

		SetPinsA(COLS | NEN, COLS ^ (COL0 << x));
		
		//SetPins('A', NEN, 0x00);
		//Wait(10);
		//SetPins('A', NEN, NEN);
	}
	//Wait(300);
	//while (Timer < 30)
	//{
	//SetPins('A', NEN, NEN);
	
	PORTC = ~PORTC;
	//}
}

void SetTimer()
{
	//cli();

	// Compare Match Interrupt Enable for Timer1
	TIMSK0 |= (1<<OCIE0A);
	// set timer1 counter initial value to 0
	TCNT0 = 0x00;
	// lets turn on 16 bit timer1 also
	TCCR0B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
	//set compare register
	OCR1A = 0x7D;


	// enable interrupts
	sei();
}

ISR (TIMER0_COMPA_vect) // timer compare interrupt service routine
{
	
	DoWait = false;
	//Timer++;
	//PORTB = ~PORTB;
}

void UpdateRGB()
{
	if (Timer % 200 == 0)
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
		for (u8 i = HEIGHT - 1; i > 0; i--)
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
		}
	}
	
	Timer++;
}

int main()
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	//u16 a = 0, b = 20, c = 1;
	//u64 a = 0, b = 0, c = 0;
	
	//LED[3][1][2] = 0xFF;
	//LED[3][2][2] = 0xFF;
	
	SetPinsA(COLS, COLS);
	
	
	//SetTimer();
	
	while(1)
	{
		UpdateRGB();
		Display();
	}
}

