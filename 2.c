// 2023031703 김서현 0408 자구응 실습 2.c 제출
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
};


void append(listPointer* head, int data);
int deleteNode(listPointer* head, int data);
void printList(listPointer first);


int main() {
	int num;
	FILE* fp = fopen("list3.txt", "r");
	fscanf(fp, "%d\n", &num);
	listPointer list = NULL;
	int* templist = (int*)malloc(sizeof(int) * num);

	for (int i = 0; i < num; i++) {
		fscanf(fp, "%d ", &templist[i]);
		append(&list, templist[i]);
	}

	printf("[오름차순 정렬]\n");
	printList(list);
	fclose(fp);
	
	int del = 0;
	while (del != -1) {
		printf("삭제할 노드 번호 : ");
		scanf("%d", &del);
		if (del == -1) {
			printf("종료\n"); return 0;
		}
		if (deleteNode(&list, del) == 0) {
			printf("%d가 리스트에 없음\n", del);
		}
		else {
			printList(list);
		}
	}

}


void append(listPointer *first, int num) {
	listPointer temp, cur, prev;
	temp=(listPointer)malloc(sizeof(struct listNode));
	temp->data = num;
	temp->link = NULL;
	if (*first==NULL) {
		//비어있을 때
		*first = temp;
	}
	else {
		cur = *first;
		prev = NULL;
		while (cur != NULL && cur->data < num) {
			prev = cur;
			cur = cur->link;
		}
		if (prev == NULL) {
			temp->link = *first;
			*first = temp;
		}
		else {
			prev->link = temp;
			temp->link = cur;
		}
	}
}

// 삭제할 값(data)을 인자로 받아 해당 값을 가진 노드를 찾아 삭제합니다.
// 삭제가 성공하면 1을, 실패하면(즉, 값이 리스트에 없으면) 0을 반환합니다.
int deleteNode(listPointer* head, int data) {
	listPointer temp = *head, prev = NULL;

	// 빈 리스트인 경우
	if (temp == NULL) return 0;

	// 삭제할 노드가 첫 번째 노드인 경우
	if (temp != NULL && temp->data == data) {
		*head = temp->link; // 헤드를 다음 노드로 변경
		free(temp); // 첫 번째 노드 메모리 해제
		return 1;
	}

	// data를 찾아서 삭제하기
	while (temp != NULL && temp->data != data) {
		prev = temp;
		temp = temp->link;
	}

	// 리스트 끝까지 탐색했지만 data를 찾지 못한 경우
	if (temp == NULL) return 0;

	// data가 있는 노드를 찾았다면 삭제 처리
	prev->link = temp->link; // 이전 노드의 링크를 삭제할 노드의 다음 노드로 변경
	free(temp); // 메모리 해제

	return 1; // 성공적으로 삭제됨
}


void printList(listPointer first) {
	for (; first; first = first->link) {
		printf("%4d", first->data);
	}
	printf("\n");
}