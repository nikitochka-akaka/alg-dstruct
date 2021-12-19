#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct Tree
{
	int key;
	int num;
	struct Tree* right;
	struct Tree* left;
	struct Tree* parent;
};

typedef struct Tree Tree;

void AddElement(Tree* tree, int key)
{
	if (tree == NULL)
	{
		fprintf(stderr, "NULL pointer error");
		return;
	}

	Tree* newEl = (Tree*)malloc(sizeof(Tree));
	if (newEl == NULL)
	{
		fprintf(stderr, "Can't allocate memory for new tree element");
		return;
	}

	Tree* ptr = tree;
	Tree* prevPtr = NULL;
	while (ptr != NULL)
	{
		prevPtr = ptr;
		ptr->num += 1;

		if (key < ptr->key)
		{
			ptr = ptr->left;
		}
		else
		{
			ptr = ptr->right;
		}
	}

	if (key < prevPtr->key)
	{
		prevPtr->left = newEl;
	}
	else
	{
		prevPtr->right = newEl;
	}

	newEl->left = NULL;
	newEl->right = NULL;
	newEl->parent = prevPtr;
	newEl->key = key;
	newEl->num = 1;
}

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
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	if (tree == NULL)
	{
		return;
	}
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = NULL;
	tree->key = 31;
	tree->num = 1;

	AddElement(tree, 29);
	AddElement(tree, 26);
	AddElement(tree, 30);
	AddElement(tree, 33);
	AddElement(tree, 32);
	AddElement(tree, 35);
	AddElement(tree, 34);

	PrintKMinElements(tree, 5);

	return 0;
}
