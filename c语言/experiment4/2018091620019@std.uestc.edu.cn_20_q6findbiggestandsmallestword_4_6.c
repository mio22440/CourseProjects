#include<stdio.h>
#include<string.h>

#define MAX_LEN 20

int read_line(char str[], int n);//���뵥�� 

int main(void)
{
	char smallest_word[MAX_LEN+1]={'\0'}, largest_word[MAX_LEN+1]={'\0'};//���������/��С���� 
	char input[MAX_LEN+1]={'\0'};//����������ĵ��� 
	char temp_word[MAX_LEN+1]={'\0'};//�����滻��һ�������С���ʣ���Ϊ�м���� 
	int i=0;//���Ƶ�һ�θ�ֵ��smallest_word����ֹif������\0���㲻�� 
	//��������Ҳ����... 
	
	while(1){
		printf("Enter word: ");
		read_line(input,20);
		
				
		if(strlen(input)==0)//Ϊ��ʱ 
		   continue;

		if(i==0){
			strcpy(smallest_word,input);
		} 
		if(strcmp(input,smallest_word)<0){
			strcpy(smallest_word,input);
		}
		if(strcmp(input,largest_word)>0){
			strcpy(largest_word,input);
		}
		
		if(strcmp(smallest_word,largest_word)>0){
			strcpy(temp_word,largest_word);
			strcpy(largest_word,smallest_word);
			strcpy(smallest_word,temp_word);
		} 
		
		if(strlen(input)==4){
			break;
		}
		i++;
		
		if(strlen(input)==0)
		   break;

	} 
	
	printf("\n"); 
	
	printf("Smallest word: ");
	puts(smallest_word);
	
	printf("Largest word: ");
	puts(largest_word);
	
	return 0;
	
}




 int read_line(char str[], int n)
 {
 	int ch, i = 0;
 	
 	while((ch = getchar()) != '\n'){
	 	if(i < n){
	 		str[i++] = ch;
	 	}
	 }
    str[i] = '\0';
    return i;
 }
