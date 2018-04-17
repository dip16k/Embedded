/*
 * usart_test.c
 *
 * Created: 18-05-2015 23:36:30
 *  Author: Dip
 */ 

#define F_CPU 1000000 	//1 mhz

#include <avr/io.h>
#include <util/delay.h>

#define BAUDRATE 9600
#define BAUDRATE_PRESCALE (((F_CPU)/(16UL*BAUDRATE))-1)	//USART BAUDRATE

void usart_init()
{
	UCSRB |=(1<<RXEN)|(1<<TXEN);
	UCSRC |=(1<<USBS)|(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	
	//SETTING 8BIT MODE
	UBRRL=BAUDRATE_PRESCALE;
	UBRRH=BAUDRATE_PRESCALE>>8;	//LOAD HIGHER VALUE TO UBRRH REGISTER
}

unsigned char usart_getchar()// receiving DATA from PC
{
	while ((UCSRA&(1<<RXC))==0)// monitoring RXC flag value
	{// waiting for reception when it receive a byte RXC flag go high and condition fail
	}
	return UDR;//UART DATA REGISTER now UDR contain the received value(from PC) and return to program
}// read from UDR

void usart_puchar(unsigned char send)// sending DATA to PC
{
	while (!(UCSRA & (1<<UDRE)))// CHECK FOR if UDR is empty or not
	{	// if UDRE=1 data loaded bit goes high this condition fail
	}
	UDR = send;// write data to UDR
}

int main(void)
{
	DDRA=0xff;
	DDRC = 0xff;
	
	unsigned char val = 0;
	usart_init();//initializing UART
    while(1)
    {
        val = usart_getchar();//receive data from PC
		usart_puchar(val); //reply back to PC 
		if (val == '1')
		{
			PORTC = 0x01;
			_delay_ms(200);
			PORTC = 0x00;
		}
    }
}