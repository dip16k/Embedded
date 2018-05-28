#include<lpc214x.h>

int add(int x, int y)
{
	return x+y;
}
int main()
{
	int i=0,j=2,k=4;
	char a[4];
	int x[4];
	
	if(i>0)
			j = 10;
	else	
			j = 100;	
	for(i=0;i<4;i++)
		k = k+i;
	a[0] = 10;
	a[1] = 20;
	
	x[0] = 0x12;
	
	return j;
}
