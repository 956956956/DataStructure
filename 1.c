//2023031703 김서현 0429 자구응 실습 1.c 제출
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
	int data;
	treePointer lChild, rChild;
};
treePointer head;

//왼쪽 자식 생성과 오른쪽 자식 생성을 따로따로 만들어줄겁니당..
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
			printf("0인 데이터로 인한 무한반복은 너굴맨이 처리했으니 안심하라구!\n");
			continue;
		}
		if (data < 0) {
			printf("종료\n");
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

//call by value로 포인터의 값을 직접 수정하지는 않습니다...
void CreateLeftNode(treePointer ptr, int data) {
	if (data > 100) return;
	if (!ptr->lChild) {
		treePointer temp = malloc(sizeof(struct node));
		temp->data = data;
		temp->lChild = temp->rChild = NULL;
		ptr->lChild = temp;
		//재귀처럼 사용해줍니당
		CreateLeftNode(temp, data * 3);  
		CreateRightNode(temp, data * 4); 
	}
}

void CreateRightNode(treePointer ptr, int data) {
	if (data > 100) return;
	//오른쪽 자식이 만들어져 있지 않다면 생성을 해줍니당
	if (!ptr->rChild) {
		treePointer temp = malloc(sizeof(struct node));
		temp->data = data;
		temp->lChild = temp->rChild = NULL;
		ptr->rChild = temp;
		CreateLeftNode(temp, data * 3);   // 재귀적으로 왼쪽 자식을 추가
		CreateRightNode(temp, data * 4);  // 재귀적으로 오른쪽 자식을 추가
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