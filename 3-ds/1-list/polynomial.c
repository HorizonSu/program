#include <stdio.h>
#include <stdlib.h>

typedef struct _data_type_ {
	int coeff;
	int exp;
}ldata_t;

typedef struct _linknode_ {
	ldata_t data;
	struct _linknode_ *next;
}linknode_t;

linknode_t *creat_linknode(ldata_t *data);
linknode_t *creat_empty_linklist(void);
int get_data(linknode_t *head);
int insert_linklist(linknode_t *head, ldata_t *data);
int show_linklist(linknode_t *head);
linknode_t *combine_linklist(linknode_t *lista, linknode_t *listb);

int main()
{
	linknode_t *lista = NULL,
			 *listb = NULL,
			 *listc = NULL;

	lista = creat_empty_linklist();
	listb = creat_empty_linklist();
	listc = creat_empty_linklist();
	
	get_data(lista);
	get_data(listb);

	show_linklist(lista);
	show_linklist(listb);

	listc = combine_linklist(lista,listb);
	show_linklist(listc);

	return 0;
}

linknode_t *creat_linknode(ldata_t *data)
{
	linknode_t *node = NULL;

	node = (linknode_t *)malloc(sizeof(linknode_t));
	node->data = *data;
	node->next = NULL;
	
	return node;
}

linknode_t *creat_empty_linklist(void)
{
	ldata_t data = {0,0};
	return creat_linknode(&data);
}

int get_data(linknode_t *head)
{
	ldata_t data;

	while(1)
	{
		while( 2 != scanf("%d,%d",&data.coeff, &data.exp))
			getchar();
		if(0 == data.coeff)
			break;
		insert_linklist(head, &data);
	}

	return 0;
}

int insert_linklist(linknode_t *head, ldata_t *data)
{
	linknode_t *new = NULL;
	while(NULL != head->next && head->next->data.exp > data->exp)
		head = head->next;
	if(NULL == head->next || head->next->data.exp < data->exp)
	{
		new = creat_linknode(data);
		new->next = head->next;
		head->next = new;
	}
	else
		head->next->data.coeff += data->coeff;
	
	return 0;
}

int show_linklist(linknode_t *head)
{
	head = head->next;
	while(NULL != head)
	{
		printf(" %dX^%d +",head->data.coeff, head->data.exp);
		head = head->next;
	}
	puts("\b ");
	return 0;
}

linknode_t *combine_linklist(linknode_t *lista, linknode_t *listb)
{
	linknode_t *head = lista;
	linknode_t *tmp = NULL;

	while(NULL != lista->next && NULL != listb->next)
	{
		if(lista->next->data.exp > listb->next->data.exp);
		else if(lista->next->data.exp == listb->next->data.exp)
		{
			lista->next->data.coeff += listb->next->data.coeff;
			tmp = listb->next;
			listb->next = tmp->next;
			free(tmp);
		}
		else
		{
			tmp = listb->next;
			listb->next = tmp->next;

			tmp->next = lista->next;
			lista->next = tmp;
		}
		lista = lista->next;
	}
	if(listb->next)
		lista->next = listb->next;
	free(listb);

	return head;
}
