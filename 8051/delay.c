#include <REG51.h>

void _delay_ms(unsigned char n)
{
	unsigned int i=0;
	for(i=0;i<n;i++)
		for(i=0;i<65500;i++);
		for(i=0;<65500;i++);
}