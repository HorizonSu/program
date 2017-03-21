#include <stdio.h>
#include <stdlib.h>

#define STACK_DEBUG	1

typedef struct _stack_ {
	int *data;
	int tlen;
	int top;
}stack_t;

stack_t *stack_init(int len);
int stack_destroy(stack_t *stack);
int stack_push(stack_t *stack, int value);
int stack_pop(stack_t *stack, int *value);
int stack_gettop(stack_t *stack, int *value);
inline int stack_isfull(stack_t *stack);
inline int stack_isempty(stack_t *stack);
#if STACK_DEBUG
int _stack_debug_(stack_t *stack);
#endif

int main()
{
	stack_t *stack = NULL;
	int value = 100;
	int i;
	
	stack = stack_init(10);

	while (0 == stack_push(stack, value))
		value += 100;
	if (-1 == stack_gettop(stack, &value))
		puts("stack empty");
	else
		printf("top data: %d\n", value);
#if STACK_DEBUG
	_stack_debug_(stack);
#endif

#if 0
	while (0 == stack_pop(stack, &value))
		printf("%5d", value);
	putchar('\n');
#else
	for (i = 0; i < 5; i ++) {
		stack_pop(stack, &value);
		printf("%5d", value);
	}
	putchar('\n');

	value = 1;
	while (0 == stack_push(stack, value))
		value ++;
#endif

#if STACK_DEBUG
	_stack_debug_(stack);
#endif
	stack_destroy(stack);

	return 0;
}

stack_t *stack_init(int len)
{
	stack_t *stack = NULL;

	stack = (stack_t *)malloc(sizeof(stack_t));
	stack->tlen = len;
	stack->top = 0;
	stack->data = (int *)malloc(sizeof(int) * len);

	return stack;
}

int stack_destroy(stack_t *stack)
{
	free(stack->data);
	free(stack);

	return 0;
}

inline int stack_isfull(stack_t *stack)
{
	if (stack->top >= stack->tlen)
		return 1;
	return 0;
}

inline int stack_isempty(stack_t *stack)
{
	if (stack->top <= 0)
		return 1;
	return 0;
}

int stack_push(stack_t *stack, int value)
{
	if (stack_isfull(stack))
		return -1;
	stack->data[stack->top ++] = value;

	return 0;
}

int stack_pop(stack_t *stack, int *value)
{
	if (stack_isempty(stack))
		return -1;
	*value = stack->data[--stack->top];

	return 0;
}

int stack_gettop(stack_t *stack, int *value)
{
	if (stack_isempty(stack))
		return -1;
	*value = stack->data[stack->top - 1];
	return 0;
}

#if STACK_DEBUG
int _stack_debug_(stack_t *stack)
{
	int index;
	
	printf("tlen: %d\tTop: %d\n", stack->tlen, stack->top);
	for (index = 0; index < stack->tlen; index ++)
		printf("%5d", stack->data[index]);
	putchar('\n');

	return 0;
}
#endif
