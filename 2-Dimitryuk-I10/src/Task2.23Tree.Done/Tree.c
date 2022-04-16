#define _CRT_SECURE_NO_WARNINGS

#include "Tree.h"

int Contains(Tree* node, int key)
{
	for (int i = 0; i < node->size; ++i)
	{
		if (node->keys[i] == key)
		{
			return true;
		}
	}

	return false;
}

void SwapValues(int* x, int* y)
{
	int r = *x;
	*x = *y;
	*y = r;
}

void SortTwoValues(int* x, int* y)
{
	if (*x > *y)
	{
		SwapValues(x, y);
	}
}

void SortThreeValues(int* x, int* y, int* z)
{
	if (*x > *y)
	{
		SwapValues(x, y);
	}

	if (*x > *z)
	{
		SwapValues(x, z);
	}

	if (*y > *z)
	{
		SwapValues(y, z);
	}
}

void SortKeys(Tree* node)
{
	if (node == NULL)
	{
		return;
	}

	if (node->size == 1)
	{
		return;
	}

	if (node->size == 2)
	{
		SortTwoValues(&(node->keys[0]), &(node->keys[1]));
	}

	if (node->size == 3)
	{
		SortThreeValues(&(node->keys[0]), &(node->keys[1]), &(node->keys[2]));
	}
}

void NodeInsertKey(Tree* node, int key)
{
	if (node == NULL)
	{
		return;
	}

	if (node->size >= 3)
	{
		return;
	}

	node->keys[node->size] = key;
	node->size++;
	SortKeys(node);
}

void NodeDeleteKey(Tree* node, int key)
{
	if (node == NULL)
	{
		return;
	}

	if (node->size >= 1 && node->keys[0] == key)
	{
		node->keys[0] = node->keys[1];
		node->keys[1] = node->keys[2];
		node->size--;
	}
	else if (node->size == 2 && node->keys[1] == key)
	{
		node->keys[1] = node->keys[2];
		node->size--;
	}
}

void TwoNodeConvert(Tree* node, Tree* first, Tree* second, int key)
{
	if (node == NULL)
	{
		return;
	}

	node->keys[0] = key;
	node->childs[0] = first;
	node->childs[1] = second;
	node->childs[2] = NULL;
	node->childs[3] = NULL;
	node->parent = NULL;
	node->size = 1;
}

int IsLeaf(Tree* node)
{
	if (node == NULL)
	{
		return false;
	}

	return (node->childs[0] == NULL) && (node->childs[1] == NULL) && (node->childs[2] == NULL);
}

Tree* Node(int key)
{
	Tree* node = (Tree*)malloc(sizeof(Tree));
	if (node == NULL)
	{
		return NULL;
	}

	node->childs[0] = node->childs[1] = node->childs[2] = node->childs[3] = NULL;
	node->keys[0] = key;
	node->keys[1] = node->keys[2] = 0;
	node->parent = NULL;
	node->size = 1;

	return node;
}

Tree* _Node(int key, Tree* first, Tree* second, Tree* third, Tree* fourth, Tree* parent)
{
	Tree* node = (Tree*)malloc(sizeof(Tree));
	if (node == NULL)
	{
		return NULL;
	}

	node->childs[0] = first;
	node->childs[1] = second;
	node->childs[2] = third;
	node->childs[3] = fourth;
	node->keys[0] = key;
	node->keys[1] = node->keys[2] = 0;
	node->parent = parent;
	node->size = 1;

	return node;
}

Tree* Insert(Tree* node, int key)
{
	if (node == NULL)
	{
		return Node(key);
	}

	if (Contains(node, key))
	{
		return node;
	}

	if (IsLeaf(node))
	{
		NodeInsertKey(node, key);
	}
	else if (key < node->keys[0])
	{
		Insert(node->childs[0], key);
	}
	else if ((node->size == 1) || ((node->size == 2) && key < node->keys[1]))
	{
		Insert(node->childs[1], key);
	}
	else
	{
		Insert(node->childs[2], key);
	}

	return Split(node);
}

