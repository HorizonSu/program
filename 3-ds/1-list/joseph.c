#include <stdio.h>
#include <stdlib.h>

typedef struct _linknode_ {
	int data;
	struct _linknode_ *next;
}linknode_t;

linknode_t *joseph_init(int number);
linknode_t *create_clinknode(int value);
int joseph_show(linknode_t *head);
linknode_t *joseph_begin(linknode_t *head, int rule);
int joseph_free(linknode_t *head);

int main()
{
	linknode_t *list = NULL;
	int num, rule;

	puts("input two number:");

	scanf("%d%d", &num, &rule);
	
	list = joseph_init(num);
	list = joseph_begin(list, rule);

	joseph_show(list);
	joseph_free(list);
	return 0;
}

linknode_t *joseph_init(int number)
{
	linknode_t *head = NULL;
	linknode_t *new = NULL;
	int i;

	head = create_clinknode(1);

	for (i = number; i > 1; i --) {
		new = create_clinknode(i);
		new->next = head->next;
		head->next = new;
	}

	return head;
}

linknode_t *create_clinknode(int value)
{
	linknode_t *node = NULL;

	node = (linknode_t *)malloc(sizeof(linknode_t));
	node->data = value;
	node->next = node;

	return node;
}

int joseph_show(linknode_t *head)
{
	linknode_t *p = head;

	if (head == NULL)
		return 0;

	do {
		printf("%5d", p->data);
		p = p->next;
	} while (head != p);
	putchar('\n');

	return 0;
}

linknode_t *joseph_begin(linknode_t *head, int rule)
{
	linknode_t *tmp = NULL;
	int counter;

	for (counter = 1; head->next != head; counter ++) {
		if (counter == rule - 1) {
			tmp = head->next;
			head->next = tmp->next;
			free(tmp);
			counter = 0;
		}
		head = head->next;
	}

	return head;
}

int joseph_free(linknode_t *head)
{
	free(head);
}
