#include <stdio.h>
#include <stdlib.h>

int isNum(char c) {
	return c <= '9' && c >= '0';
}

int isOp(char c){
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void error(char *err) {
	printf("err: %s\n", err);
}

typedef struct {
	void *stack;
	int len;
	int size;
} stack;

stack *make_stack(int n) {
	stack *stack = calloc(1, sizeof(stack));
	stack->stack = malloc(n * sizeof(int));
	return stack;
}

void print_stack(stack *stack) {
	for (int i = 0; i < stack->len; i++) {
		printf("%d, ", ((int *) stack->stack)[i]);
	}
	printf("\n");
}

void push(stack *stack, int n) {
	((int *) stack->stack)[stack->len++] = n;
}

int pop(stack *stack) {
	stack->len--;
	return ((int *) stack->stack)[stack->len];
}

void eval(stack *stack, char c) {
	int a = pop(stack);
	int b = pop(stack);
	switch (c) {
		case '+':
			push(stack, a + b);
			break;
		case '-':
			push(stack, a - b);
			break;
		case '*':
			push(stack, a * b);
			break;
		case '/':
			push(stack, a / b);
			break;
		default:
			error("unknown symbol");
			break;
	}
}

void readNum(stack *stack) {
	char c;
	char *num = (char *) malloc(100 * sizeof (char));
	int i = 0;
	while ((c = getchar()) != EOF && isNum(c)) {
		num[i++] = c;
	}
	num[i] = '\0';
	if (i == 0) {error("no number");}
	else {
		push(stack, atoi(num));}
}

void read(stack *stack) {
	char c;
	while ((c = getchar()) != EOF) {
		if (isNum(c)) {
			ungetc(c, stdin);
			readNum(stack);
		} else if (isOp(c)) {
			eval(stack, c);
		}
	}
}

int main () {
	stack *stack = make_stack(100);
	read(stack);
	print_stack(stack);
}