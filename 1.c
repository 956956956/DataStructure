//2023031703 �輭�� 0429 �ڱ��� �ǽ� 1.c ����
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
	int data;
	treePointer lChild, rChild;
};
treePointer head;

//���� �ڽ� ������ ������ �ڽ� ������ ���ε��� ������̴ٰϴ�..
void CreateLeftNode(treePointer ptr, int data);
void CreateRightNode(treePointer ptr, int data);
void inorder(treePointer ptr);
void postorder(treePointer ptr);
void preorder(treePointer ptr);

int main() {
	int data = 1;
	int temp;
	head = malloc(sizeof(struct node));
	do{
		printf("input data : ");
		scanf("%d", &data);
		head->data = data;
		head->lChild = head->rChild = NULL;
		int ldata = temp * 3, rdata = temp * 4;
		if (data == 0) {
			printf("0�� �����ͷ� ���� ���ѹݺ��� �ʱ����� ó�������� �Ƚ��϶�!\n");
			continue;
		}
		if (data < 0) {
			printf("����\n");
			break;
		}
		CreateLeftNode(head, data * 3);
		CreateRightNode(head, data * 4);
		printf("Inorder : ");
		inorder(head);
		printf("\n");
		printf("Postorder : ");
		postorder(head);
		printf("\n");
		printf("Preorder : ");
		preorder(head);
		printf("\n");
		
	} while (data >= 0);
	free(head);

}

//call by value�� �������� ���� ���� ���������� �ʽ��ϴ�...
void CreateLeftNode(treePointer ptr, int data) {
	if (data > 100) return;
	if (!ptr->lChild) {
		treePointer temp = malloc(sizeof(struct node));
		temp->data = data;
		temp->lChild = temp->rChild = NULL;
		ptr->lChild = temp;
		//���ó�� ������ݴϴ�
		CreateLeftNode(temp, data * 3);  
		CreateRightNode(temp, data * 4); 
	}
}

void CreateRightNode(treePointer ptr, int data) {
	if (data > 100) return;
	//������ �ڽ��� ������� ���� �ʴٸ� ������ ���ݴϴ�
	if (!ptr->rChild) {
		treePointer temp = malloc(sizeof(struct node));
		temp->data = data;
		temp->lChild = temp->rChild = NULL;
		ptr->rChild = temp;
		CreateLeftNode(temp, data * 3);   // ��������� ���� �ڽ��� �߰�
		CreateRightNode(temp, data * 4);  // ��������� ������ �ڽ��� �߰�
	}
}



void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->lChild);
		printf("%d ", ptr->data);
		inorder(ptr->rChild);
	}
}

void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->lChild);
		postorder(ptr->rChild);
		printf("%d ", ptr->data);
	}
}

void preorder(treePointer ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->lChild);
		preorder(ptr->rChild);
	}
}