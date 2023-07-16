/*******************************************
有一组数据无法正常检测 


**********************************************/
#include<stdio.h>

#define STACK_SIZE 100
#define TRUE 1
#define FALSE 0

typedef int Bool;

//函数声明 
void make_empty(void); 
Bool is_empty(void);
Bool is_full(void);
void push(char i);
char pop(void);
void stack_overflow(void);
void stack_underflow(void);

//变量声明 
char contents[STACK_SIZE];
int top = 0;
int num_overflow = 0;
 
//函数定义 
void make_empty(void)
{
	top = 0;
} 

Bool is_empty(void)
{
	return top == 0;
}

Bool is_full(void)
{
	return top == STACK_SIZE;
}

void push(char i)
{
	if(is_full())
	   stack_overflow();
    else
       contents[top++] = i;
}

char pop(void)
{
	if(is_empty())
	   stack_underflow();
    else
       return contents[--top];
}

void stack_overflow(void)
{
	printf("--Overflow, can not push--\n");
	num_overflow++;
}

void stack_underflow(void)
{
	//printf("--Underfolw, can not pop--");
}

//主函数定义 
int main(void)
{
	char a;
	int count;
	int modify; 
	make_empty();
	printf("Enter parentheses and/or braces: ");
	
	while((a = getchar())!= '\n'){
		
		if(a == '{'||a == '('){          
			                             
			push(a);                      
		}
		if('}' == a){
			if(pop() == '{')
			   continue;
            else{
            	modify++;
            	break;
            }
               
		}
		if(')' == a){
			if(pop() == '(')
			   continue;
            else{
            	modify++;
            	break;
            }
               
			
		}
		
	} 
	
	if(0 == top && num_overflow == 0 && modify == 0)
		printf("Parentheses/braces are nested properly\n");
	else
	    printf("Parentheses/braces are NOT nested properly\n");
}