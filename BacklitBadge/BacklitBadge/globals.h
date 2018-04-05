

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <avr/io.h>
#include <avr/iotn828.h>
#include <avr/interrupt.h>
#include <math.h>

#define min(a,b) (a <= b ? a : b)
#define max(a,b) (a >= b ? a : b)
#define abs(a) (a < 0 ? -a : a)

#define CLK		0b00000001
#define SERIAL	0b00000010
#define NEN		0b00000100
#define NLA		0b00001000
#define COL0	0b00010000
#define COL1	0b00100000
#define COL2	0b01000000
#define COL3	0b10000000
#define COLS	0b11110000

#define WIDTH 4
#define HEIGHT 5

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

u8 Timer = 0;
u32 WTimer = 0;

u8 LED[WIDTH][HEIGHT][3] = { 0 }; // WIDTH, HEIGHT, RGB
//u8 *LEDLeader[4][3] = { 0 };
//u8 const LEDLeaderPos[4][2] = { { 0, 0 },{ WIDTH - 1, 0 },{ 0, HEIGHT - 1 },{ WIDTH - 1, HEIGHT - 1 } };
//u8 LEDLeaderTarget[4][3] = { 0 };
u8 LEDS[WIDTH][HEIGHT] = { 0 };
u8 LEDTarget[WIDTH][HEIGHT] = { 0 };

u8 Target = 0;
u8 GRGB = 0;

u8 FRGB = 7;//Fast RGB
u8 FRGBL = 7; //Fast RGB Previous(Last)

//u8 DoWait = 0;
u8 Lume = 0;

u8 Mode = 0;
u8 ModeEnable = 0;


inline void SetPinsA(u8 mask, u8 value)
{
	//		set all selected bits in port to be 0      set new bits inside port from value
	//u8 buff;
	//buff = PORTA & ~mask; PORTA = buff| (value & mask);
	PORTA = (PORTA & ~mask) | (value & mask);
}
inline void SetPinsB(u8 mask, u8 value)
{
	//				set all selected bits in port to be 0      set new bits inside port from value
	//u8 buff;
	//buff = PORTB & ~mask; PORTB = buff | (value & mask);
	PORTB = (PORTB & ~mask) | (value & mask);
}
inline void SetPinsC(u8 mask, u8 value)
{
	//		set all selected bits in port to be 0      set new bits inside port from value
	//u8 buff;
	//buff = PORTC & ~mask; PORTC = buff | (value & mask);
	PORTC = (PORTC & ~mask) | (value & mask);
}


inline void Wait()//volatile u8 ticks)
{
	/*volatile int delay = Timer + ticks;
	
	while (Timer < delay)
	{*/
	/*for (u16 i = 0; i < ticks; i++)
	{
		__asm__ __volatile__("nop");
	}*/
	
	/*// Compare Match Interrupt Enable for Timer1
	TIMSK0 |= (1<<OCIE0A);
	// set timer1 counter initial value to 0
	TCNT0 = 0x00;
	// lets turn on 16 bit timer1 also
	TCCR0B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
	//set compare register
	OCR0A = ticks;
	
	DoWait = 1;
	
	// enable interrupts
	sei();
	
	while (DoWait)
	{
		__asm__ __volatile__("nop");
	}
	
	//disable interrupts
	cli();*/
	//__asm__ __volatile__("nop");
	//__asm__ __volatile__("nop");
	//__asm__ __volatile__("nop");
	//__asm__ __volatile__("nop");
	//__asm__ __volatile__("nop");
	//__asm__ __volatile__("nop");
	
	for (u16 i = 0; i < 10000; i++)
	{
		__asm__ __volatile__("nop");
	}
}

uint16_t lfsr = 0xACE1u;
uint16_t bit = 0;

uint16_t Rand()
{

	bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
	return lfsr = (lfsr >> 1) | (bit << 15);
}






#endif /* GLOBALS_H_ */