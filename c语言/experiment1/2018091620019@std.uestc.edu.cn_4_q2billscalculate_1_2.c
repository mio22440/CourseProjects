/*Enter a mount of money and it will be output with least steps of $20 $10
$5 $1 to pay**************************************************/
#include<stdio.h>

int main(void)
{
	int a,b,c,d,e; 
	
	printf("Enter a dollar amount: \n");
	scanf("%d",&a);
	
	b = a / 20;
	c = (a - 20 * b) / 10;
	d = (a - 20 * b - 10 * c) / 5;
	e = a - 20 * b - 10 * c - d * 5;
	
	printf("$20 bills: %d\n",b);
	printf("$10 bills: %d\n",c);
	printf(" $5 bills: %d\n",d);
	printf(" $1 bills: %d\n",e);
	
	return 0;
	
} 
