#include<lpc214x.h>

/*macro definition*/
#define RDR (1<<0)
#define TEMT (1<<6)

void uart0init(void)
{
	// initialize pinselect block for tx and rx
	PINSEL0 = 0x05;
	
	// enable FIFO and reset them
	U0FCR = 0x07;
	
	//set DLAB and word length set to 8 bit
	U0LCR = 0x83;
	
	// baudrate 9600
	U0DLL = 0x5a;
	U0DLM = 0x0;
	
	//clear DLAB
	U0LCR = 0x03;
}

void uart0tx(unsigned char c)
{
	U0THR = c;
	
	// wait till U0THR and U0TSR are both empty
	while(!(U0LSR & TEMT));
}

char uart0rx(void)
{
	//wait till receiver data ready set
	while(!(U0LSR & RDR));
	
	// received data put in UART0 receiver buffer
	return U0RBR;
}
int main()
{
	char buf;
	
	uart0init();
	
	while(1)
	{
		buf = uart0rx();

		uart0tx(buf);
	}
}
