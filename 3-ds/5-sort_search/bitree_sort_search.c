#include <stdio.h>
#include <stdlib.h>

typedef struct _bitree_node_ {
	int data;
	struct _bitree_node_ *lchild,
						 *rchild;
}btnode_st;

btnode_st *creat_bitnode(int value);
btnode_st *bitree_creat(int *data, int num);
int bitree_insert(btnode_st *root, int value);
int bitree_inorder(btnode_st *root);
btnode_st* bitree_search(btnode_st *root, int obj);

int main()
{
	int value;
	btnode_st *root = NULL;
	int data[] = {5, 3, 6, 2, 8, 1, 4, 9, 7, 10};

	root = bitree_creat(data, sizeof(data)/sizeof(*data));

	puts("sort:");
	bitree_inorder(root);
	putchar('\n');

	puts("input number:");
	scanf("%d", &value);
	if (NULL != bitree_search(root, value))
		printf("%d", value);

	return 0;
}

btnode_st *bitree_creat(int *data, int num)
{
	btnode_st *root = NULL;
	int i;

	root = creat_bitnode(*data);

	for (i = 1; i < num; i++)
		bitree_insert(root, data[i]);

	return root;
}

btnode_st *creat_bitnode(int value)
{
	btnode_st *node = NULL;

	node = malloc(sizeof(*node));
	node->lchild = NULL;
	node->rchild = NULL;
	node->data = value;

	return node;
}

int bitree_inorder(btnode_st *root)
{
	if (root == NULL)
		return -1;

	bitree_inorder(root->lchild);
	printf("%5d", root->data);
	bitree_inorder(root->rchild);

	return 0;
}

int bitree_insert(btnode_st *root, int value)
{
	btnode_st *p = root;

	while (root != NULL) {
		p = root;
		if (value < root->data)
			root = root->lchild;
		else
			root = root->rchild;
	}

	root = p;

	if (value < root->data)
		root->lchild = creat_bitnode(value);
	else
		root->rchild = creat_bitnode(value);
	
	return 0;
}

btnode_st* bitree_search(btnode_st *root, int obj)
{
	btnode_st *p = root;

	while(p != NULL && p->data != obj) {
		if(obj < p->data)
			p = p->lchild;
		else
			p = p->rchild;
	}

	return p;
}
