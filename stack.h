
#ifndef STACK_H_
#define STACK_H_

typedef struct {
	void *stack;
	int len;
	int size;
} stack;

stack *make_stack(int n);
void free_stack(stack *s);
void stack_print(stack *s);
void stack_push(stack *s, int n);
int stack_pop(stack *s);

#endif // STACK_H_
