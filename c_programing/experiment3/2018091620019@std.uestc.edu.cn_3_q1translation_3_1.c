#include<stdio.h>
 
int main(void)
{
	char a;
	printf("Enter phone number: ");
	while((a=getchar())!='\n')
	{
		if(a=='A'||a=='B'||a=='C')
		putchar('2');
		else if(a=='D'||a=='E'||a=='F')
		putchar('3');
		else if(a=='G'||a=='H'||a=='I')
		putchar('4');
		else if(a=='J'||a=='K'||a=='L')
		putchar('5');
		else if(a=='M'||a=='O'||a=='N')
		putchar('6');
		else if(a=='P'||a=='Q'||a=='R'||a=='S')
		putchar('7');
		else if(a=='T'||a=='U'||a=='V')
		putchar('8');
		else if(a=='W'||a=='X'||a=='Y'||a=='Z')
		putchar('9');
		else
		putchar(a);
	}
	
	printf("\n");
	
	return 0;
}
