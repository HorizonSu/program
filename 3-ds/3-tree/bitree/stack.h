#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>
#include "bitnode.h"

#define STACK_DEBUG	0

typedef btnode_t* stkdata_t;
typedef struct _stack_ {
	stkdata_t *data;
	int tlen;
	int top;
}stack_t;

extern stack_t *stack_init(int len);
extern int stack_destroy(stack_t *stack);
extern int stack_push(stack_t *stack, stkdata_t value);
extern int stack_pop(stack_t *stack, stkdata_t *value);
extern int stack_gettop(stack_t *stack, stkdata_t *value);
extern inline int stack_isfull(stack_t *stack);
extern inline int stack_isempty(stack_t *stack);
#if STACK_DEBUG
extern void _stack_debug_(stack_t *stack);
#endif

#endif /* __STACK_H__ */
