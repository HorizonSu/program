#include "linklist.h"

LinkNode *creat_linknode(ListData data)
{
	LinkNode *new = NULL;
	
	new = (LinkNode *)malloc(sizeof(LinkNode));
	new->lndata = data;
	new->next = NULL;

	return new;
}

LinkNode *creat_empty_linklist(void)
{
	return creat_linknode(0);
}

int free_linklist(LinkNode *head)
{
	LinkNode *tmp = NULL;
	while(head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return 0;
}

int insert_linklist(LinkNode *head, ListData data)
{
	LinkNode *new = NULL;

	while(NULL != head->next && head->next->lndata->btdata.weight < data->btdata.weight)
		head = head->next;
	new = creat_linknode(data);
	new->next = head->next;
	head->next = new;

	return 0;
}

int show_linklist(LinkNode *head)
{
	while(NULL != head->next)
	{
		printf("%c ",head->next->lndata->btdata.ch);
		printf("[%d]\n",head->next->lndata->btdata.weight);
		head = head->next;
	}
	putchar('\n');
	return 0;
}

#if 0
int modify_linklist(LinkNode *head, int obj, int data)
{
	head  = head->next;
	while(NULL != head && head->data != obj)
		head = head->next;
	if(NULL == head)
		return -1;
	head->data = data;
	return 0;
}

int locat_linklist(LinkNode *head, int data)
{
	int nu = 1;

	head  = head->next;
	while(NULL != head && head->data != data)
	{
		head = head->next;
		nu ++;
	}
	if(NULL == head)
		return -1;
	return nu;
}

int delet_linklist(LinkNode *head, int data)
{
	LinkNode *tmp = NULL;

	while(NULL != head->next && head->next->data != data)
		head = head->next;
	if(NULL == head->next)
		return -1;
	tmp = head->next;
	head->next = tmp->next;
	free(tmp);
	return 0;
}
#endif
