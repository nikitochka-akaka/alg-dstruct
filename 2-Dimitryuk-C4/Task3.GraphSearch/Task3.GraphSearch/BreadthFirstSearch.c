#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BreadthFirstSearch.h"

#define MAX_VERTECIES 2000
#define RAND 1 + rand() % 2000

int QueueAddElement(Queue* queue, int elNumber)
{
	if (queue == null)
	{
		fprintf(stderr, "QueueAddElement: Argument null pointer error\n");
		return 1;
	}

	List* queueElPtr = queue->queueList;
	while (queueElPtr != null)
	{
		if (queueElPtr->elNumber == elNumber)
		{
			return 1;
		}

		queueElPtr = queueElPtr->nextEl;
	}

	List* newEl = (List*)malloc(sizeof(List));
	if (newEl == null)
	{
		fprintf(stderr, "QueueAddElement: can't allocate memory for new queue element\n");
		return 1;
	}

	if (queue->queueList != null)
	{
		List* queueElPtr = queue->queueList;
		while (queueElPtr->nextEl != null)
		{
			queueElPtr = queueElPtr->nextEl;
		}

		queueElPtr->nextEl = newEl;
	}
	else
	{
		queue->queueList = newEl;
	}

	newEl->nextEl = null;
	newEl->elNumber = elNumber;

	return 0;
}

int DrawQueueElementNumber(Queue* queue)
{
	if (queue == null)
	{
		fprintf(stderr, "DrawQueueElementNumber: Argument null pointer error\n");
		return -1;
	}

	int result = queue->queueList->elNumber;
	List* nextEl = queue->queueList->nextEl;
	free(queue->queueList);
	queue->queueList = nextEl;
	
	return result;
}

bool IsQueueEmpty(Queue* queue)
{
	if (queue == null)
	{
		return true;
	}

	if (queue->queueList == null)
	{
		return true;
	}

	return false;
}

void DeleteQueue(Queue* queue)
{
	if (queue == null)
	{
		return;
	}

	if (queue->queueList == null)
	{
		free(queue);
		return;
	}

	List* curEl = queue->queueList;
	List* nextEl = curEl->nextEl;

	while (nextEl != null)
	{
		free(curEl);
		curEl = nextEl;
		nextEl = curEl->nextEl;

		if (nextEl == null)
		{
			free(curEl);
		}
	}
}

int* ReadGraph(int* edgesAmount, FILE* filePtr)
{
	size_t index = 0;

	char sym = '0';
	char str[BUFF_WIDTH] = { 0 };
	size_t i = 0;

	int* memCheck = null;
	int* graph = (int*)malloc(2 * (*edgesAmount + 1) * sizeof(int));
	if (graph == null)
	{
		fprintf(stderr, "BreadthFirstSearch: can't allocate memory for edges array");
		return null;
	}

	while ((sym = getc(filePtr)) != EOF)
	{
		if (sym == '\n')
		{
			sscanf(str, "%d %d", &graph[index], &graph[index + 1]);
			
			memset(str, '\0', BUFF_WIDTH);
			index += 2;

			(*edgesAmount)++;

			int* memCheck = null;
			memCheck = (int*)realloc(graph, 2 * (*edgesAmount + 1) * sizeof(int));
			if (memCheck == null)
			{
				return null;
			}
			else
			{
				graph = memCheck;
			}

			i = 0;
		}
		else
		{
			str[i] = sym;
			++i;
		}
	}

	return graph;
}

int** CreateAdjacencyMatrix(int* graph, int edgesAmount, int verticesAmount)
{
	int** graphMatrix = (int**)malloc(verticesAmount * sizeof(int*));
	if (graphMatrix == null)
	{
		return null;
	}

	for (int i = 0; i < verticesAmount; ++i)
	{
		graphMatrix[i] = (int*)calloc(verticesAmount, sizeof(int));
		if (graphMatrix[i] == null)
		{
			free(graphMatrix);
			return null;
		}
	}

	for (int i = 0; i < 2 * edgesAmount - 2; i += 2)
	{
		graphMatrix[graph[i]][graph[i + 1]] = 1;
		graphMatrix[graph[i + 1]][graph[i]] = 1;
	}

	return graphMatrix;
}

void BreadthFirstSearch(FILE* filePtr)
{
	if (filePtr == null)
	{
		filePtr = stdin;
	}

	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == null)
	{
		fprintf(stderr, "BreadthFirstSearch: can't allocate memory for queue");
		return null;
	}

	queue->queueList = null;

	int verticesAmount = 0;
	if (fscanf(filePtr, "%d\n", &verticesAmount) != 1)
	{
		return;
	}
	int* wasArray = (int*)calloc(verticesAmount, sizeof(int));
	if (wasArray == null)
	{
		fprintf(stderr, "BreadthFirstSearch: can't allocate memory for visited vertices array");
		return null;
	}

	size_t edgesAmount = 0;
	int* graph = ReadGraph(&edgesAmount, filePtr);

	int** graphMatrix = CreateAdjacencyMatrix(graph, edgesAmount, verticesAmount);

	QueueAddElement(queue, 0);
	size_t index = 0;
	bool was = false;
	while (!IsQueueEmpty(queue))
	{
		int el = DrawQueueElementNumber(queue);
		wasArray[index] = el;
		for (int i = 0; i < verticesAmount; ++i)
		{
			if (graphMatrix[el][i] == 1)
			{
				for (int j = 0; j < verticesAmount; ++j)
				{
					if (wasArray[j] == i)
					{
						was = true;
						break;
					}
				}

				if (was)
				{
					was = false;
					continue;
				}

				QueueAddElement(queue, i);
			}
		}
		index++;
	}

	for (int i = 0; i < verticesAmount; ++i)
	{
		if ((i > 0) && (wasArray[i] == 0))
		{
			continue;
		}

		printf("%d ", wasArray[i]);
	}

	free(wasArray);
	DeleteQueue(queue);
	for (int i = 0; i < verticesAmount; ++i)
	{
		free(graphMatrix[i]);
	}
	free(graphMatrix);
}

void StressTest()
{
	FILE* filePtr = fopen("../../Task3.GraphGenerator/Task3.GraphGenerator/Graph.txt", "w+");
	if (filePtr == null)
	{
		return;
	}

	srand(time(null));

	fprintf(filePtr, "%d\n", MAX_VERTECIES + 1);
	fprintf(filePtr, "0 1\n");

	for (int i = 0, vertex = 0; i < MAX_VERTECIES; i++)
	{
		if ((vertex = RAND) != (i + 1))
		{
			fprintf(filePtr, "%d %d\n", i + 1, RAND);
			--i;
		}
		else
		{
			fprintf(filePtr, "%d %d\n", vertex, RAND);
		}
	}

	fprintf(filePtr, "\n");

	fseek(filePtr, SEEK_SET, 0);

	BreadthFirstSearch(filePtr);

	fclose(filePtr);
}
