//2023031703 �輭�� 0327 �ڱ��� �ǽ� 1.c ����
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
//expr�� [0], [1], [2] �̷��� ���پ� �ֱⶫ�� ���������� ��Ÿ���ִ� num�� ������ݴϴ�

//operator�� �����ϴ� stack
precedence stack[MAX_STACK_SIZE]; int top = 0;

//��Ʈ���� �����ϴ� ���� �迭 (infix�� ���⿡ �����Ұ̴ϴ�)
char expr[MAX_EXPR_SIZE][MAX_EXPR_SIZE];

//����� �ɺ��� ��Ʈ�� �����ϴ� �迭�� ������ ���ݴϴ� n�� �ε�������
//get_token�Լ��� �������̸� ������ �´� ������ ��ȯ���ְ� �����ڰ� �ƴ϶�� operand(�ǿ�����)���� ��ȯ���ݴϴ�
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
	// �� ó�� push�� �� top=0�̱� ������ ���� ������ �ϰ� ������ ���ݴϴ�
	stack[++top] = token;
}

//num�� expr�� [0]���� [1]���� ��Ÿ���ִ� �ε����Դϴ�
void postfix(void) {
	int n = 0;
	char symbol=expr[num][n];
	stack[0] = eos;
	//������ symbol�� get_token�Լ����� ��ġ�� �˾Ƽ� �ٲ�ϴ�... n�� ���� �Ű澲���� ���ô�
	int i = 0;
	precedence token;
		for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n)) {
			if (token == operand) printf("%c", symbol);
			// token�� get �ؿӴµ� �ǿ����ڶ�� �ٷιٷ� ����� ���ݴϴ�.
			else if (token == rparen) {
				// rapren�� �ִµ� top ������ lparen�� �ƴ϶�� �����Դϴ�.
				// ������ ��ȣ�� ���� ��ȣ���� ���� �������
				while (stack[top] != lparen) {
					if (top == 0) {
						printf("\n��ȣ ����");
						break;
					}
					//�װ� �ƴ϶�� �׳� �� ���ݴϴ�
					print_token(pop());
				}
				// ������ ��ȣ�� �� ���� �����϶� for���� ���� Ż�������� �ϱ� ������ if���� break�� �� �� �� �ɾ��ݴϴ�
				if (token == rparen && top == 0) break;
				//�ƴϹ� �׳� pop �ϸ� ��ϴ�
				pop();
			}
			// �޾ƿ� ��ū�� �������� ����Դϴ�
			else {
				while (isp[stack[top]] >= icp[token]) {
					print_token(pop());
				}
				push(token);
			}
		}
		//for ���� ���� �� (�� �а� �� �� stack�� �����ִ� ģ������ �� �����ݴϴ�
		while ((token = pop()) != eos) {
			//���� ���� �ȿ� lparen�� �����ִٸ� ���� ��ȣ�� ������ ��ȣ���� ���� ����Դϴ�
			if (token == lparen) {
				printf("\n��ȣ ����");
				//�̹� for���� �� �������״� ���⼭ break�� �� ���� �ɾ��ָ� �˴ϴ�
				break;
			}
			// ���� ��ū�� ������ݽô�
			print_token(token);
		}
		
	}



int main() {
	
	FILE* fp = fopen("infix.txt", "r");
	if (fp == NULL) printf("���� ���� ����");
	int i= 0;
	//expr�� ���������� ���� �������ݽô�
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