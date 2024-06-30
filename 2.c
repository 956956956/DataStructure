//2023031703 김서현 자료구조응용 2.c
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main() {
	//파일을 열어줍니다
	FILE* fp1 = fopen("in1.txt", "r");
	FILE* fp2 = fopen("in2.txt", "r");

	int n1, n2;
	//맨 처음 값을 지정해줍니다
	fscanf(fp1, "%d", &n1);
	fscanf(fp2, "%d", &n2);
	//fp1과 fp2가 파일의 끝에 도달할 때 까지 무한반복 돌려줍니다
	while (!feof(fp1) && !feof(fp2)) {
		if (n1 > n2) {
			//n1>n2라면 fp1만 다음 값을 받아줍니다
			fscanf(fp1, "%d", &n1);
		}
		if (n1 < n2) {
			//n2>n1이라면 fp2만 다음 값을 받아줍니다
			fscanf(fp2, "%d", &n2);
		}
		if (n1 == n2) {
			//같은 값이라면 출력하고 두 파일 다 다음 값을 받아줍니다
			printf("%d ", n1);
			fscanf(fp1, "%d", &n1);
			fscanf(fp2, "%d", &n2);
		}
	}
	//파일을 닫아줍니다
	fclose(fp1);
	fclose(fp2);
}