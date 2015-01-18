
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

stack *make_stack(int n) {
	stack *s = calloc(1, sizeof(stack));
	s->stack = malloc(n * sizeof(int));
	s->size = n;
	return s;
}

void free_stack(stack *s) {
	free(s->stack);
	free(s);
}

int stack_pop(stack *s) {
	s->len--;
	return ((int *) s->stack)[s->len];
}

void stack_push(stack *s, int n) {
	if (s->len >= s->size) {
		size_t size = ((s->size * sizeof(int)) * 2);
		s->stack = realloc(s->stack, size);
		s->size = size;
	}
	((int *) s->stack)[s->len++] = n;
}

void stack_print(stack *s) {
	for (int i = 0; i < s->len; i++) {
		printf("%d, ", ((int *) s->stack)[i]);
	}
	printf("\n");
}
