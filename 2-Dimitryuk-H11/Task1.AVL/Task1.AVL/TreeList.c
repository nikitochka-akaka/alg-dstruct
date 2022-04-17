#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "TreeList.h"

Tree* FindMaximum(Tree* node)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (node->right == NULL)
	{
		return node;
	}

	return FindMinimum(node->right);
}

Tree* FindMinimum(Tree* node)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (node->left == NULL)
	{
		return node;
	}

	return FindMinimum(node->left);
}

Tree* RotateLeftRight(Tree* node)
{
	if (node->left == NULL || node->left->size <= 0)
	{
		return node;
	}
	else if (node->left->right == NULL || node->left->right->size <= 0)
	{
		return node;
	}

	RotateLeft(node->left);
	node = RotateRight(node);

	return node;
}

Tree* RotateRightLeft(Tree* node)
{
	if (node->right == NULL || node->right->size <= 0)
	{
		return node;
	}
	else if (node->right->left == NULL || node->right->left->size <= 0)
	{
		return node;
	}

	RotateRight(node->right);
	node = RotateLeft(node);

	return node;
}

int GetBalance(Tree* node)
{
	if (node == NULL)
	{
		return 0;
	}

	if (IsLeaf(node))
	{
		return 0;
	}

	if (node->left == NULL)
	{
		return -node->right->height;
	}

	if (node->right == NULL)
	{
		return node->left->height;
	}

	return (node->left->height - node->right->height);
}

void Recalculate(Tree* node)
{
	if (node == NULL)
	{
		return;
	}

	if (node->left != NULL)
	{
		Recalculate(node->left);
	}

	if (node->right != NULL)
	{
		Recalculate(node->right);
	}

	if (IsLeaf(node))
	{
		node->size = 1;
		node->height = 1;

		return;
	}

	if (node->left == NULL)
	{
		node->size = node->right->size + 1;
		node->height = node->right->height + 1;

		return;
	}

	if (node->right == NULL)
	{
		node->size = node->left->size + 1;
		node->height = node->left->height + 1;

		return;
	}

	node->size = node->left->size + node->right->size + 1;
	node->height = max(node->left->height, node->right->height) + 1;
}

int IsLeaf(Tree* node)
{
	if (node == NULL)
	{
		return false;
	}

	return (node->left == NULL && node->right == NULL);
}

int IsRoot(Tree* node)
{
	if (node == NULL)
	{
		return false;
	}

	return (node->parent == NULL);
}

Tree* RotateRight(Tree* node)
{
	if (node->left == NULL || node->left->size <= 0)
	{
		return node;
	}

	Tree* root = node->left;
	node->left = root->right;
	if (root->right != NULL)
	{
		root->right->parent = node;
	}
	root->right = node;
	if (node->parent == NULL)
	{
		root->parent = NULL;
		node->parent = root;
		Recalculate(root);
	}
	else
	{
		if (node->parent->left == node)
		{
			node->parent->left = root;
			root->parent = node->parent;
			node->parent = root;
		}
		else if (node->parent->right == node)
		{
			node->parent->right = root;
			root->parent = node->parent;
			node->parent = root;
		}

		Recalculate(root->parent);
	}

	return root;
}

Tree* RotateLeft(Tree* node)
{
	if (node->right == NULL || node->right->size <= 0)
	{
		return node;
	}

	Tree* root = node->right;
	node->right = root->left;
	if (root->left != NULL)
	{
		root->left->parent = node;
	}
	root->left = node;
	if (node->parent == NULL)
	{
		root->parent = NULL;
		node->parent = root;
		Recalculate(root);
	}
	else
	{
		if (node->parent->left == node)
		{
			node->parent->left = root;
			root->parent = node->parent;
			node->parent = root;
		}
		else if (node->parent->right == node)
		{
			node->parent->right = root;
			root->parent = node->parent;
			node->parent = root;
		}

		Recalculate(root->parent);
	}

	return root;
}

Tree* Search(Tree* node, int key)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (node->key == key)
	{
		return node;
	}

	if (key < node->key)
	{
		return Search(node->left, key);
	}
	else
	{
		return Search(node->right, key);
	}
}

Tree* FindFit(Tree* node, int key)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (key == node->key)
	{
		return NULL;
	}

	if (IsLeaf(node))
	{
		return node;
	}

	if (key < node->key)
	{
		if (node->left == NULL)
		{
			return node;
		}
		else
		{
			return FindFit(node->left, key);
		}
	}
	else
	{
		if (node->right == NULL)
		{
			return node;
		}
		else
		{
			return FindFit(node->right, key);
		}
	}
}

