#include "stack.h"

stack_st *stack_init(int capability)
{
	stack_st *stack = NULL;

	stack = (stack_st *)malloc(sizeof(stack_st));
	stack->total = capability;
	stack->current = 0;
	stack->top = NULL;

	return stack;
}

int stack_free(stack_st *stack)
{
	stknode_st *p = stack->top;
	stknode_st *tmp = NULL;
	
	while (NULL != p) {
		tmp = p;
		p = tmp->next;
		free(tmp);
	}
	free(stack);

	return 0;
}

int stack_push(stack_st *stack, int value)
{
	stknode_st *node = NULL;

	if (stack_isfull(stack))
		return -1;

	node = create_stknode(value);
	node->next = stack->top;
	stack->top = node;

	stack->current ++;

	return 0;
}

int stack_pop(stack_st *stack, int *buff)
{
	stknode_st *tmp = NULL;
	
	if (stack_isempty(stack))
		return -1;
	
	*buff = stack->top->data;
	stack->current --;

	tmp = stack->top;
	stack->top = tmp->next;
	free(tmp);

	return 0;
}

int stack_gettop(stack_st *stack, int *buff)
{
	if (stack_isempty(stack))
		return -1;

	*buff = stack->top->data;

	return 0;
}

int stack_isfull(stack_st *stack)
{
	if (stack->current >= stack->total)
		return 1;
	return 0;
}

int stack_isempty(stack_st *stack)
{
	if (NULL == stack->top)
		return 1;
	return 0;
}

stknode_st *create_stknode(int value)
{
	stknode_st *node = NULL;

	node = (stknode_st *)malloc(sizeof(stknode_st));
	node->data = value;
	node->next = NULL;

	return node;
}

#if DEBUG
void _stack_debug_(stack_st *stack)
{
	stknode_st *p = stack->top;
	
	puts("--------------------  DEBUG  ----------------------");
	printf("Total: %d\tCurrent: %d\n", stack->total, stack->current);
	while (NULL != p) {
		printf("%5d", p->data);
		p = p->next;
	}
	puts("\n--------------------------------------------------");
	return ;
}
#endif
