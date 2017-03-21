#include <stdio.h>
#include <stdlib.h>

typedef struct _linknode_ {
	int data;
	struct _linknode_ *next;
}linknode_t;

typedef struct _linklist_ {
	linknode_t *head;
	int clen;
	int tlen;
}linklist_t;

linknode_t *create_linknode(int value);
linklist_t *list_init(int len);
int list_insert(linklist_t *list, int value);
int list_show(linklist_t *list);
int list_destroy(linklist_t *list);
int list_delete(linklist_t *list, int obj);
linknode_t *list_search(linklist_t *list, int obj);
int list_modify(linklist_t *list, int old, int new);
int list_getlen(linklist_t *list);
int list_reverse(linklist_t *list);

int main()
{
	linklist_t *list = NULL;
	int value = 100;
	linknode_t *p = NULL;
	
	list = list_init(10);

	while (0 == list_insert(list, value))
		value += 100;
	list_show(list);

	list_reverse(list);
	list_show(list);

#if 0
	list_delete(list, 300);
	list_show(list);
	
	p = list_search(list, 140);
	if (NULL == p)
		puts("NO !!");
	else
		printf("Find: %d\n", p->data);

	list_modify(list, 101, 3);
	list_show(list);
	
	printf("Clen: %d\n", list_getlen(list));
#endif

	list_destroy(list);

	return 0;
}

linklist_t *list_init(int len)
{
	linklist_t *list = NULL;

	list = malloc(sizeof(linklist_t));
	list->head = create_linknode(0);
	list->clen = 0;
	list->tlen = len;

	return list;
}

int list_insert(linklist_t *list, int value)
{
	linknode_t *new = NULL;
	linknode_t *p = list->head;

	if (list->clen >= list->tlen)
		return -1;

	new = create_linknode(value);
	new->next = p->next;
	p->next = new;

	list->clen++;

	return 0;
}

linknode_t *create_linknode(int value)
{
	linknode_t *node = NULL;

	node = malloc(sizeof(linknode_t));
	node->next = NULL;
	node->data = value;

	return node;
}

int list_show(linklist_t *list)
{
	linknode_t *p = list->head->next;

	while (NULL != p) {
		printf("%5d", p->data);
		p = p->next;
	}
	putchar('\n');

	return 0;
}

int list_destroy(linklist_t *list)
{
	linknode_t *p = list->head;
	linknode_t *tmp = NULL;

	while (NULL != p) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
	free(list);

	return 0;
}

int list_delete(linklist_t *list, int obj)
{
	linknode_t *p = list->head;
	linknode_t *tmp = NULL;

	while (NULL != p->next && p->next->data != obj)
		p = p->next;
	if (NULL == p->next)
		return -1;

	tmp = p->next;
	p->next = tmp->next;
	free(tmp);

	list->clen--;

	return 0;
}

linknode_t *list_search(linklist_t *list, int obj)
{
	linknode_t *p = list->head->next;

	while (NULL != p && p->data != obj)
		p = p->next;

	return p;
}

int list_modify(linklist_t *list, int old, int new)
{
	linknode_t *p = list->head->next;

	while (NULL != p && p->data != old)
		p = p->next;
	if (NULL == p)
		return -1;

	p->data = new;

	return 0;
}

int list_getlen(linklist_t *list)
{
	return list->clen;
}

int list_reverse(linklist_t *list)
{
	linknode_t *p = list->head->next;
	linknode_t *tmp = NULL;

	list->head->next = NULL;
	while (NULL != p) {
		tmp = p;
		p = p->next;
		tmp->next = list->head->next;
		list->head->next = tmp;
	}

	return 0;
}
