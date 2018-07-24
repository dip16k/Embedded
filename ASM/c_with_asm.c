#include<lpc214x.h>

int shift(unsigned char x)
{
	__asm{
		"mov r5,r0\n"
		"mov r5,r5,ror"
	}
	return x;
}
int main()
{
	unsigned char a = 0xf0;
	
	a = shift(a);
	
	return a;
}