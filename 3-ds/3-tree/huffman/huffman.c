#include "linklist.h"

#define N	6

bitnode_st *creat_huffmantree(LinkNode *head);

int main()
{
	DataType userdata[N] = {
		{'A',1},{'B',5},{'C',9},{'D',15},{'E',20},{'F',30}
	};
	LinkNode *list = NULL;
	int i;
	bitnode_st *bitnode = NULL;

	list = creat_empty_linklist();
	for(i = 0; i < N; i ++)
	{
		bitnode = creat_bitree_node(userdata + i);
		insert_linklist(list,bitnode);
	}
	show_linklist(list);
	creat_huffmantree(list);
//	show_linklist(list);
	nuorder_bitree(list->next->lndata);

	return 0;
}

bitnode_st *creat_huffmantree(LinkNode *head)
{
	bitnode_st *root = NULL;
	DataType data;
	LinkNode *tmp = NULL;
	int i;

	while(head->next != NULL && NULL != head->next->next)
	{
		root = creat_bitree_node(&data);
		root->lchild = head->next->lndata;
		root->rchild = head->next->next->lndata;
		root->btdata.weight = root->lchild->btdata.weight + root->rchild->btdata.weight;
		
		for(i = 0; i < 2; i ++)
		{
			tmp = head->next;
			head->next = tmp->next;
			free(tmp);
		}
//		head->next = head->next->next->next;
		
		insert_linklist(head,root);
	}
	return 0;
}
