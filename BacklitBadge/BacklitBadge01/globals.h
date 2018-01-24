

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

u64 Timer = 0;

u8 Colour[3] = { 0 };
u8 PrevColour[3] = { 0 };


inline void SetPins(char portLabel, u8 mask, u8 value)
{
	//				set all selected bits in port to be 0      set new bits inside port from value
	if (portLabel == 'A') { PORTA = PORTA & ~mask; PORTA = PORTA | (value & mask); }
	else if (portLabel == 'B') { PORTB = PORTB & ~mask; PORTB = PORTB | (value & mask); }
	else if (portLabel == 'C') { PORTC = PORTC & ~mask; PORTC = PORTC | (value & mask); }
}

inline void Wait(volatile u64 ticks)
{
	/*volatile int delay = Timer + ticks;
	
	while (Timer < delay)
	{*/
	for (u32 i = 0; i < ticks; i++)
	{
		__asm__ __volatile__("nop");
	}
}

uint16_t Rand()
{
	volatile static uint16_t lfsr = 0xACE1u;
	volatile static uint16_t bit = 0;

	bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
	return lfsr = (lfsr >> 1) | (bit << 15);
}






#endif /* GLOBALS_H_ */