Tree* Split(Tree* node)
{
	if (node == NULL)
	{
		return node;
	}

	if (node->size < 3)
	{
		return node;
	}

	Tree* x = _Node(node->keys[0], node->childs[0], node->childs[1], NULL, NULL, node->parent);
	Tree* y = _Node(node->keys[2], node->childs[2], node->childs[3], NULL, NULL, node->parent);

	if (x->childs[0])
	{
		x->childs[0]->parent = x;
	}

	if (x->childs[1])
	{
		x->childs[1]->parent = x;
	}

	if (y->childs[0])
	{
		y->childs[0]->parent = y;
	}

	if (y->childs[1])
	{
		y->childs[1]->parent = y;
	}

	if (node->parent != NULL)
	{
		NodeInsertKey(node->parent, node->keys[1]);

		if (node->parent->childs[0] == node)
		{
			node->parent->childs[0] = NULL;
		}
		else if (node->parent->childs[1] == node)
		{
			node->parent->childs[1] = NULL;
		}
		else if (node->parent->childs[2] == node)
		{
			node->parent->childs[2] = NULL;
		}

		if (node->parent->childs[0] == NULL) {
			node->parent->childs[3] = node->parent->childs[2];
			node->parent->childs[2] = node->parent->childs[1];
			node->parent->childs[1] = y;
			node->parent->childs[0] = x;
		}
		else if (node->parent->childs[1] == NULL) {
			node->parent->childs[3] = node->parent->childs[2];
			node->parent->childs[2] = y;
			node->parent->childs[1] = x;
		}
		else {
			node->parent->childs[3] = y;
			node->parent->childs[2] = x;
		}

		Tree* tmp = node->parent;

		free(node);

		return tmp;
	}
	else
	{
		x->parent = node;
		y->parent = node;

		TwoNodeConvert(node, x, y, node->keys[1]);

		return node;
	}
}

Tree* Search(Tree* node, int key)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (Contains(node, key))
	{
		return node;
	}
	else if (key < node->keys[0])
	{
		return Search(node->childs[0], key);
	}
	else if ((node->size == 2) && (key < node->keys[1]) || (node->size == 1))
	{
		return Search(node->childs[1], key);
	}
	else if (node->size == 2)
	{
		return Search(node->childs[2], key);
	}
}

Tree* SearchMin(Tree* node)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (node->childs[0] == NULL)
	{
		return node;
	}
	else
	{
		return SearchMin(node->childs[0]);
	}
}

Tree* Delete(Tree* node, int key)
{
	if (node == NULL)
	{
		return NULL;
	}

	Tree* item = Search(node, key);

	if (item == NULL)
	{
		return node;
	}

	Tree* minNode = NULL;
	if (item->keys[0] == key)
	{
		minNode = SearchMin(item->childs[1]);
	}
	else
	{
		minNode = SearchMin(item->childs[2]);
	}

	if (minNode != NULL)
	{
		int* z = (key == item->keys[0] ? &(item->keys[0]) : &(item->keys[1]));
		SwapValues(z, &(minNode->keys[0]));
		item = minNode;
	}

	NodeDeleteKey(item, key);

	return FixLeaf(item);
}

Tree* FixLeaf(Tree* leaf)
{
	if (leaf == NULL)
	{
		return NULL;
	}

	if (leaf->size == 0 && leaf->parent == NULL)
	{
		free(leaf);
		return NULL;
	}

	if (leaf->size != 0) {
		if (leaf->parent)
		{
			return FixLeaf(leaf->parent);
		}
		else
		{
			return leaf;
		}
	}

	Tree* parent = leaf->parent;
	if (parent->childs[0]->size == 2 || parent->childs[1]->size == 2 || parent->size == 2)
	{
		leaf = Spread(leaf);
	}
	else if (parent->size == 2 && parent->childs[2]->size == 2)
	{
		leaf = Spread(leaf);
	}
	else
	{
		leaf = Merge(leaf);
	}

	return FixLeaf(leaf);
}

