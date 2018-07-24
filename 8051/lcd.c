#include <REG51.h>
#include "i2c.h"
#include "lcd.h"


void sendData(unsigned char val)
{
	LCDPORT = val;
	LCDPORT = LCDPORT + 0x05;
	delay_ms(1);
	LCDPORT = LCDPORT - 0x04;
}

void DisplayData(unsigned char val)
{
	unsigned char msb;
	
	msb = (0xf0 & val);
	sendData(msb);
	msb = ((val << 4) & 0xf0);
	sendData(msb);
}

void sendCmd(unsigned char cmd)
{
	LCDPORT = cmd;
	LCDPORT = LCDPORT + 0x04;
	delay_ms(1);
	LCDPORT = LCDPORT - 0x04;
}
void DisplayCmd(unsigned char cmd)
{
	unsigned char msb;
	
	msb = (cmd & 0xf0);
	sendCmd(msb);
	msb = ((cmd << 4) & 0xf0);
	sendCmd(msb);
}
void LcdInit()
{
	DisplayCmd(0x02);
	DisplayCmd(0x28);
	DisplayCmd(0x0e);
	DisplayCmd(0x06);
}

void DisplayString(char * string)
{
	unsigned char i = 0;
	
	while (string[i])
	{
		DisplayData(string[i]);
		i++;
	}
}
/*
	it will print up to 5digit of data
*/
void DisplayNum(int num)
{	
		DisplayData((num/10000)+0x30);
		num=num%10000;
		
		DisplayData((num/1000)+0x30);
		num=num%1000;
		
		DisplayData((num/100)+0x30);
		num=num%100;
		
		DisplayData((num/10)+0x30);
		
		DisplayData((num%10)+0x30);
}

void Displayfnum(float num)
{
	unsigned long int a,b,c,d;
	DisplayCmd(0x04);
	a=num*1000;
	c=a/1000;
	while(a!=0)
	{
		b=a%10;
		if(b==0)
			DisplayData(48);
		else
		DisplayData(b+48);
		a=a/10;
	}
	DisplayData('.');
	while(c!=0)
	{
		d=c%10;
		DisplayData(d+48);
		c=c/10;
	}
}