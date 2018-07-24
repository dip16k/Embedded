#include <REG51.h>
typedef unsigned int u16;

#include "i2c.h"
#include "lcd.h"
#include "spi.h"

int main()
{
	u8 val;
	float f;
	
	LcdInit();
	
	DisplayString("Hello World");
	
	i2c_device_write(0xd0,0x00,'A');
	
	delay_ms(10);
	
	val = i2c_device_read(0xd0, 0x00);
	
	DisplayCmd(line2);
	
	DisplayData(val);
	
	f = read_adc(1);
	DisplayCmd(0xca);
	Displayfnum(f*100);

	while(1){
	f = read_adc(1);
	DisplayCmd(0xca);
	Displayfnum(f*100);
		delay_ms(100);
	}
	return 0;
}