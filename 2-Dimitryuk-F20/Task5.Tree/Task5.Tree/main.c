#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

struct Tree
{
	int key;
	int num;
	struct Tree* right;
	struct Tree* left;
	struct Tree* parent;
};

typedef struct Tree Tree;

Tree* KMin(Tree* tree, int k)
{
	if ((tree->num < k) || (k <= 0))
	{
		return NULL;
	}

	int leftSize;

	if (tree->left != NULL)
	{
		leftSize = tree->left->num + 1;
	}
	else
	{
		leftSize = 1;
	}

	if (leftSize != k)
	{
		if (leftSize > k)
		{
			if (tree->left != NULL)
			{
				tree = KMin(tree->left, k);
			}
		}
		else
		{
			if (tree->right != NULL)
			{
				tree = KMin(tree->right, k - leftSize);
			}
		}
	}
	
	return tree;
}

void __PrintTree(Tree* tree)
{
	if (tree == NULL)
	{
		return;
	}

	printf("%d ", tree->key);

	if (tree->left != NULL)
	{
		__PrintTree(tree->left);
	}

	if (tree->right != NULL)
	{
		__PrintTree(tree->right);
	}
}

void __PrintLessSerialEls(Tree* tree)
{
	if (tree == NULL)
	{
		return;
	}

	Tree* parent;

	while (tree->parent != NULL)
	{
		parent = tree->parent;

		if (parent->right == tree)
		{
			__PrintTree(parent->left);
			printf("%d ", parent->key);
		}
		else
		{
			printf("%d ", parent->key);
		}
		
		tree = parent;
	}
}

void PrintKMinElements(Tree* tree, int k)
{
	Tree* kMin = KMin(tree, k);

	if ((kMin->key % 2) == 0)
	{
		__PrintLessSerialEls(kMin);
	}
	else
	{
		printf("Element is odd");
	}
}

int main()
{
	Tree node8 = { 34, 1, NULL, NULL, NULL };
	Tree node7 = { 35, 2, NULL, &node8, NULL };
	Tree node6 = { 32, 1, NULL, NULL, NULL };
	Tree node5 = { 33, 4, &node7, &node6, NULL };
	Tree node4 = { 30, 1, NULL, NULL, NULL };
	Tree node3 = { 26, 1, NULL, NULL, NULL };
	Tree node2 = { 29, 3, &node4, &node3, NULL };
	Tree node1 = { 31, 8, &node5, &node2, NULL };

	node2.parent = &node1;
	node3.parent = &node2;
	node4.parent = &node2;
	node5.parent = &node1;
	node6.parent = &node5;
	node7.parent = &node5;
	node8.parent = &node7;

	PrintKMinElements(&node1, 1);

	return 0;
}
