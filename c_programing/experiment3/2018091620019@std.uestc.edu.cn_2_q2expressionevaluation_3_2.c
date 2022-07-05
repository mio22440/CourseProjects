#include<stdio.h>

int main(void)
{
	char caculate;
	int count=1;
	float input;
	float result;
	float test;	
	
	printf("Enter an expression: ");
	
	scanf("%f",&result);
	
	do{

		if(1==count){
			caculate = getchar();//putchar(caculate);//This is for testing
			count = 2;
		//	continue;//This is a wrong try...
			if('\n'==caculate){
				break;
			}
        }
		if(2==count){
			scanf("%f",&input);
			
			if('+'==caculate){
				result += input;
			}
			else if('-'==caculate){
				result -= input;
			}
			else if('*'==caculate){
				result *= input;
			}
			else if('/'==caculate){
				result /= input; 
			}
			else{
				printf("Illigal input");
				break;
			}
			count =1;
		}

			

		}while(1);
		
    test = (int)result;
    
    if(test==result){
        printf("Value of expression: %.0f\n",result);
    }
	else{
        printf("Value of expression: %.1f\n",result);//Value is equal to result
	}	

		
	return 0;		
     
} 