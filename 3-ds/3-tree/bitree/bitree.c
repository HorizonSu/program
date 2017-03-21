#include <stdio.h>
#include <stdlib.h>
#include "bitnode.h"
#include "stack.h"
#include "queue.h"

btnode_t *create_btnode(int value);
btnode_t *bitree_create(int start, int end);
int bitree_preorder(btnode_t *root);
int bitree_inorder(btnode_t *root);
int bitree_postorder(btnode_t *root);
int bitree_nuorder(btnode_t *root);
int bitree_destroy(btnode_t *root);

int main()
{
	btnode_t *root = NULL;
	
	root = bitree_create(1, 10);

	puts("preorder:");
	bitree_preorder(root);
	putchar('\n');

	puts("inorder:");
	bitree_inorder(root);
	putchar('\n');

	puts("postorder:");
	bitree_postorder(root);
	putchar('\n');

	puts("nuorder:");
	bitree_nuorder(root);
	putchar('\n');

	bitree_destroy(root);

	return 0;
}

btnode_t *create_btnode(int value)
{
	btnode_t *node = NULL;

	node = malloc(sizeof(*node));
	node->data = value;
	node->lchild = NULL;
	node->rchild = NULL;

	return node;
}

btnode_t *bitree_create(int start, int end)
{
	btnode_t *root;

	root = create_btnode(start);
//	printf("%5d", root->data);

	if (start * 2 <= end)
		root->lchild = bitree_create(start * 2, end);
	if (start * 2 + 1 <= end)
		root->rchild = bitree_create(start * 2 + 1, end);

	return root;
}

#if 0
int bitree_preorder(btnode_t *root)
{
	printf("%5d", root->data);
	if (root->lchild != NULL)
		bitree_preorder(root->lchild);
	if (root->rchild != NULL)
		bitree_preorder(root->rchild);

	return 0;
}
#else

int bitree_preorder(btnode_t *root)
{
	stack_t *stack;

	stack = stack_init(10);

	while (!stack_isempty(stack) || root != NULL) {
		if (root != NULL) {
			printf("%5d", root->data);
			stack_push(stack, root);
			root = root->lchild;
		} else {
			stack_pop(stack, &root);
			root = root->rchild;
		}	
	}

	stack_destroy(stack);

	return 0;
}

#endif

int bitree_inorder(btnode_t *root)
{
	if (root == NULL)
		return -1;

	bitree_inorder(root->lchild);
	printf("%5d", root->data);
	bitree_inorder(root->rchild);

	return 0;
}

int bitree_postorder(btnode_t *root)
{
	if (root == NULL)
		return -1;

	bitree_postorder(root->lchild);
	bitree_postorder(root->rchild);
	printf("%5d", root->data);

	return 0;
}

int bitree_destroy(btnode_t *root)
{
	if (root == NULL)
		return -1;
	
	bitree_destroy(root->lchild);
	bitree_destroy(root->rchild);
	free(root);

	return 0;
}

int bitree_nuorder(btnode_t *root)
{
	queue_t *queue = NULL;

	queue = queue_init(10);
	queue_enqueue(queue, root);

	while (queue->head != queue->tail) {
		queue_dequeue(queue, &root);
		printf("%5d", root->data);
		if (NULL != root->lchild)
			queue_enqueue(queue, root->lchild);
		if (NULL != root->rchild)
			queue_enqueue(queue, root->rchild);
	}
	
	queue_destroy(queue);
	return 0;
}
