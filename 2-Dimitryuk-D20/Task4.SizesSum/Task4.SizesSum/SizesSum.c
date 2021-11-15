#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "SizesSum.h"

/**
 * CPU: Intel(R) Core(TM) i5-8300H CPU 2.30GHz
 * RAM: Single-Channel 1200 MHz 17-17-17-39
 * SSD: NVMe 4x 8 GT/s
 *
 * Stress test results:
 *	   Memory used: 765.02 MB
 *	   Algorithm execution time: 49 seconds
*/

int AddOne(int* number, int count)
{
	if (number == NULL)
	{
		fprintf(stderr, "\n\nAddOne: Argument null pointer error\n\n");

		return NULL_POINTER;
	}

	if (count <= 0)
	{
		fprintf(stderr, "\n\nAddOne: Count variable invalid value\n\n");

		return INVALID_COUNT;
	}

	int r = 0;

	if (number[count - 1] == 0)
	{
		number[count - 1] = 1;

		return SUCCESS;
	}
	else
	{
		number[count - 1] = 0;

		r = 1;
	}

	for (int i = count - 2; i >= 0; --i)
	{
		if (r == 0)
		{
			return SUCCESS;
		}
		else
		{
			if (number[i] == 1)
			{
				number[i] = 0;
			}
			else
			{
				number[i] = 1;
				r = 0;
			}
		}
	}

	return SUCCESS;
}

int CheckSum(int* arr, int* result, int count, int requireSum)
{
	if ((arr == NULL) || (result == NULL))
	{
		fprintf(stderr, "\n\nCheckSum: Argument null pointer error\n\n");

		return NULL_POINTER;
	}

	if (count <= 0)
	{
		fprintf(stderr, "\n\nCheckSum: Count variable invalid value\n\n");

		return INVALID_COUNT;
	}

	if (requireSum == 0)
	{
		fprintf(stderr, "\n\nCheckSum: RequireSum variable invalid value\n\n");

		return INVALID_SUM;
	}

	int curSum = 0;

	for (int i = 0; i < count; ++i)
	{
		if (result[i] == 1)
		{
			curSum += arr[i];
		}
	}

	if (curSum == requireSum)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int FindSum(int* arr, int count, int requireSum)
{
	if (arr == NULL)
	{
		fprintf(stderr, "\n\nFindSum: Argument null pointer error\n\n");

		return NULL_POINTER;
	}

	if (count <= 0)
	{
		fprintf(stderr, "\n\nFindSum: Count variable invalid value\n\n");

		return INVALID_COUNT;
	}

	if (requireSum == 0)
	{
		fprintf(stderr, "\n\nFindSum: RequireSum variable invalid value\n\n");

		return INVALID_SUM;
	}

	int* result = (int*)calloc(count, sizeof(int));
	if (result == NULL)
	{
		fprintf(stderr, "\n\nFindSum: can't allocate memory for result array\n\n");

		return MEM_ERROR;
	}

	int amount = pow(2, count) - 1;

	for (int i = 0; i < amount; ++i)
	{
		AddOne(result, count);

		if (CheckSum(arr, result, count, requireSum))
		{
			for (int j = 0; j < count; ++j)
			{
				if (result[j] == 1)
				{
					printf("%d ", arr[j]);
				}
			}

			free(result);

			return TRUE;
		}
	}

	free(result);

	printf("0");

	return FALSE;
}

int SizesSum()
{
	FILE* inPtr = fopen("input.txt", "r");
	if (inPtr == NULL)
	{
		fprintf(stderr, "\n\nSizesSum: can't open input.txt file\n\n");

		return FILE_ERROR;
	}

	int count = 0;
	unsigned int requireSum = 0;

	fscanf(inPtr, "%d\n", &requireSum);
	fscanf(inPtr, "%d\n", &count);

	int* arr = (int*)calloc(count, sizeof(int));
	if (arr == NULL)
	{
		fprintf(stderr, "\n\nSizesSum: can't allocate memory for main array\n\n");

		return MEM_ERROR;
	}

	for (int i = 0; i < count; ++i)
	{
		fscanf(inPtr, "%d ", &(arr[i]));
	}

	fclose(inPtr);

	int result = FindSum(arr, count, requireSum);

	free(arr);

	return result;
}

void StressTest()
{
	FILE* outPtr = fopen("input.txt", "w");
	if (outPtr == NULL)
	{
		fprintf(stderr, "\n\nStressTest: can't open input.txt file\n\n");

		return;
	}

	srand(time(NULL));

	int n = 0;

	fprintf(outPtr, "%d\n", rand() % UINT_MAX);
	fprintf(outPtr, "%d\n", n = 200000000);

	for (int i = 0; i < n; ++i)
	{
		fprintf(outPtr, "%d ", (rand() % (USHRT_MAX + 2)));
	}

	unsigned long long start = clock();

	SizesSum();

	unsigned long long end = clock();

	printf("\n\nTime: %llu\n\n", (end - start) / CLK_TCK);
}
