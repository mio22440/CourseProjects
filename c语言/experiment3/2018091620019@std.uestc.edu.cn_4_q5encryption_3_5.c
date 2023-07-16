#include<stdio.h>

#define NUM_MAX_INPUT 100

int main(void)
{
	char inputarray[NUM_MAX_INPUT]={0};
	char input;
	int i=0;
	int amount=0;
	int shift;
	
	printf("Life was like a box of chocolates, you never know what youre gonna get.\n\n");
	
	printf("Enter message to be encrypted: ");
	while((input=getchar())!='\n'){
		inputarray[i] = input;
		i++;
		amount++;
	}
	
	printf("Enter shift amount (1-25): ");
	scanf("%d",&shift);
	
	for(i=0;i<amount;i++){
		if(inputarray[i]<65||(inputarray[i]>90)&&(inputarray[i]<97)||
			inputarray[i]>122){
			inputarray[i] -= shift;
			continue; 
		}
		if((inputarray[i]+shift>90&&inputarray[i]<=90)){
			inputarray[i] = inputarray[i] - 26;//not 90,the number of alphabet is 26
			continue;
		}
		if((inputarray[i]+shift>122&&inputarray[i]<=122)){
			inputarray[i] = inputarray[i] - 26;
			continue;
		}
		
	}
	
	printf("Encrypted message: ");
	
	for(i=0;i<amount;i++){
		    printf("%c",inputarray[i]+shift);
	}
	
	printf("\n");
	

	
	return 0;
}