Tree* Insert(Tree* node, int key)
{
	if (node == NULL)
	{
		Tree* newNode = (Tree*)malloc(sizeof(Tree));
		if (newNode == NULL)
		{
			return NULL;
		}

		newNode->height = 1;
		newNode->key = key;
		newNode->left = newNode->right = newNode->parent = NULL;
		newNode->size = 1;

		return newNode;
	}

	Tree* fitLeaf = FindFit(node, key);
	if (fitLeaf == NULL)
	{
		return node;
	}

	Tree* newNode = (Tree*)malloc(sizeof(Tree));
	if (newNode == NULL)
	{
		return NULL;
	}

	newNode->key = key;
	newNode->left = newNode->right = NULL;
	newNode->size = 1;
	newNode->parent = fitLeaf;

	if (key < fitLeaf->key)
	{
		fitLeaf->left = newNode;
	}
	else
	{
		fitLeaf->right = newNode;
	}

	Recalculate(node);

	Tree* treePtr = newNode->parent;
	int bal = 0;
	while (!IsRoot(treePtr))
	{
		bal = GetBalance(treePtr);

		if (bal > 1)
		{
			if (treePtr->left != NULL)
			{
				if (key < treePtr->left->key)
				{
					treePtr = RotateRight(treePtr);
				}
				else
				{
					treePtr = RotateLeftRight(treePtr);
				}
			}
		}

		if (bal < -1)
		{
			if (treePtr->right != NULL)
			{
				if (key > treePtr->right->key)
				{
					treePtr = RotateLeft(treePtr);
				}
				else
				{
					treePtr = RotateRightLeft(treePtr);
				}
			}
		}

		treePtr = treePtr->parent;
	}

	bal = GetBalance(treePtr);
	if (bal > 1)
	{
		if (treePtr->left != NULL)
		{
			if (key < treePtr->left->key)
			{
				treePtr = RotateRight(treePtr);
			}
			else
			{
				treePtr = RotateLeftRight(treePtr);
			}
		}
	}

	if (bal < -1)
	{
		if (treePtr->right != NULL)
		{
			if (key > treePtr->right->key)
			{
				treePtr = RotateLeft(treePtr);
			}
			else
			{
				treePtr = RotateRightLeft(treePtr);
			}
		}
	}

	return treePtr;
}

Tree* Delete(Tree* node, int key)
{
	if (node == NULL)
	{
		return NULL;
	}

	Tree* deleteNode = Search(node, key);
	if (deleteNode == NULL)
	{
		return node;
	}

	Tree* treePtr = NULL;
	if (IsLeaf(deleteNode))
	{
		if (IsRoot(deleteNode))
		{
			free(deleteNode);
			return NULL;
		}
		else
		{
			treePtr = deleteNode->parent;
			if (deleteNode->parent->right == deleteNode)
			{
				deleteNode->parent->right = NULL;
				free(deleteNode);
			}
			else if (deleteNode->parent->left == deleteNode)
			{
				deleteNode->parent->left = NULL;
				free(deleteNode);
			}
		}
	}
	else if ((deleteNode->left != NULL) ^ (deleteNode->right != NULL))
	{
		if (deleteNode->left != NULL)
		{
			if (IsLeaf(deleteNode->left))
			{
				treePtr = deleteNode;
				deleteNode->key = deleteNode->left->key;
				free(deleteNode->left);
				deleteNode->left = NULL;
			}
			else
			{
				Tree* maxNode = FindMaximum(deleteNode->left);
				if (maxNode == NULL)
				{
					fprintf(stderr, "error ocured while delete!");
					exit(1);
				}

				treePtr = maxNode->parent;

				if (maxNode->parent->left == maxNode)
				{
					maxNode->parent->left = maxNode->left;
				}
				else if (maxNode->parent->right == maxNode)
				{
					maxNode->parent->right = maxNode->left;
				}

				deleteNode->key = maxNode->key;
				free(maxNode);
			}
		}
		else if (deleteNode->right != NULL)
		{
			if (IsLeaf(deleteNode->right))
			{
				treePtr = deleteNode;
				deleteNode->key = deleteNode->right->key;
				free(deleteNode->right);
				deleteNode->right = NULL;
			}
			else
			{
				Tree* minNode = FindMinimum(deleteNode->right);
				if (minNode == NULL)
				{
					fprintf(stderr, "error ocured while delete!");
					exit(1);
				}

				treePtr = minNode->parent;

				if (minNode->parent->left == minNode)
				{
					minNode->parent->left = minNode->right;
				}
				else if (minNode->parent->right == minNode)
				{
					minNode->parent->right = minNode->right;
				}

				deleteNode->key = minNode->key;
				free(minNode);
			}
		}
	}
	else
	{
		Tree* minNode = FindMinimum(deleteNode->right);
		if (minNode == NULL)
		{
			fprintf(stderr, "error ocured while delete!");
			exit(1);
		}

		deleteNode->key = minNode->key;

		if (IsLeaf(minNode))
		{
			if (minNode->parent->left == minNode)
			{
				minNode->parent->left = NULL;
			}
			else if (minNode->parent->right == minNode)
			{
				minNode->parent->right = NULL;
			}
		}
		else
		{
			if (minNode->parent->left == minNode)
			{
				minNode->parent->left = minNode->right;
			}
			else if (minNode->parent->right == minNode)
			{
				minNode->parent->right = minNode->right;
			}

			minNode->right->parent = minNode->parent;
		}

		treePtr = minNode->parent;

		free(minNode);
	}

	Recalculate(node);

	if (treePtr == NULL)
	{
		fprintf(stderr, "error ocured while delete!");
		exit(1);
		return node;
	}

	int bal = 0;
	while (!IsRoot(treePtr))
	{
		bal = GetBalance(treePtr);

		if (bal > 1)
		{
			if (treePtr->left != NULL)
			{
				if (GetBalance(treePtr->left) >= 0)
				{
					treePtr = RotateRight(treePtr);
				}
				else
				{
					treePtr = RotateLeftRight(treePtr);
				}
			}
		}

		if (bal < -1)
		{
			if (treePtr->right != NULL)
			{
				if (GetBalance(treePtr->right) <= 0)
				{
					treePtr = RotateLeft(treePtr);
				}
				else
				{
					treePtr = RotateRightLeft(treePtr);
				}
			}
		}

		treePtr = treePtr->parent;
	}

	bal = GetBalance(treePtr);

	if (bal > 1)
	{
		if (treePtr->left != NULL)
		{
			if (GetBalance(treePtr->left) >= 0)
			{
				treePtr = RotateRight(treePtr);
			}
			else
			{
				treePtr = RotateLeftRight(treePtr);
			}
		}
	}

	if (bal < -1)
	{
		if (treePtr->right != NULL)
		{
			if (GetBalance(treePtr->right) <= 0)
			{
				treePtr = RotateLeft(treePtr);
			}
			else
			{
				treePtr = RotateRightLeft(treePtr);
			}
		}
	}

	return treePtr;
}

