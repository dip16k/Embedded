#include<lpc214x.h>

int add(int x, int y)
{
	return x+y;
}
int main()
{
	int z = 0;
	
	z = add(10,20);
	
	z =z * 10;
	while(1);
	return 0;
}
