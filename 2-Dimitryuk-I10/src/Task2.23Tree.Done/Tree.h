#pragma once

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false !true

struct Tree
{
	int size;
	int keys[3];
	struct Tree* childs[4];
	struct Tree* parent;
};

typedef struct Tree Tree;

int Contains(Tree* node, int key);
void SwapValues(int* x, int* y);
void SortTwoValues(int* x, int* y);
void SortThreeValues(int* x, int* y, int* z);
void SortKeys(Tree* node);
void NodeInsertKey(Tree* node, int key);
void NodeDeleteKey(Tree* node, int key);
void TwoNodeConvert(Tree* node, Tree* first, Tree* second, int key);
int IsLeaf(Tree* node);
Tree* Node(int key);
Tree* Split(Tree* node);
Tree* Insert(Tree* root, int key);
Tree* Search(Tree* node, int key);
Tree* SearchMin(Tree* node);
Tree* Merge(Tree* leaf);
Tree* Spread(Tree* leaf);
Tree* FixLeaf(Tree* leaf);
Tree* Delete(Tree* root, int key);
void PrintTree(Tree* root);
