#include<stdio.h>

#define MAX_NUM 30

int main(void)
{
	char input_array[MAX_NUM+1];
	char input;
	int i=0;
	
	printf("Enter a message: "); 
	
	while((input = getchar()) != '\n'){
		input_array[i++] = input;
	}
	
	i--;//¼õ»ØÈ¥ 
	
	printf("Reversal is: ");
	
	for(;i>=0;i--){
	    putchar(input_array[i]);
    } 
	
	printf("\n");
	
	return 0;
	
	 
} 