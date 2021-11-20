#pragma once

#define START 0
#define TRUE 1
#define FALSE !TRUE

enum Errors
{
	NULL_POINTER = 2,
	INVALID_COUNT,
	INVALID_SUM,
	MEM_ERROR,
	FILE_ERROR
};

char Backtracking(int* arr, char* result, int count, int requireSum, int curSum, int curPos);
int FindSum(int* arr, char* result, int count, int requireSum);
int SizesSum();
void StressTest();
