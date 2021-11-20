#include "gtest/gtest.h"

extern "C"
{
#include <stdlib.h>
#include "SizesSum.h"
}

TEST(FindSumTest, NullPointerArg1_err1)
{
	char resultArr[4] = { 0, 0, 0, 0 };
	int requireSum = 5;
	int count = 4;

	int result = FindSum(NULL, resultArr, count, requireSum);

	EXPECT_TRUE(result == NULL_POINTER);
}

TEST(FindSumTest, NullPointerArg2_err1)
{
	int arr[4] = { 1, 5, 3, 4 };
	int requireSum = 5;
	int count = 4;

	int result = FindSum(arr, NULL, count, requireSum);

	EXPECT_TRUE(result == NULL_POINTER);
}

TEST(FindSumTest, InvalidCountZero_err2)
{
	char resultArr[4] = { 0, 0, 0, 0 };
	int arr[2] = { 1, 3 };
	int requireSum = 5;

	int result = FindSum(arr, resultArr, 0, requireSum);

	EXPECT_TRUE(result == INVALID_COUNT);
}

TEST(FindSumTest, InvalidCountNegative_err2)
{
	char resultArr[4] = { 0, 0, 0, 0 };
	int arr[2] = { 1, 3 };
	int requireSum = 5;

	int result = FindSum(arr, resultArr, -rand(), requireSum);

	EXPECT_TRUE(result == INVALID_COUNT);
}

TEST(FindSumTest, InvalidRequireSum_err3)
{
	char resultArr[4] = { 0, 0, 0, 0 };
	int arr[2] = { 1, 3 };
	int count = 2;

	int result = FindSum(arr, resultArr, count, 0);

	EXPECT_TRUE(result == INVALID_SUM);
}

TEST(FindSumTest, NormalArguments_CorrectAnswerTRUE)
{
	char resultArr[5] = { 0, 0, 0, 0, 0 };
	int arr[5] = { 2, 3, 4, 5, 9 };
	int requireSum = 10;
	int count = 5;

	int result = FindSum(arr, resultArr, count, requireSum);

	EXPECT_TRUE(result == TRUE);
}

TEST(FindSumTest, NormalArguments_CorrectAnswerFALSE)
{
	char resultArr[5] = { 0, 0, 0, 0, 0 };
	int arr[5] = { 2, 3, 4, 5, 9 };
	int requireSum = 1;
	int count = 5;

	int result = FindSum(arr, resultArr, count, requireSum);

	EXPECT_TRUE(result == FALSE);
}

TEST(SizesSumTest, FileDoesntExist_FileErr)
{
	int result = SizesSum();

	EXPECT_TRUE(result == FILE_ERROR);
}
