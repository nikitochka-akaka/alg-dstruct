#pragma once

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false !true
#define max(a, b) (a > b ? a : b)

struct List
{
	struct List* next;
	struct List* prev;
	int data;
};

struct Tree
{
	int key;
	int size;
	int height;
	struct Tree* left;
	struct Tree* right;
	struct Tree* parent;
};

typedef struct List List;
typedef struct Tree Tree;

int IsLeaf(Tree* node);
int GetBalance(Tree* node);
Tree* FindFit(Tree* node, int key);
Tree* Search(Tree* node, int key);
Tree* Insert(Tree* node, int key);
Tree* Delete(Tree* node, int key);
void Recalculate(Tree* node);
Tree* RotateRight(Tree* node);
Tree* RotateLeft(Tree* node);
Tree* RotateLeftRight(Tree* node);
Tree* RotateRightLeft(Tree* node);
Tree* FindMinimum(Tree* node);
Tree* FindMaximum(Tree* node);
Tree* CreateTreeFromList(List* begin);
Tree* FindNodeBySerial(Tree* tree, size_t serial);
