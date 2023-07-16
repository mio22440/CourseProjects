#include<stdio.h>

    int main(void)
    {
        float a;
        
        printf("Enter an amount: ");
        scanf("%f",&a);
        
        a = a * 1.05;
        
        printf("With tax added: $%.2f\n",a);
        
        return 0;
    } 

