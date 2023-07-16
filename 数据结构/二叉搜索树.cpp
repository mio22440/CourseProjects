#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>


typedef struct Node {
	int key;
	struct Node* parent;
	//ע������Ľڵ�������ڵ�ָ�� 
	struct Node *lchild, *rchild; 
}Node;

//��������
Node* createNode(int key);
Node* insert(Node* &root, int key);
Node* minimum(Node* root);
Node* begin(Node* root);
Node* next(Node* current);
Node* end(Node* root);



	Node* createNode(int key) {
		Node* temp = (Node*)malloc(sizeof(Node));  
		temp->key = key;
		temp->lchild = temp->rchild = temp->parent = NULL; 
		return temp;
	}

	//�����в���һ���ڵ� 
	Node* insert(Node* &root, int key) {  
		//TODO
	}

	//����������Сֵ�ڵ��λ�� 
	Node* minimum(Node* root) {  
		//TODO
	}

	//���ظ����������������ʼ�ڵ��λ�� 
	Node* begin(Node* root) {  
		return minimum(root); 
	}

//����������������иýڵ����һ���ڵ��λ�� //����ýڵ��Ѿ������е����һ���ڵ㣬�򷵻�NULL 
	Node* next(Node* current) {    
		//TODO
	}

//�������������һ���ڵ����һ���ڵ��λ�ã�Ҳ����NULL
	Node* end(Node* root) {   
		return NULL; 
	}

	int main() {
		Node* root = NULL; //һ�ÿ���  
		int N;  
		scanf("%d", &N);  
		for (int i = 0; i < N; i++) {  
			int x;      
			scanf("%d", &x);   
			insert(root, x); 
		}
//����һ���������   
		for (Node* p = begin(root); p != end(root);p = next(p)) { 
			printf("%d ", p->key); 
		}    printf("\n"); 
		return 0;
	}
