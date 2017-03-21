#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>

#define STACK_DEBUG 1

typedef struct _stknode_ {
	int data;
	struct _stknode_ *next;
}stknode_st;

typedef struct _link_stack_{
	int total;
	int current;
	stknode_st *top;
}stack_st;

stack_st *stack_init(int capability);
int stack_free(stack_st *stack);
int stack_push(stack_st *stack, int value);
int stack_pop(stack_st *stack, int *buff);
int stack_isfull(stack_st *stack);
int stack_isempty(stack_st *stack);
stknode_st *create_stknode(int value);
int stack_gettop(stack_st *stack, int *buff);
#if STACK_DEBUG
void _stack_debug_(stack_st *stack);
#endif

#endif /* __STACK_H__ */
