#include <stdio.h>
#include <stdlib.h>

int is_num(char c) {
	return c <= '9' && c >= '0';
}

int is_op(char c){
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
	stack *s = calloc(1, sizeof(stack));
	s->stack = malloc(n * sizeof(int));
	s->size = n;
	return s;
}

void destroy_stack(stack *s) {
	free(s->stack);
	free(s);
}

void print_stack(stack *s) {
	for (int i = 0; i < s->len; i++) {
		printf("%d, ", ((int *) s->stack)[i]);
	}
	printf("\n");
}

void push(stack *s, int n) {
	if (s->len >= s->size) {
		size_t size = ((s->size * sizeof(int)) * 2);
		s->stack = realloc(s->stack, size);
		s->size = size;
	}
	((int *) s->stack)[s->len++] = n;
}

int pop(stack *s) {
	s->len--;
	return ((int *) s->stack)[s->len];
}

void eval(stack *s, char c) {
	if (s->len < 2){error("not enough arguments"); return;}
	int a = pop(s);
	int b = pop(s);
	switch (c) {
		case '+':
			push(s, a + b);
			break;
		case '-':
			push(s, a - b);
			break;
		case '*':
			push(s, a * b);
			break;
		case '/':
			push(s, a / b);
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
	while ((c = getchar()) != '\n' && c != EOF && is_num(c)) {
		num[i++] = c;
	}
	ungetc(c, stdin);
	if (i == 0) {error("no number");}
	else {
		push(s, (int) strtol(num, NULL, 10));
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
	if (c == EOF) {return 0;}
	else {return 1;}
}

int main () {
	stack *stack = make_stack(100);
	do {
		if (stack->len > 0) {print_stack(stack);}
		printf(": "); // preceeds input
	} while(read(stack));
	printf("\n");
	destroy_stack(stack);
}