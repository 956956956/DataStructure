//2023031703 �輭�� �ڷᱸ������ 2.c
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main() {
	//������ �����ݴϴ�
	FILE* fp1 = fopen("in1.txt", "r");
	FILE* fp2 = fopen("in2.txt", "r");

	int n1, n2;
	//�� ó�� ���� �������ݴϴ�
	fscanf(fp1, "%d", &n1);
	fscanf(fp2, "%d", &n2);
	//fp1�� fp2�� ������ ���� ������ �� ���� ���ѹݺ� �����ݴϴ�
	while (!feof(fp1) && !feof(fp2)) {
		if (n1 > n2) {
			//n1>n2��� fp1�� ���� ���� �޾��ݴϴ�
			fscanf(fp1, "%d", &n1);
		}
		if (n1 < n2) {
			//n2>n1�̶�� fp2�� ���� ���� �޾��ݴϴ�
			fscanf(fp2, "%d", &n2);
		}
		if (n1 == n2) {
			//���� ���̶�� ����ϰ� �� ���� �� ���� ���� �޾��ݴϴ�
			printf("%d ", n1);
			fscanf(fp1, "%d", &n1);
			fscanf(fp2, "%d", &n2);
		}
	}
	//������ �ݾ��ݴϴ�
	fclose(fp1);
	fclose(fp2);
}