#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include "bitree.h"

typedef bitnode_st* ListData;

typedef struct _linknode_ {
	ListData lndata;
	struct _linknode_ *next;
}LinkNode;

extern LinkNode *creat_linknode(ListData data);
extern LinkNode *creat_empty_linklist(void);
extern int insert_linklist(LinkNode *head, ListData data);
extern int show_linklist(LinkNode *head);
extern int free_linklist(LinkNode *head);

#endif
