#include <reg51.h>
#include "i2c.h"

sbit scl = P3^0;
sbit sda = P3^1;

void delay_ms(unsigned char n)
{
	unsigned int i=0,j=0;
	for(i=0;i<n;i++)
		for(j=0;j<1275;j++);
}

void i2c_start(void)
{
	scl = 0;
	sda = 1;
	scl = 1;
	sda = 0;
}

// both will go same
void i2c_stop(void)
{
	scl = 0;
	sda = 0;
	scl = 1;
	sda = 1;
}

//
void i2c_write(u8 val)
{
	u8 i = 0;
	for (i = 0; i < 8; i++)
	{
		scl = 0;
		sda = (val & (0x80 >> i)) ? 1:0;
		scl = 1;
	}
} 
// data transmission is valid when clock goes low to high
void i2c_ack()
{
	bit t;
	scl = 0;
	sda = 1;
	scl = 1;
	t = sda;
	while (t);
}

void i2c_noack()
{
	scl = 0;
	sda = 1;//remain sda high
	scl = 1;
}

u8 i2c_read()
{
	u8 val, i = 0;
	for (i = 0;i <8; i++)
	{
		scl = 0;
		scl = 1;
		if (sda)
		{
			val |= 0x80>>i; 
		}
	}
	return val;
}

void i2c_device_write(u8 slave, u8 addr, u8 msg)
{
	i2c_start();
	
	i2c_write(slave);
	
	i2c_ack();
	
	i2c_write(addr);
	
	i2c_ack();
	
	i2c_write(msg);
	
	i2c_ack();
	
	i2c_stop();
	
	delay_ms(20);
}

u8 i2c_device_read(u8 slave, u8 addr)
{
	u8 buf;
	
	i2c_start();
	
	i2c_write(slave);
	
	i2c_ack();
	
	i2c_write(addr);
	
	i2c_ack();
	//restart
	i2c_start();
	// now slave address with read option
	i2c_write(slave|1);
	
	i2c_ack();
	
	buf = i2c_read();
	
	i2c_noack();
	
	i2c_stop();
	
	//delay_ms(10);
	
	return buf;
}