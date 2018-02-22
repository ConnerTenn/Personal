
#include "globals.h"





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


inline void Display()
{
	
	for (u8 x = 0; x < WIDTH; x++)
	{
		
		//Last bit of register done first
		SetPinsA(CLK, 0xFF);//remove these and expand it into a single assignment statement
		SetPinsA(CLK, 0x00);
		
		for (u8 yc = HEIGHT * 3 - 1; yc < HEIGHT * 3; yc--)
		{
			SetPinsA(SERIAL, LED[x][0][yc] > Lume ? 0xFF : 0x00);
			
			SetPinsA(CLK, 0xFF);
			SetPinsA(SERIAL | CLK, 0x00);
		}
		
		SetPinsA(COLS | NLA | NEN, COLS | NLA | NEN);
		SetPinsA(COLS | NLA, COLS ^ (COL0 << x));
	}
	
	
	Lume+=256/16;
}

//xc: x current		xn: x next		yc: y & colour combined
inline void Display2Y(const u8 xc, const u8 xn, const u8 yc, const u8 lume)
{
	PORTA = CLK | (PORTA = (COLS ^ (COL0 << xc)) | (LED[xn][0][yc] >= lume ? SERIAL : 0x00));//activate serial, then activate clock
}

inline void Display2X(const u8 xc, const u8 xn, const u8 lume)
{
	PORTA = (COLS ^ (COL0 << xc)) | CLK;
	
	
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
	
	PORTA = COLS | NLA | NEN;
	PORTA = COLS ^ (COL0 << xn);
}

__attribute__((optimize("unroll-loops")))
inline void Display2()
{
	for (u8 lume = 0; lume < 250; lume += 13)
	{
		Display2X(3, 0, lume);
		Display2X(0, 1, lume);
		Display2X(1, 2, lume);
		Display2X(2, 3, lume);
	}
	
	PORTA = COLS;
}

inline void Display3Y(const u8 c)
{
	//remove this loop
	PORTA = CLK | (PORTA = COLS | (FRGB & c ? SERIAL : 0x00));//activate serial, then activate clock
	
}

//__attribute__((optimize("unroll-loops")))
inline void Display3()
{
	//Last bit of register done first
	PORTA = CLK;
	
	Display3Y(4);
	Display3Y(2);
	Display3Y(1);
	Display3Y(4);
	Display3Y(2);
	Display3Y(1);
	Display3Y(4);
	Display3Y(2);
	Display3Y(1);
	Display3Y(4);
	Display3Y(2);
	Display3Y(1);
	Display3Y(4);
	Display3Y(2);
	Display3Y(1);
		
	PORTA = COLS | NLA | NEN;
	PORTA = 0;
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
inline void UpdateRGB5()
{
	if (!WTimer)
	{
		do { FRGB = (Rand() % 7) + 1; /*1-7 inclusive*/ } while (FRGB == FRGBL);
		FRGBL = FRGB;
		
		Display3();
	}
	WTimer = (WTimer < 100000 ? WTimer + 1 : 0);
}

inline void SetTimer()
{
	//cli();

	// Compare Match Interrupt Enable for Timer1
	TIMSK0 |= (1<<OCIE0A);
	// set timer1 counter initial value to 0
	TCNT0 = 0x00;
	// lets turn on 16 bit timer1 also
	TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
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
	if (ModeEnable == 2) { SetTimer(); }
	
	if ((PINC & 0x80) && (ModeEnable == 0)) { ModeEnable = 1; }
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
	
	PCMSK2 |= (1 << PCINT23);
	PCICR |= (1 << PCIE2);
	sei();
	
	while(1)
	{
		
		switch (Mode)
		{
		case 0:
			while(ModeEnable != 1)
			{
				UpdateRGB4();
				Display2();
			}
			break;
		case 1:
			while(ModeEnable != 1)
			{
				UpdateRGB3();
				Display2();
			}
			break;
		case 2:
			while(ModeEnable != 1)
			{
				UpdateRGB5();
			}
			break;
		}
		
		if (ModeEnable == 1)
		{
			Mode = (Mode + 1 > 2 ? 0 : Mode + 1); ModeEnable = 2;
			Timer = 0; WTimer = 0;
		}
	}
}

