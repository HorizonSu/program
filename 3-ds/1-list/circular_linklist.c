#include <stdio.h>
#include<stdlib.h>

typedef struct _linknode_ {
	int data;
	struct _linknode_ *next;
}linknode_t;

typedef struct _link_list_ {
	int clen;
	int tlen;
	linknode_t *head;
}linklist_st;

linknode_t *create_linknode(int value);
linklist_st *linklist_init(int len);
int linklist_insert(linklist_st *list, int value);
int linklist_show(linklist_st *list);
int linklist_free(linklist_st *list);
int linklist_delete(linklist_st *list, int obj);
int linklist_modify(linklist_st *list, int obj, int value);
int linklist_search(linklist_st *list, int obj);
linknode_t *_linklist_locate_(linklist_st *list, int obj);

int main()
{
	linklist_st *list;
	int value = 100;
	int obj;
	
	list = linklist_init(10);
	while (-1 != linklist_insert(list, value))
		value += 100;
	
	obj = 500;
	if (linklist_search(list, obj))
		printf("%d ok\n", obj);
	else 
		printf("%d error \n", obj);
	linklist_delete(list, 500);
	linklist_modify(list, 1000, 2000);
	
	linklist_show(list);
	linklist_free(list);

	return 0;
}

linklist_st *linklist_init(int len)
{
	linklist_st *list = NULL;

	list = (linklist_st *)malloc(sizeof(linklist_st));
	list->clen = 0;
	list->tlen = len;
	list->head = create_linknode(0);

	return list;
}

int linklist_insert(linklist_st *list, int value)
{
	linknode_t *new = NULL;

	if (list->clen >= list->tlen)
		return -1;

	new = create_linknode(value);
	new->next = list->head->next;
	list->head->next = new;

	list->clen ++;

	return 0;
}

linknode_t *create_linknode(int value)
{
	linknode_t *node = NULL;

	node = (linknode_t *)malloc(sizeof(linknode_t));
	node->data = value;
	node->next = node;

	return node;
}

int linklist_show(linklist_st *list)
{
	int counter = 0;
	linknode_t *p = list->head->next;

	for (counter = 0; counter < list->clen; counter ++) {
		printf("%5d", p->data);
		p = p->next;
	}
	putchar('\n');

	return counter;
}

int linklist_free(linklist_st *list)
{
	linknode_t *p = list->head;
	linknode_t *tmp = NULL;
#if 0
	int counter;
	
	for (counter = 0; counter < list->clen; counter ++) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
#else
	do {
		tmp = p;
		p = p->next;
		free(tmp);	
	} while (p != list->head);
#endif
	free(list);

	return 0;
}

int linklist_delete(linklist_st *list, int obj)
{
	linknode_t *p = NULL;
	linknode_t *tmp = NULL;

	if (NULL == (p = _linklist_locate_(list, obj)))
		return -1;

	tmp = p->next;
	p->next = tmp->next;
	free(tmp);
	list->clen --;

	return 0;
}

int linklist_modify(linklist_st *list, int obj, int value)
{
	linknode_t *p = NULL;

	if (NULL == (p = _linklist_locate_(list, obj)))
		return -1;
	p->next->data = value;

	return 0;
}

int linklist_search(linklist_st *list, int obj)
{
	if (NULL == _linklist_locate_(list, obj))
		return 0;
	return 1;
}

linknode_t *_linklist_locate_(linklist_st *list, int obj)
{
	linknode_t *p = list->head;

	while (list->head != p->next && p->next->data != obj)
		p = p->next;
	if (list->head == p->next)
		return NULL;
	return p;
}
