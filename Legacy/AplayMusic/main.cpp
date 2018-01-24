
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323
#define TAU (2.0*PI) 


int main()
{
	unsigned char byte = 0;
	int freq = 0;

	//printf("Begin\n");
	/*for (int i = 0; i < 100000; i++)
	{
		freq = (sin((float)i/10000.0f * TAU)+1.0) * 50.0 + 70;

		byte = (i%freq) < freq/2 ? 0xF : 0x0;
		//putchar(byte);
		printf((const char *)&byte);
		//unsigned int out = byte;
		//std::cout << "Value:" << out << "\r";
	}*/

	/*for (int i = 0; i < 100000; i++)
	{
		byte = int(i*8);
		putchar(byte);
		//printf((const char *)&byte);
	}*/
	
	for (int i = 0; i < 10000; i++)
	{
		byte = int((sin(i*TAU/60.0)+1.0) * 7.5);
		putchar(byte);
	}

	return 0;
}

