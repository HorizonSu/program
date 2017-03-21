#include "stack.h"

stack_t *stack_init(int len)
{
	stack_t *stack = NULL;

	stack = malloc(sizeof(stack_t));
	stack->data = malloc(sizeof(*stack->data) * len);
	stack->tlen = len;
	stack->top = 0;

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

int stack_push(stack_t *stack, stkdata_t value)
{
	if (stack_isfull(stack))
		return -1;
	stack->data[stack->top ++] = value;

	return 0;
}

int stack_pop(stack_t *stack, stkdata_t *value)
{
	if (stack_isempty(stack))
		return -1;
	*value = stack->data[--stack->top];

	return 0;
}

int stack_gettop(stack_t *stack, stkdata_t *value)
{
	if (stack_isempty(stack))
		return -1;
	*value = stack->data[stack->top - 1];
	return 0;
}

#if STACK_DEBUG
void _stack_debug_(stack_t *stack)
{
	int index;
	
	printf("tlen: %d\tTop: %d\n", stack->tlen, stack->top);
	for (index = 0; index < stack->tlen; index ++)
		printf("%5d", stack->data[index]);
	putchar('\n');

	return ;
}
#endif
