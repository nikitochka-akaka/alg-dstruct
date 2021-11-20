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
 *     Number: 50'000'000
 * 
 *	   Memory used: 306.84 MB
 *	   Algorithm execution time: 45 seconds
*/

int FindSum(int* arr, char* result, int count, int requireSum)
{
	if (arr == NULL)
	{
		fprintf(stderr, "\n\nFindSum: Argument null pointer error\n\n");

		return NULL_POINTER;
	}

	if (result == NULL)
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

	if (Backtracking(arr, result, count, requireSum, START, START))
	{
		for (int i = 0; i < count; ++i)
		{
			if (result[i])
			{
				printf("%d ", arr[i]);
			}
		}

		return TRUE;
	}
	else
	{
		printf("0");
	}

	return FALSE;
}

char Backtracking(int* arr, char* result, int count, int requireSum, int curSum, int curPos)
{
	int tmp = 0;

	for (int i = curPos; i < count; ++i)
	{
		if (!result[i])
		{
			tmp = arr[i];

			if (curSum + tmp == requireSum)
			{
				result[i] = TRUE;
				return TRUE;
			}

			if (curSum + tmp > requireSum)
			{
				if (i != (count - 1))
				{
					continue;
				}
				else
				{
					result[i] = FALSE;
					return FALSE;
				}
			}

			if (curSum + tmp < requireSum)
			{
				result[i] = TRUE;
				if (Backtracking(arr, result, count, requireSum, curSum + tmp, i))
				{
					return TRUE;
				}
				else
				{
					if (i != (count - 1))
					{
						result[i] = FALSE;
						continue;
					}
					else
					{
						result[i] = FALSE;
						return FALSE;
					}
				}
			}
		}
		else
		{
			if (i != (count - 1))
			{
				continue;
			}
			else
			{
				return FALSE;
			}
		}
	}
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

	int newCount = count;
	for (int i = 0; i < count; ++i)
	{
		if (arr[i] > requireSum)
		{
			newCount--;
		}

		if (arr[i] == requireSum)
		{
			printf("%d", arr[i]);
			free(arr);
			return;
		}
	}

	int* newArr = (int*)malloc(newCount * sizeof(int));
	if (newArr == NULL)
	{
		free(arr);
		return;
	}

	for (int i = 0, j = 0; i < count; ++i)
	{
		if (arr[i] < requireSum)
		{
			newArr[j] = arr[i];
			j++;
		}
	}

	char* result = (char*)calloc(count, sizeof(char));
	if (result == NULL)
	{
		fprintf(stderr, "\n\nFindSum: can't allocate memory for result array\n\n");

		return MEM_ERROR;
	}

	int findSumResult = FindSum(newArr, result, newCount, requireSum);

	free(arr);

	return findSumResult;
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
	int sum = 0;
	int tmp = 0;

	fprintf(outPtr, "%d\n", sum = (rand() % UINT_MAX));
	fprintf(outPtr, "%d\n", n = 50000000);

	for (int i = 0; i < n; ++i)
	{
		if ((tmp = (rand() % (USHRT_MAX + 2))) != sum)
		{
			fprintf(outPtr, "%d ", tmp);
		}
	}

	fclose(outPtr);

	unsigned long long start = clock();

	SizesSum();

	unsigned long long end = clock();

	printf("\n\nTime: %llu\n\n", (end - start) / CLK_TCK);
}
