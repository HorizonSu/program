#ifndef _BITREE_H_
#define _BITREE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct _datatype_ {
	int ch;
	int weight;
	int code;
}DataType;

typedef DataType BitreeData;

typedef struct _bitree_node_ {
	BitreeData btdata;
	struct _bitree_node_ *lchild,
						 *rchild;
}bitnode_st;

extern bitnode_st *creat_bitree_node(BitreeData *data);
extern int nuorder_bitree(bitnode_st *root);


#endif
