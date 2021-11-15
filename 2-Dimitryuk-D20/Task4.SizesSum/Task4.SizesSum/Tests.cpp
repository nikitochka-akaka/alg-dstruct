#include "gtest/gtest.h"

extern "C"
{
#include <stdlib.h>
#include "SizesSum.h"
}


TEST(AddOneTest, NullPointer_err1)
{
	int count = rand() % 1000;

	int result = AddOne(NULL, count);

	EXPECT_TRUE(result == NULL_POINTER);
}

TEST(AddOneTest, InvalidCountZero_err2)
{
	int resultArr[2] = { 0 };

	int result = AddOne(resultArr, 0);

	EXPECT_TRUE(result == INVALID_COUNT);
}

TEST(AddOneTest, InvalidCountNegative_err2)
{
	int resultArr[2] = { 0 };

	int result = AddOne(resultArr, -rand());

	EXPECT_TRUE(result == INVALID_COUNT);
}

TEST(AddOneTest, NormalArguments_CorrectAnswer)
{
	int count = 2;
	int resultArr[2] = { 0, 1 };

	int result = AddOne(resultArr, count);

	EXPECT_TRUE((result == SUCCESS) && (resultArr[0] == 1) && (resultArr[1] == 0));
}

TEST(CheckSumTest, NullPointerArg1_err1)
{
	int count = 2;
	int resultArr[2] = { 0, 1 };

	int result = CheckSum(NULL, resultArr, count, rand() + 1);

	EXPECT_TRUE(result == NULL_POINTER);
}

TEST(CheckSumTest, NullPointerArg2_err1)
{
	int count = 2;
	int arr[2] = { 2, 3 };

	int result = CheckSum(arr, NULL, count, rand() + 1);

	EXPECT_TRUE(result == NULL_POINTER);
}

TEST(CheckSumTest, InvalidCountZero_err2)
{
	int arr[2] = { 2, 3 };
	int resultArr[2] = { 0, 1 };

	int result = CheckSum(arr, resultArr, 0, rand() + 1);

	EXPECT_TRUE(result == INVALID_COUNT);
}

TEST(CheckSumTest, InvalidCountNegative_err2)
{
	int arr[2] = { 2, 3 };
	int resultArr[2] = { 0, 1 };

	int result = CheckSum(arr, resultArr, -rand(), rand() + 1);

	EXPECT_TRUE(result == INVALID_COUNT);
}

TEST(CheckSumTest, InvalidRequireSum_err3)
{
	int count = 2;
	int arr[2] = { 2, 3 };
	int resultArr[2] = { 0, 1 };

	int result = CheckSum(arr, resultArr, count, 0);

	EXPECT_TRUE(result == INVALID_SUM);
}

TEST(CheckSumTest, NormalArguments_CorrectAnswerTRUE)
{
	int requireSum = 5;
	int count = 4;
	int arr[4] = { 2, 3, 1, 5 };
	int resultArr[4] = { 0, 0, 0, 1 };

	int result = CheckSum(arr, resultArr, count, requireSum);

	EXPECT_TRUE(result == TRUE);
}

TEST(CheckSumTest, NormalArguments_CorrectAnswerFALSE)
{
	int requireSum = 5;
	int count = 4;
	int arr[4] = { 2, 3, 1, 5 };
	int resultArr[4] = { 0, 0, 1, 1 };

	int result = CheckSum(arr, resultArr, count, requireSum);

	EXPECT_TRUE(result == FALSE);
}

TEST(FindSumTest, NullPointer_err1)
{
	int requireSum = 5;
	int count = 4;

	int result = FindSum(NULL, count, requireSum);

	EXPECT_TRUE(result == NULL_POINTER);
}

TEST(FindSumTest, InvalidCountZero_err2)
{
	int requireSum = 5;
	int arr[2] = { 1, 3 };

	int result = FindSum(arr, 0, requireSum);

	EXPECT_TRUE(result == INVALID_COUNT);
}

TEST(FindSumTest, InvalidCountNegative_err2)
{
	int requireSum = 5;
	int arr[2] = { 1, 3 };

	int result = FindSum(arr, -rand(), requireSum);

	EXPECT_TRUE(result == INVALID_COUNT);
}

TEST(FindSumTest, InvalidRequireSum_err3)
{
	int count = 2;
	int arr[2] = { 1, 3 };

	int result = FindSum(arr, count, 0);

	EXPECT_TRUE(result == INVALID_SUM);
}

TEST(FindSumTest, NormalArguments_CorrectAnswerTRUE)
{
	int requireSum = 10;
	int count = 5;
	int arr[5] = { 2, 3, 4, 5, 9 };

	int result = FindSum(arr, count, requireSum);

	EXPECT_TRUE(result == TRUE);
}

TEST(FindSumTest, NormalArguments_CorrectAnswerFALSE)
{
	int requireSum = 1;
	int count = 5;
	int arr[5] = { 2, 3, 4, 5, 9 };

	int result = FindSum(arr, count, requireSum);

	EXPECT_TRUE(result == FALSE);
}

TEST(SizesSumTest, FileDoesntExist_FileErr)
{
	int result = SizesSum();

	EXPECT_TRUE(result == FILE_ERROR);
}
