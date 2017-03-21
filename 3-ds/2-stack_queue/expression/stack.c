#include "stack.h"

#if DEBUG
void _debug_seqstack_(SeqStack *stack)
{
	int i;
	
	puts("debug:");
	for(i = 0; i < stack->len; i ++)
		printf("%c[%d] ", stack->data[i], stack->data[i]);
	putchar('\n');
}
#endif

SeqStack *creat_seqstack(int len)
{
	SeqStack *stack = NULL;

	stack = (SeqStack *)malloc(sizeof(SeqStack));
	stack->data = (int *)malloc(sizeof(int) * len);
	stack->top = -1;
	stack->len = len;

	return stack;
}

int isfull_seqstack(SeqStack *stack)
{
	return stack->top >= stack->len - 1;
}

int isempty_seqstack(SeqStack *stack)
{
	return stack->top < 0;
}

int push_seqstack(SeqStack *stack, int value)
{
	if(isfull_seqstack(stack))
		return -1;
	stack->data[++ stack->top] = value;
	return 0;
}

int pop_seqstack(SeqStack *stack, int *dest)
{
	if(isempty_seqstack(stack))
		return -1;
	*dest = stack->data[stack->top --];
	return 0;
}

int free_seqstack(SeqStack *stack)
{
	free(stack->data);
	free(stack);

	return 0;
}

int gettop_seqstack(SeqStack *stack, int *dest)
{
	if(isempty_seqstack(stack))
		return -1;
	*dest = stack->data[stack->top];
	return 0;
}
