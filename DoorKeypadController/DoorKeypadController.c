
//#include <avr/math.h>
#include <avr/io.h>
//#include <avr/io2313.h>
#include <avr/interrupt.h>

//DDR_	Direction register  1:out  0:in
//PORT_	Data Register
//PIN_	Input pins
typedef uint8_t bool;


/*void SetPins(char portID, char portLabel, char mask, char value)
{
	volatile uint8_t *portPtr = 0;
	if (portID == 'P' && portLabel == 'B') { portPtr = &PORTB; }
	if (portID == 'D' && portLabel == 'B') { portPtr = &DDRB; }
	if (portID == 'P' && portLabel == 'D') { portPtr = &PORTD; }
	if (portID == 'D' && portLabel == 'D') { portPtr = &DDRD; }

	*portPtr = *portPtr & ~mask; //set all selected bits in port to be 0
	*portPtr = *portPtr | (value & mask); //set new bits inside port from value
}*/

void SetPins(volatile char portID, volatile char portLabel, volatile char mask, volatile char value)
{
	//				set all selected bits in port to be 0      set new bits inside port from value
	if (portID == 'P' && portLabel == 'B') { PORTB = PORTB & ~mask; PORTB = PORTB | (value & mask); }
	if (portID == 'D' && portLabel == 'B') { DDRB = DDRB & ~mask; DDRB = DDRB | (value & mask); }
	if (portID == 'P' && portLabel == 'D') { PORTD = PORTD & ~mask; PORTD = PORTD | (value & mask); }
	if (portID == 'D' && portLabel == 'D') { DDRD = DDRD & ~mask; DDRD = DDRD | (value & mask); }

	//*portPtr = *portPtr & ~mask; //set all selected bits in port to be 0
	//*portPtr = *portPtr | (value & mask); //set new bits inside port from value
}


//Very Fast Timer 1
inline void SetFastTimer()
{
	//cli();

	// Compare Match Interrupt Enable for Timer1
    TIMSK |= (1<<OCIE1A);
	// set timer1 counter initial value to 0
    TCNT1 = 0x0000;
	// lets turn on 16 bit timer1 also
    TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10) | (1 << CTC1);
	//set compare register
	OCR1A = 0x0002;


	// enable interrupts
    sei();
}


//Pretty slow Timer 1
inline void SetSlowTimer()
{
	//cli();

	// Compare Match Interrupt Enable for Timer1
    TIMSK |= (1<<OCIE1A);
	// set timer1 counter initial value to 0
    TCNT1 = 0x0000;
	// lets turn on 16 bit timer1 also
    TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10) | (1 << CTC1);
	//set compare register
	OCR1A = 0x04E2;


	// enable interrupts
    sei();
}

inline void SetTimer0()
{
	TIMSK |= (1<<TOIE0);
	// set timer1 counter initial value to 0
    TCNT0 = 0x00;
	// lets turn on 16 bit timer1 also
    TCCR0 |= (0 << CS12) | (1 << CS11) | (1 << CS10);
	//set compare register
	//OCR1A = 0x04E2;
}

uint32_t Counter = 0;

ISR (TIMER0_OVF0_vect)          // timer overflow interrupt service routine
{
	++Counter;
}

inline void DisableMotor()
{
	SetPins('P', 'B', 0b00011000, 0b00000000);
}

inline void EnableMotor()
{
	//DisableMotor();
	SetPins('P', 'B', 0b00011000, 0b00001000);
}

inline void ReverseMotor()
{
	//DisableMotor();
	SetPins('P', 'B', 0b00011000, 0b00010000);
}

/*
D0 D1 D2
D3 D4 D5
D6 B0 B1

0 1 2
3 4 5
6 7 8
*/
uint16_t Password[6] = { 1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5};
uint8_t PasswordIndex = 0;
uint32_t CorrectPasswordCntStart = 0;
bool KeyPressed = 0;
bool EnableKey = 1;
uint32_t KeyPressedCntStart = 0;
uint16_t Keys = 0x0000;
inline void ProcessInput()
{
	if (Keys)
	{
		if (!KeyPressed && EnableKey)
		{
			KeyPressed = 1;
			KeyPressedCntStart = Counter;
			EnableKey = 0;
			SetPins('P', 'B', 0x04, 0x04);

			//test that only 1 key is pressed
			if (!(Keys & (Keys - 1)))
			{
				//find whick key is pressed
				//int keyNumber = 0;
				//while (Keys != 1) { Keys >>= 1; ++keyNumber; }
				//keyNumber = log(Keys);
				//check if key is the correct button in the sequence
				if (Password[PasswordIndex] == Keys)//keyNumber)
				{
					++PasswordIndex;
				}
				else
				{
					PasswordIndex = 0;
				}
				//correct password condition
				if (PasswordIndex == 4)
				{
					PasswordIndex = 0;
					//SetPins('P', 'B', 0x08, 0x08);//set correct output line high
					EnableMotor();
					CorrectPasswordCntStart = Counter;
				}
			}
			else
			{
				PasswordIndex = 0;
			}
		}
		else
		{
			KeyPressedCntStart = Counter;
		}
	}
	else
	{
		KeyPressed = 0;
	}
}


