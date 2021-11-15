#pragma once

#define SUCCESS 0
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

int AddOne(int* number, int count);
int CheckSum(int* arr, int* result, int count, int requireSum);
int FindSum(int* arr, int count, int requireSum);
int SizesSum();
void StressTest();
