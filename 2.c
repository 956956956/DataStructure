//2023031703 김서현 0529 자구응 실습 2.c 제출
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct PERSON {
    char name[10];
    int score;
}PERSON;

int listMerge(PERSON a[], int link[], int start1, int start2);
int rmergeSort(PERSON a[], int link[], int left, int right);

PERSON* a;

int main() {
    FILE* fp = fopen("in.txt", "r");
    int num = 0; fscanf(fp, "%d\n", &num);
    a = malloc(sizeof(PERSON) * (num+1));
    for (int i = 1; i <= num; i++) {
        fscanf(fp, "%s %d\n", a[i].name, &a[i].score);
    }

    //링크를 포인터로 받고 동적할당하고 초깃값을 지정 안 해주니까 오류나서 초깃값을 지정해줍니당...(이유는 모르겟음)
    int* link = malloc(sizeof(int) * (num + 1));
    for (int i = 1; i <= num; i++) {
        link[i] = 0;
    }

    int start = rmergeSort(a, link, 1, num);
    
    //결과 출력
    printf("[Recursive merge sort]\n");
    for (int i=0; i<num; i++) {
        printf("%5s %5d\n", a[start].name, a[start].score);
        start = link[start];
    }

    fclose(fp);
    free(a);
    free(link);
}

int listMerge(PERSON a[], int link[], int start1, int start2) {
    int last1, last2, lastResult = 0;
    for (last1 = start1, last2 = start2; last1 && last2;) {
        //나머지는 강의자료와 동일하고, 부등호 방향만 바꿔줬습니다
        if (a[last1].score >= a[last2].score) {
            link[lastResult] = last1;
            lastResult = last1; last1 = link[last1];
        }
        else {
            link[lastResult] = last2;
            lastResult = last2; last2 = link[last2];
        }
    }
    if (last1 == 0) link[lastResult] = last2;
    else link[lastResult] = last1;
    return link[0];
}

int rmergeSort(PERSON a[], int link[], int left, int right) {
    if (left >= right) return left;
    int mid = (left + right) / 2;
    return listMerge(a, link, rmergeSort(a, link, left, mid), rmergeSort(a, link, mid + 1, right));
}
