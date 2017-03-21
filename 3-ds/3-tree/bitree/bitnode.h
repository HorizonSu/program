#ifndef __BITNODE_H__
#define __BITNODE_H__

typedef int btdata_t;
typedef struct _bitnode_ {
	btdata_t data;
	struct _bitnode_ *lchild;
	struct _bitnode_ *rchild;
}btnode_t;

#endif /* __BITNODE_H__ */
