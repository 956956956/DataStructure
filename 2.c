// 2023031703 �輭�� 0408 �ڱ��� �ǽ� 2.c ����
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

	printf("[�������� ����]\n");
	printList(list);
	fclose(fp);
	
	int del = 0;
	while (del != -1) {
		printf("������ ��� ��ȣ : ");
		scanf("%d", &del);
		if (del == -1) {
			printf("����\n"); return 0;
		}
		if (deleteNode(&list, del) == 0) {
			printf("%d�� ����Ʈ�� ����\n", del);
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
		//������� ��
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

// ������ ��(data)�� ���ڷ� �޾� �ش� ���� ���� ��带 ã�� �����մϴ�.
// ������ �����ϸ� 1��, �����ϸ�(��, ���� ����Ʈ�� ������) 0�� ��ȯ�մϴ�.
int deleteNode(listPointer* head, int data) {
	listPointer temp = *head, prev = NULL;

	// �� ����Ʈ�� ���
	if (temp == NULL) return 0;

	// ������ ��尡 ù ��° ����� ���
	if (temp != NULL && temp->data == data) {
		*head = temp->link; // ��带 ���� ���� ����
		free(temp); // ù ��° ��� �޸� ����
		return 1;
	}

	// data�� ã�Ƽ� �����ϱ�
	while (temp != NULL && temp->data != data) {
		prev = temp;
		temp = temp->link;
	}

	// ����Ʈ ������ Ž�������� data�� ã�� ���� ���
	if (temp == NULL) return 0;

	// data�� �ִ� ��带 ã�Ҵٸ� ���� ó��
	prev->link = temp->link; // ���� ����� ��ũ�� ������ ����� ���� ���� ����
	free(temp); // �޸� ����

	return 1; // ���������� ������
}


void printList(listPointer first) {
	for (; first; first = first->link) {
		printf("%4d", first->data);
	}
	printf("\n");
}