#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

int is_num(char c) {
	return c <= '9' && c >= '0';
}

int is_op(char c){
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void error(char *err) {
	printf("err: %s\n", err);
}

void eval(stack *s, char c) {
	if (s->len < 2){error("not enough arguments"); return;}
	int a = stack_pop(s);
	int b = stack_pop(s);
	switch (c) {
		case '+':
			stack_push(s, a + b);
			break;
		case '-':
			stack_push(s, a - b);
			break;
		case '*':
			stack_push(s, a * b);
			break;
		case '/':
			stack_push(s, a / b);
			break;
		default:
			error("unknown symbol");
			break;
	}
}

void read_num(stack *s) {
	char c;
	char *num = (char *) calloc(100, sizeof (char));
	int i = 0;
	while ((c = getchar()) != '\n' && c != EOF && is_num(c) && i < 100) {
		num[i++] = c;
	}
	ungetc(c, stdin);
	if (i == 0) {error("no number");}
	else {
		stack_push(s, (int) strtol(num, NULL, 10));
	}
	free(num);
}

int read(stack *s) {
	char c;
	while ((c = getchar()) != '\n' && c != EOF) {
		if (is_num(c)) {
			ungetc(c, stdin);
			read_num(s);
		} else if (is_op(c)) {
			eval(s, c);
		}
	}
	if (c == EOF) {return 1;}
	else {return 0;}
}

int main () {
	stack *stack = make_stack(100);
	do {
		if (stack->len > 0) {stack_print(stack);}
		printf(": "); // preceeds input
	} while(!read(stack));
	printf("\n");
	free_stack(stack);
}