Tree* Spread(Tree* leaf)
{
	if (leaf == NULL)
	{
		return leaf;
	}

	Tree* parent = leaf->parent;
	Tree* first = parent->childs[0];
	Tree* second = parent->childs[1];
	Tree* third = parent->childs[2];

	if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2))
	{
		if (first == leaf)
		{
			parent->childs[0] = parent->childs[1];
			parent->childs[1] = parent->childs[2];
			parent->childs[2] = NULL;
			NodeInsertKey(parent->childs[0], parent->keys[0]);
			parent->childs[0]->childs[2] = parent->childs[0]->childs[1];
			parent->childs[0]->childs[1] = parent->childs[0]->childs[0];

			if (leaf->childs[0] != NULL)
			{
				parent->childs[0]->childs[0] = leaf->childs[0];
			}
			else if (leaf->childs[1] != NULL)
			{
				parent->childs[0]->childs[0] = leaf->childs[1];
			}

			if (parent->childs[0]->childs[0] != NULL)
			{
				parent->childs[0]->childs[0]->parent = parent->childs[0];
			}

			NodeDeleteKey(parent, parent->keys[0]);

			if (first != NULL)
			{
				free(first);
			}
		}
		else if (second == leaf)
		{
			NodeInsertKey(first, parent->keys[0]);
			NodeDeleteKey(parent, parent->keys[0]);

			if (leaf->childs[0] != NULL)
			{
				first->childs[2] = leaf->childs[0];
			}
			else if (leaf->childs[1] != NULL)
			{
				first->childs[2] = leaf->childs[1];
			}

			if (first->childs[2] != NULL)
			{
				first->childs[2]->parent = first;
			}

			parent->childs[1] = parent->childs[2];
			parent->childs[2] = NULL;

			if (second != NULL)
			{
				free(second);
			}
		}
		else if (third == leaf)
		{
			NodeInsertKey(second, parent->keys[1]);
			parent->childs[2] = NULL;
			NodeDeleteKey(parent, parent->keys[1]);

			if (leaf->childs[0] != NULL)
			{
				second->childs[2] = leaf->childs[0];
			}
			else if (leaf->childs[1] != NULL)
			{
				second->childs[2] = leaf->childs[1];
			}

			if (second->childs[2] != NULL)
			{
				second->childs[2]->parent = second;
			}

			if (third != NULL)
			{
				free(third);
			}
		}
	}
	else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2)))
	{
		if (third == leaf)
		{
			if (leaf->childs[0] != NULL)
			{
				leaf->childs[1] = leaf->childs[0];
				leaf->childs[0] = NULL;
			}

			NodeInsertKey(leaf, parent->keys[1]);
			if (second->size == 2)
			{
				parent->keys[1] = second->keys[1];
				NodeDeleteKey(second, second->keys[1]);
				leaf->childs[0] = second->childs[2];
				second->childs[2] = NULL;

				if (leaf->childs[0] != NULL)
				{
					leaf->childs[0]->parent = leaf;
				}
			}
			else if (first->size == 2)
			{
				parent->keys[1] = second->keys[0];
				leaf->childs[0] = second->childs[1];
				second->childs[1] = second->childs[0];

				if (leaf->childs[0] != NULL)
				{
					leaf->childs[0]->parent = leaf;
				}

				second->keys[0] = parent->keys[0];
				parent->keys[0] = first->keys[1];
				NodeDeleteKey(first, first->keys[1]);
				second->childs[0] = first->childs[2];

				if (second->childs[0] != NULL)
				{
					second->childs[0]->parent = second;
				}

				first->childs[2] = NULL;
			}
		}
		else if (second == leaf)
		{
			if (third->size == 2)
			{
				if (leaf->childs[0] == NULL)
				{
					leaf->childs[0] = leaf->childs[1];
					leaf->childs[1] = NULL;
				}

				NodeInsertKey(second, parent->keys[1]);
				parent->keys[1] = third->keys[0];
				NodeDeleteKey(third, third->keys[0]);
				second->childs[1] = third->childs[0];

				if (second->childs[1] != NULL)
				{
					second->childs[1]->parent = second;
				}

				third->childs[0] = third->childs[1];
				third->childs[1] = third->childs[2];
				third->childs[2] = NULL;
			}
			else if (first->size == 2)
			{
				if (leaf->childs[1] == NULL)
				{
					leaf->childs[1] = leaf->childs[0];
					leaf->childs[0] = NULL;
				}

				NodeInsertKey(second, parent->keys[0]);
				parent->keys[0] = first->keys[1];
				NodeDeleteKey(first, first->keys[1]);
				second->childs[0] = first->childs[2];

				if (second->childs[0] != NULL)
				{
					second->childs[0]->parent = second;
				}

				first->childs[2] = NULL;
			}
		}
		else if (first == leaf)
		{
			if (leaf->childs[0] == NULL)
			{
				leaf->childs[0] = leaf->childs[1];
				leaf->childs[1] = NULL;
			}

			NodeInsertKey(first, parent->keys[0]);

			if (second->size == 2)
			{
				parent->keys[0] = second->keys[0];
				NodeDeleteKey(second, second->keys[0]);
				first->childs[1] = second->childs[0];

				if (first->childs[1] != NULL)
				{
					first->childs[1]->parent = first;
				}

				second->childs[0] = second->childs[1];
				second->childs[1] = second->childs[2];
				second->childs[2] = NULL;
			}
			else if (third->size == 2)
			{
				parent->keys[0] = second->keys[0];
				second->keys[0] = parent->keys[1];
				parent->keys[1] = third->keys[0];
				NodeDeleteKey(third, third->keys[0]);
				first->childs[1] = second->childs[0];

				if (first->childs[1] != NULL)
				{
					first->childs[1]->parent = first;
				}

				second->childs[0] = second->childs[1];
				second->childs[1] = third->childs[0];

				if (second->childs[1] != NULL)
				{
					second->childs[1]->parent = second;
				}

				third->childs[0] = third->childs[1];
				third->childs[1] = third->childs[2];
				third->childs[2] = NULL;
			}
		}
	}
	else if (parent->size == 1)
	{
		NodeInsertKey(leaf, parent->keys[0]);

		if (first == leaf && second->size == 2)
		{
			parent->keys[0] = second->keys[0];
			NodeDeleteKey(second, second->keys[0]);

			if (leaf->childs[0] == NULL)
			{
				leaf->childs[0] = leaf->childs[1];
			}

			leaf->childs[1] = second->childs[0];
			second->childs[0] = second->childs[1];
			second->childs[1] = second->childs[2];
			second->childs[2] = NULL;

			if (leaf->childs[1] != NULL)
			{
				leaf->childs[1]->parent = leaf;
			}
		}
		else if (second == leaf && first->size == 2)
		{
			parent->keys[0] = first->keys[1];
			NodeDeleteKey(first, first->keys[1]);

			if (leaf->childs[1] == NULL)
			{
				leaf->childs[1] = leaf->childs[0];
			}

			leaf->childs[0] = first->childs[2];
			first->childs[2] = NULL;

			if (leaf->childs[0] != NULL)
			{
				leaf->childs[0]->parent = leaf;
			}
		}
	}

	return parent;
}

