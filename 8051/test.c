/* p2 lcd controling pin p3 data pin*/
#include<reg51.h>
#define LCDPORT P2
sbit rs=P2^0;
sbit rw=P2^1;
sbit en=P2^2;

sbit clk=P1^0;
sbit din=P1^1;
sbit dout=P1^2;
sbit cs=P1^3;
//void disp_cmd(unsigned char );

void delay_ms(unsigned char n)
{
	unsigned char i,j;
	for(i=n;i>0;i--)
	{
			for(j=250;j>0;j--);
			for(j=250;j>0;j--);
	}
}
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
void disp_fnum(float num)
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

float adc_read(unsigned char ch)
{
	unsigned int adc_val;
	unsigned char i=0;
	bit d1,d0;
		if(ch==0)		{	d0=d1=0;}
		else if(ch==1)	{d1=0;d0=1;}
		else if(ch==2){d1=1;d0=0;}
		else if(ch==3){d1=1;d0=1;}
		
		din=dout=cs=clk=1;
		cs=0;// communication start
		clk=0;clk=1;	//start
		clk=0;clk=1;		//single ended
		clk=0;clk=1;		//dont care
		clk=0;	din=d1; clk=1	;	//d1
		clk=0;	din=d0;	clk=1	;//d0 now conversion start
		clk=0; clk=1;	//stop
		clk=0;clk=1;		//null bit
		
		for(i=0;i<12;i++)
		{
				clk=0;
				clk=1;
				if(dout)
				adc_val|=0x800>>i;
			}
		cs=1;		//stop communication
		return (adc_val*(5.00/4096));
		}
main()
{
		float buff;
		LcdInit();
		DisplayCmd(0x80);
		DisplayString("SPI COMM..");
		while(1)
		{
				buff=adc_read(1);
				DisplayCmd(0xca);
				disp_fnum(100*buff);
			delay_ms(500);
		}
	}