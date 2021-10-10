#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memallocator.h"

#define MAX_ITERS 10000
#define MAX_BLOCK_SIZE 1000
#define MAX_MEM_POOL_SIZE 10000

double mallocTime[MAX_ITERS];
double memallocTime[MAX_ITERS];

void MallocTest(int iters) {
	unsigned long start = clock();

	for (int i = 0; i < iters; i++) {
		void* ptr = malloc((rand() % MAX_BLOCK_SIZE));
		free(ptr);
	}

	mallocTime[iters] = ((double)clock() - start) / CLOCKS_PER_SEC;
}

void MemallocTest(int iters) {
	unsigned long start = clock();

	for (int i = 0; i < iters; i++) {
		void* ptr = memalloc((rand() % MAX_BLOCK_SIZE));
		memfree(ptr);
	}

	memallocTime[iters] = ((double)clock() - start) / CLOCKS_PER_SEC;
}

int main()
{
	srand(time(NULL));

	FILE* filePtr = fopen("output.txt", "w+");
	if (filePtr == NULL)
	{
		return 1;
	}

	size_t memSize = MAX_MEM_POOL_SIZE + memgetminimumsize();
	void* memPtr = malloc(memSize);

	meminit(memPtr, memSize);
	for (int curIters = 1; curIters <= MAX_ITERS; ++curIters)
	{
		MallocTest(curIters);
		MemallocTest(curIters);
		//fprintf(filePtr, "%d\t%lf\t%lf\n", curIters, mallocTime[curIters - 1], memallocTime[curIters - 1]);
		//fprintf(filePtr, "%lf, ", mallocTime[curIters - 1]);
		fprintf(filePtr, "%lf, ", memallocTime[curIters - 1]);
	}

	fclose(filePtr);

	free(memPtr);

	return 0;
}