bool State = 0;

ISR (TIMER1_COMP1_vect)          // timer compare interrupt service routine
{
	cli();
	if (State)
	{
		//DDRD = 0x00; //all inputs
		//short pins;
		Keys = PIND;
		Keys |= (PINB & 0x03) << 6;
		
		//PORTD = 0xFF; //pull up
		//DDRD = 0xFF; //all outputs
		SetPins('P', 'D', 0xFF, 0xFF);//set D pull up
		SetPins('P', 'B', 0x03, 0xFF);//set B pull up
		SetPins('D', 'D', 0xFF, 0xFF);//set D outputs
		SetPins('D', 'B', 0x03, 0xFF);//set B outputs
		
		//PORTD = 0xFF;
		/*if (pins & (1 << 6))
		{
			PORTB |= (1 << 0);//set to 1
		}
		else
		{
			PORTB &= ~(1 << 0);//set to 0
		}*/
		ProcessInput();

		State = 0;
		SetSlowTimer();
	}
	else
	{
		//PORTD = 0x0;
		//DDRD = 0x00; //all inputs
		//PORTD = 0x00; //pull down
		SetPins('D', 'D', 0xFF, 0x00);//set D inputs
		SetPins('D', 'B', 0x03, 0x00);//set B inputs
		SetPins('P', 'D', 0xFF, 0x00);//set D pull down
		SetPins('P', 'B', 0x03, 0x00);//set B pull down

		State = 1;
		SetFastTimer();
	}
}

uint8_t MotorState = 0;
void main()
{
	SetTimer0();
	SetSlowTimer();
	
	//DDRB = 0b00000011;
	//DDRD = 0xFF;
	SetPins('D', 'D', 0xFF, 0xFF);
	SetPins('D', 'B', 0x1F, 0x1F);

	//PORTD = 0xFF;
	//PORTB = 0b00000010;
	SetPins('P', 'D', 0xFF, 0xFF);
	SetPins('P', 'B', 0x03, 0x03);

	//int i = 0;
	while (1)
	{
		if (CorrectPasswordCntStart)
		{
			if (Counter - CorrectPasswordCntStart >= 4200 && MotorState == 0)
			{
				//CorrectPasswordCntStart = 0;
				//SetPins('P', 'B', 0x08, 0x00);
				DisableMotor();
				MotorState = 1;
			}
			if (Counter - CorrectPasswordCntStart >= 4700 && MotorState == 1)
			{
				//CorrectPasswordCntStart = 0;
				//SetPins('P', 'B', 0x08, 0x00);
				ReverseMotor();
				MotorState = 2;
			}
			if (Counter - CorrectPasswordCntStart >= 6700 && MotorState == 2)
			{
				CorrectPasswordCntStart = 0;
				DisableMotor();
				MotorState = 0;
			}
			if (CorrectPasswordCntStart > Counter)
			{
				CorrectPasswordCntStart = 0;
			}
		}
		if (KeyPressedCntStart)
		{
			//if (Counter - KeyPressedCntStart >= 10)
			//{
			//	//KeyPressedCntStart = 0;
			//	SetPins('P', 'B', 0x04, 0x00);
			//}
			if (Counter - KeyPressedCntStart >= 50)
			{
				SetPins('P', 'B', 0x04, 0x00);
				KeyPressedCntStart = 0;
				EnableKey = 1;
			}
			if (KeyPressedCntStart > Counter)
			{
				KeyPressedCntStart = 0;
			}
		}
		//SetPin(5, 1);
		//Delay(100);
		//SetPin(5, 0);
		//SetPin(6, ReadPin(5));
		//Delay(100);
		if (TCNT1 > OCR1A)
		{
			TCNT1 = 0;
		}
	}
}
