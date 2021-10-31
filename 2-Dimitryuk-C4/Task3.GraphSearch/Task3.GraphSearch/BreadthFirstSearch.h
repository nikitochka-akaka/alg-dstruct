#pragma once

#define true 1
#define false !true
#define null (void*)0

#define BUFF_WIDTH 250

typedef char bool;

struct List
{
	struct List* nextEl;
	int elNumber;
};

struct Queue
{
	struct List* queueList;
};

typedef struct List List;
typedef struct Queue Queue;

int QueueAddElement(Queue* queue, int elNumber);
int DrawQueueElementNumber(Queue* queue);
bool IsQueueEmpty(Queue* queue);
void DeleteQueue(Queue* queue);
int* ReadGraph(int* edgesAmount, FILE* filePtr);
int** CreateAdjacencyMatrix(int* graph, int edgesAmount, int verticesAmount);
void BreadthFirstSearch(FILE* filePtr);
void StressTest();