Tree* Merge(Tree* leaf)
{
	if (leaf == NULL)
	{
		return leaf;
	}

	Tree* parent = leaf->parent;

	if (parent->childs[0] == leaf)
	{
		NodeInsertKey(parent->childs[1], parent->keys[0]);
		parent->childs[1]->childs[2] = parent->childs[1]->childs[1];
		parent->childs[1]->childs[1] = parent->childs[1]->childs[0];

		if (leaf->childs[0] != NULL)
		{
			parent->childs[1]->childs[0] = leaf->childs[0];
		}
		else if (leaf->childs[1] != NULL)
		{
			parent->childs[1]->childs[0] = leaf->childs[1];
		}

		if (parent->childs[1]->childs[0] != NULL)
		{
			parent->childs[1]->childs[0]->parent = parent->childs[1];
		}

		NodeDeleteKey(parent, parent->keys[0]);
		if (parent->childs[0] != NULL)
		{
			free(parent->childs[0]);
		}
		parent->childs[0] = NULL;
	}
	else if (parent->childs[1] == leaf)
	{
		NodeInsertKey(parent->childs[0], parent->keys[0]);

		if (leaf->childs[0] != NULL)
		{
			parent->childs[0]->childs[2] = leaf->childs[0];
		}
		else if (leaf->childs[1] != NULL)
		{
			parent->childs[0]->childs[2] = leaf->childs[1];
		}

		if (parent->childs[0]->childs[2] != NULL)
		{
			parent->childs[0]->childs[2]->parent = parent->childs[0];
		}

		NodeDeleteKey(parent, parent->keys[0]);
		if (parent->childs[1] != NULL)
		{
			free(parent->childs[1]);
		}
		parent->childs[1] = NULL;
	}

	if (parent->parent == NULL)
	{
		Tree* tmp = NULL;

		if (parent->childs[0] != NULL)
		{
			tmp = parent->childs[0];
		}
		else
		{
			tmp = parent->childs[1];
		}

		tmp->parent = NULL;
		if (parent != NULL)
		{
			free(parent);
		}
		return tmp;
	}

	return parent;
}

void PrintTree(Tree* root)
{
	if (root == NULL)
	{
		return;
	}

	PrintTree(root->childs[0]);

	for (int i = 0; i < root->size; ++i)
	{
		printf("%d ", root->keys[i]);
	}

	PrintTree(root->childs[1]);
	PrintTree(root->childs[2]);
}
