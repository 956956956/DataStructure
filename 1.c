//2023031703 김서현 0529 자구응 실습 1.c 제출
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

//실습 유인물에는 element가 아니라 PERSON으로 선언되어 있어 PERSON으로 작성했습니다
typedef struct PERSON {
	char name[10];
	int score;
}PERSON;

void merge(PERSON initList[], PERSON mergedList[], int i, int m, int n);
void mergeSort(PERSON* list, int n);
void mergePass(PERSON initList[], PERSON mergedList[], int n, int s);
int listMerge(PERSON a[], int link[], int start1, int start2);

PERSON* a;

int main() {
	FILE* fp = fopen("in.txt", "r");
	int num = 0; fscanf(fp, "%d\n", &num);
	a = (PERSON*)malloc(sizeof(PERSON) * num);
	for (int i = 0; i < num; i++) {
		fscanf(fp, "%s %d\n", a[i].name, &a[i].score);
	}
	fclose(fp);
	printf("[Iterative merge sort]\n");
	mergeSort(a, num);
	//결과 출력
	for (int i = 0; i < num; i++) {
		printf("%5s %5d\n", a[i].name, a[i].score);
	}

	free(a);
}

void merge(PERSON initList[], PERSON mergedList[], int i, int m, int n) {
	int j, k, t;
	j = m + 1;
	k = i;

	while (i <= m && j <= n) {
		if (initList[i].score >= initList[j].score) {
			mergedList[k++] = initList[i++];
		}
		else {
			mergedList[k++] = initList[j++];
		}
	}
	//나머지를 붙여줍니다
	while (i <= m) mergedList[k++] = initList[i++];
	while (j <= n) mergedList[k++] = initList[j++];
}


void mergeSort(PERSON* list, int n) {
	PERSON* extra = (PERSON*)malloc(sizeof(PERSON) * n );
	int s = 1;
	while (s < n) {
		printf("\ts : %d\n", s);
		mergePass(list, extra, n, s);
		s *= 2;
		mergePass(extra, list, n, s);
		s *= 2;
	}
	free(extra);
}

void mergePass(PERSON initList[], PERSON mergedList[], int n, int s) {
	int i, j;
	for (i = 0; i <= n - 2 * s ; i += 2 * s) {
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	}
	if (i + s < n) merge(initList, mergedList, i, i + s - 1, n-1);
	else {
		for (j = i; j < n; j++) {
			mergedList[j] = initList[j];
		}
	}
}

int listMerge(PERSON a[], int link[], int start1, int start2) {
	int last1, last2, lastResult = 0;
	for (last1 = start1, last2 = start2; last1 && last2;) {
		if (a[last1].score <= a[last2].score) {
			link[lastResult] = last1;
			lastResult = last1; last1 = link[last1];
		}
		else {
			link[lastResult] = last2;
			lastResult = last2; last2 = link[last2];
		}
		if (last1 == 0) link[lastResult] = last2;
		else link[lastResult] = last1;
		return link[0];
	}
}