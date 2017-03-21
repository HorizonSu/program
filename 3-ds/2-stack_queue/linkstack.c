#include <stdio.h>
#include <stdlib.h>

#define STACK_DEBUG 1

typedef struct _stknode_ {
	int data;
	struct _stknode_ *next;
}stknode_t;

typedef struct _linkstack_{
	stknode_t *top;
	int tlen;
	int clen;
}stack_t;

stack_t *stack_init(int capability);
int stack_destroy(stack_t *stack);
int stack_push(stack_t *stack, int value);
int stack_pop(stack_t *stack, int *value);
int stack_isfull(stack_t *stack);
int stack_isempty(stack_t *stack);
stknode_t *create_stknode(int value);
int stack_gettop(stack_t *stack, int *value);
#if STACK_DEBUG
void _stack_debug_(stack_t *stack);
#endif

int main()
{
	stack_t *stack = NULL;
	int value = 100;
	
	stack = stack_init(10);
	
	while (-1 != stack_push(stack, value))
		value += 100;

	if (0 == stack_gettop(stack, &value))
		printf("topvalue: %d\n", value);

#if STACK_DEBUG
	_stack_debug_(stack);
#endif
	
	while (-1 != stack_pop(stack, &value))
		printf("%5d", value);
	putchar('\n');

#if STACK_DEBUG
	_stack_debug_(stack);
#endif

	stack_destroy(stack);
	return 0;
}

stack_t *stack_init(int capability)
{
	stack_t *stack = NULL;

	stack = (stack_t *)malloc(sizeof(stack_t));
	stack->tlen = capability;
	stack->clen = 0;
	stack->top = NULL;

	return stack;
}

int stack_destroy(stack_t *stack)
{
	stknode_t *p = stack->top;
	stknode_t *tmp = NULL;
	
	while (NULL != p) {
		tmp = p;
		p = tmp->next;
		free(tmp);
	}
	free(stack);

	return 0;
}

int stack_push(stack_t *stack, int value)
{
	stknode_t *node = NULL;

	if (stack_isfull(stack))
		return -1;

	node = create_stknode(value);
	node->next = stack->top;
	stack->top = node;

	stack->clen ++;

	return 0;
}

int stack_pop(stack_t *stack, int *value)
{
	stknode_t *tmp = NULL;
	
	if (stack_isempty(stack))
		return -1;
	
	*value = stack->top->data;
	stack->clen --;

	tmp = stack->top;
	stack->top = tmp->next;
	free(tmp);

	return 0;
}

int stack_gettop(stack_t *stack, int *value)
{
	if (stack_isempty(stack))
		return -1;

	*value = stack->top->data;

	return 0;
}

int stack_isfull(stack_t *stack)
{
	if (stack->clen >= stack->tlen)
		return 1;
	return 0;
}

int stack_isempty(stack_t *stack)
{
	if (NULL == stack->top)
		return 1;
	return 0;
}

stknode_t *create_stknode(int value)
{
	stknode_t *node = NULL;

	node = (stknode_t *)malloc(sizeof(stknode_t));
	node->data = value;
	node->next = NULL;

	return node;
}

#if STACK_DEBUG
void _stack_debug_(stack_t *stack)
{
	stknode_t *p = stack->top;
	
	puts("--------------------  STACK_DEBUG  ----------------------");
	printf("tlen: %d\tclen: %d\n", stack->tlen, stack->clen);
	while (NULL != p) {
		printf("%5d", p->data);
		p = p->next;
	}
	puts("\n--------------------------------------------------");
	return ;
}
#endif
