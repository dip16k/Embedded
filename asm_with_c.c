#include<lpc214x.h>

int add(int x, int y)
{
		return x+y;
}
int main()
{
		int a,b,c;
		int x[2];
	
		a = 1; b = 2;
		c = add(a,b);
		x[0] = c;
		c = x[0];
	
	return c;
}
