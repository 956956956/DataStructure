//2023031703 김서현 0327 자구응 실습 1.c 제출
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum{lparen, rparen,
	plus, minus, times, divide, mod,
	eos, operand}precedence;

static int isp[] = { 0,19,12,12,13,13,13,0 };
static int icp[] = { 20,19,12,12,13,13,13,0 };

int num = 0;
//expr이 [0], [1], [2] 이렇게 한줄씩 있기땜에 한줄한줄을 나타내주는 num을 사용해줍니더

//operator를 저장하는 stack
precedence stack[MAX_STACK_SIZE]; int top = 0;

//스트링을 저장하는 문자 배열 (infix를 여기에 저장할겁니당)
char expr[MAX_EXPR_SIZE][MAX_EXPR_SIZE];

//날라온 심볼은 스트링 저장하는 배열에 저장을 해줍니당 n은 인덱스구요
//get_token함수는 연산자이면 각각에 맞는 연산을 반환해주고 연산자가 아니라면 operand(피연산자)임을 반환해줍니다
precedence get_token(char* symbol, int* n) {
	*symbol = expr[num][(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0' : return eos;
	default: return operand;
	}

}


void print_token(precedence token) {
	switch (token) {
	case plus: printf("+"); break;
	case minus: printf("-"); break;
	case times: printf("*"); break;
	case divide: printf("/"); break;
	case mod: printf("%%"); break;
	default: break;
	}
}

int pop() {
	if (top > 0) return stack[top--];
	else return eos;
}

void push(precedence token) {
	// 맨 처음 push할 때 top=0이기 때문에 전위 연산을 하고 저장을 해줍니다
	stack[++top] = token;
}

//num은 expr의 [0]인지 [1]인지 나타내주는 인덱스입니당
void postfix(void) {
	int n = 0;
	char symbol=expr[num][n];
	stack[0] = eos;
	//어차피 symbol은 get_token함수에서 위치가 알아서 바뀝니다... n을 굳이 신경쓰지는 맙시당
	int i = 0;
	precedence token;
		for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n)) {
			if (token == operand) printf("%c", symbol);
			// token을 get 해왓는데 피연산자라면 바로바로 출력을 해줍니다.
			else if (token == rparen) {
				// rapren이 있는데 top 스택이 lparen이 아니라면 오류입니당.
				// 오른쪽 괄호가 왼쪽 괄호보다 많은 경우이죠
				while (stack[top] != lparen) {
					if (top == 0) {
						printf("\n괄호 오류");
						break;
					}
					//그게 아니라면 그냥 팝 해줍니다
					print_token(pop());
				}
				// 오른쪽 괄호가 더 많은 오류일때 for문을 완전 탈출해조야 하기 때문에 if문과 break를 한 번 더 걸어줍니다
				if (token == rparen && top == 0) break;
				//아니묜 그냥 pop 하면 댑니다
				pop();
			}
			// 받아온 토큰이 연산자일 경우입니다
			else {
				while (isp[stack[top]] >= icp[token]) {
					print_token(pop());
				}
				push(token);
			}
		}
		//for 문이 끝난 후 (다 읽고 난 뒤 stack에 남아있는 친구들을 다 꺼내줍니다
		while ((token = pop()) != eos) {
			//만약 스택 안에 lparen이 남아있다면 왼쪽 괄호가 오른쪽 괄호보다 많은 경우입니다
			if (token == lparen) {
				printf("\n괄호 오류");
				//이미 for문을 다 돌았을테니 여기서 break는 한 번만 걸어주면 됩니당
				break;
			}
			// 팝한 토큰을 출력해줍시당
			print_token(token);
		}
		
	}



int main() {
	
	FILE* fp = fopen("infix.txt", "r");
	if (fp == NULL) printf("파일 열기 실패");
	int i= 0;
	//expr에 한줄한줄을 각각 저장해줍시당
	while (fgets(expr[i], MAX_EXPR_SIZE, fp) != NULL) {
		expr[i][strlen(expr[i]) - 1] = '\0';
		i++;
		
	}
	

	for (int j = 0; j < i; j++) {
		printf("Infix : %s\n", expr[j]);
		printf("Postfix : ");
		postfix();
		printf("\n\n");
		num++;
	}
}