Tree* CreateTreeFromList(List* begin)
{
	if (begin == NULL)
	{
		return NULL;
	}

	Tree* root = Insert(NULL, begin->data);

	List* listPtr = begin;
	int length = 1;
	while (listPtr->next != NULL)
	{
		++length;
		listPtr = listPtr->next;
	}

	listPtr = begin->next;
	for (int i = 1; i < length; ++i, listPtr = listPtr->next)
	{
		root = Insert(root, listPtr->data);
	}

	return root;
}

Tree* FindNodeBySerial(Tree* tree, size_t serial)
{
	if (tree == NULL)
	{
		fprintf(stderr, "\nError! Function 'FindNodeBySerial' aborted. Argument 'tree' was NULL.");
		return NULL;
	}

	int k = serial;
	Tree* treePtr = tree;
	while (k > 0)
	{
		if (treePtr->left != NULL)
		{
			if (treePtr->left->size + 1 > k)
			{
				treePtr = treePtr->left;
				--k;
			}
			else
			{
				if (treePtr->left->size + 1 == k)
				{
					return treePtr;
				}
				else
				{
					if (treePtr->right == NULL)
					{
						return NULL;
					}

					k -= treePtr->left->size + 1;
					treePtr = treePtr->right;
				}
			}
		}
		else
		{
			if (treePtr->right == NULL)
			{
				return NULL;
			}

			treePtr = treePtr->right;
			--k;
		}
	}

	return treePtr;
}

Tree* TreeListInsertBySerial(List* list, size_t serial, int data)
{
	if (list == NULL)
	{
		return NULL;
	}

	List* listPtr = list;
	int length = 1;
	while (listPtr->next != NULL)
	{
		++length;
		listPtr = listPtr->next;
	}

	if (serial > length)
	{
		return NULL;
	}

	listPtr = list;
	for (int i = 0; i < serial; ++i)
	{
		listPtr = listPtr->next;
	}

	List* newNode = (List*)malloc(sizeof(List));
	if (newNode == NULL)
	{
		return NULL;
	}

	newNode->data;


	if (serial == 0)
	{
		newNode->next = listPtr;
	}
	else
	{
		newNode->next = listPtr->next;
		newNode->prev = listPtr;

		if (listPtr->next != NULL)
		{
			listPtr->next->prev = newNode;
		}

		listPtr->next = newNode;
	}

	while (listPtr->prev != NULL)
	{
		listPtr = listPtr->prev;
	}

	return CreateTreeFromList(listPtr);
}

Tree* TreeListDeleteBySerial(List* list, size_t serial)
{
	if (list == NULL)
	{
		return NULL;
	}

	List* listPtr = list;
	int i = 0;
	while (listPtr->next != NULL)
	{
		listPtr = listPtr->next;
		++i;
	}

	if (i == serial)
	{
		if (listPtr->next != NULL)
		{
			listPtr->next->prev = listPtr->prev;
		}

		if (listPtr->prev != NULL)
		{
			listPtr->prev->next = listPtr->next;
		}

		free(listPtr);

		while (listPtr->prev != NULL)
		{
			listPtr = listPtr->prev;
		}

		return CreateTreeFromList(listPtr);
	}
	else
	{
		return NULL;
	}
}

Tree* MergeLists(List* main, List* second)
{
	if (main == NULL)
	{
		if (second == NULL)
		{
			return NULL;
		}
		else
		{
			return CreateTreeFromList(second);
		}
	}

	if (second == NULL)
	{
		return CreateTreeFromList(main);
	}

	List* listPtr = main;
	while (listPtr->next != NULL)
	{
		listPtr = listPtr->next;
	}

	listPtr->next = second;
	second->prev = listPtr;

	return CreateTreeFromList(main);
}
