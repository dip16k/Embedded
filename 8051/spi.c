#include<reg51.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit clk  = P1^0;
sbit din  = P1^1;
sbit dout = P1^2;
sbit cs  = P1^3;

float read_adc(u8 ch)
{
	u16 adc_val = 0;
	u8 i;
	bit d1, d0;
	
	if		 (ch == 0) {d1=0; d0=0;}
	else if(ch == 1){d1=0; d0=1;}
	else if(ch == 2){d1=1; d0=0;}
	else if(ch == 3){d1=1; d0=1;}
	
	//make all high
	din = dout = cs = clk = 1;
	
	cs = 0;//select slave
	
	clk = 0; clk =1 ; //start
	clk = 0; clk = 1;//single ended
	clk = 0; clk = 1; //dont care
	//channel
	clk = 0; din = d1; clk = 1;
	clk = 0; din = d0; clk = 1;
	
	clk = 0; clk = 1;//stop
	clk = 0; clk = 1;//null
	
	for( i = 0; i < 12; i++)
	{
		clk = 0;
		clk = 1;
		if(dout)
			adc_val |= 0x800>>i;
	}
	cs = 1;//slave free
	return (adc_val * (5.0/4096));
	//return adc_val;
}

