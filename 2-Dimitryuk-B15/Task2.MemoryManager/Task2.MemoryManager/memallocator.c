#include <stdio.h>
#include "memallocator.h"

#define INT_MAX 2147483647
#define TRUE 1
#define FALSE 0

struct Block
{
	struct Block* prevBlock;
	struct Block* nextBlock;
	size_t blockSize;
	char isAllocated;
};

typedef Block MemoryManager;

MemoryManager* __Manager = NULL;
size_t __fullSize = 0;

inline void* __MemBlockPtr(struct Block* blockPtr)
{
	return (void*)(blockPtr + 1);
}

struct Block* __FindBestBlock(size_t size)
{
	#pragma region FeasibilityCheck

	if (__Manager == NULL)
	{
		return NULL;
	}

	#pragma endregion

	struct Block* blockPtr = __Manager;
	struct Block* bestBlockPtr = NULL;
	while (blockPtr != NULL)
	{
		if (blockPtr->isAllocated == FALSE)
		{
			if (blockPtr->blockSize >= size)
			{
				if ((bestBlockPtr == NULL ? INT_MAX : bestBlockPtr->blockSize) > blockPtr->blockSize)
				{
					bestBlockPtr = blockPtr;
				}
			}
		}
		
		blockPtr = blockPtr->nextBlock;
	}

	return bestBlockPtr;
}

void* __InsertNewBlock(struct Block* destBlock, size_t size)
{
	#pragma region FeasibilityCheck

	if (__Manager == NULL)
	{
		return NULL;
	}

	if (destBlock == NULL)
	{
		return NULL;
	}

	if (destBlock->isAllocated == TRUE)
	{
		return NULL;
	}

	#pragma endregion

	if (destBlock->blockSize - size > sizeof(MemoryManager))
	{
		struct Block* newBlock = (struct Block*)((char*)__MemBlockPtr(destBlock) + size);

		newBlock->blockSize = destBlock->blockSize - size - sizeof(MemoryManager);
		newBlock->isAllocated = FALSE;
		newBlock->nextBlock = destBlock->nextBlock;
		newBlock->prevBlock = destBlock;
		if (destBlock->nextBlock != NULL)
		{
			destBlock->nextBlock->prevBlock = newBlock;
		}
		destBlock->nextBlock = newBlock;
	}
	
	destBlock->blockSize = size;
	destBlock->isAllocated = TRUE;

	return __MemBlockPtr(destBlock);
}

int __GetCurrentFreeSize()
{
	#pragma region FeasibilityCheck

		if (__Manager == NULL)
		{
			return -1;
		}

	#pragma endregion

	struct Block* blockPtr = __Manager;
	int curSize = 0;
	while (blockPtr != NULL)
	{
		if (blockPtr->isAllocated == FALSE)
		{
			curSize += blockPtr->blockSize;
		}

		blockPtr = blockPtr->nextBlock;
	}

	return curSize + sizeof(MemoryManager);
}

struct Block* __GetBlockPtrFromFirstCell(void* cellPtr)
{
	struct Block* foundBlock = (struct Block*)cellPtr - 1;
	struct Block* blockPtr = __Manager;

	while (blockPtr != NULL)
	{
		if (blockPtr == foundBlock)
		{
			return foundBlock;
		}

		blockPtr = blockPtr->nextBlock;
	}

	return NULL;
}

int meminit(void* pMemory, int size)
{
	#pragma region FeasibilityCheck

	if (__Manager != NULL)
	{
		return 1;
	}

	if (size < sizeof(MemoryManager))
	{
		return 2;
	}

	if (pMemory == NULL)
	{
		return 3;
	}

	#pragma endregion

	__Manager = (MemoryManager*)pMemory;

	__Manager->blockSize = size - sizeof(MemoryManager);
	__Manager->nextBlock = NULL;
	__Manager->prevBlock = NULL;
	__Manager->isAllocated = FALSE;

	__fullSize = size;

	return 0;
}

void memdone()
{
	#pragma region FeasibilityCheck

		if (__Manager == NULL)
		{
			return;
		}

	#pragma endregion

	int curSise = __GetCurrentFreeSize();
	if (curSise == -1)
	{
		return;
	}
	
	if (curSise < __fullSize)
	{
		fprintf(stderr, "Memory leak detected:\n\t\texpected size: %d\tgot: %d\n", __fullSize, curSise);
	}
}

void* memalloc(int size)
{
	#pragma region FeasibilityCheck

	if (__Manager == NULL)
	{
		return NULL;
	}

	#pragma endregion

	struct Block* destBlockPtr = __FindBestBlock(size);
	if (destBlockPtr == NULL)
	{
		fprintf(stderr, "Memory alloc: Can't find block, not enough space\n");

		return 0;
	}

	void* memBlockPtr = __InsertNewBlock(destBlockPtr, size);
	if (memBlockPtr == NULL)
	{
		return 0;
	}

	return memBlockPtr;
}

void memfree(void* p)
{
	#pragma region FeasibilityCheck

	if (p == NULL)
	{
		return;
	}

	#pragma endregion

	struct Block* deleteBlock = __GetBlockPtrFromFirstCell(p);
	if (deleteBlock == NULL)
	{
		fprintf(stderr, "Memory free: Invalid pointer, can't find block\n");

		return;
	}

	if (deleteBlock->isAllocated == FALSE)
	{
		fprintf(stderr, "Memfree: block isn't allocated\n");
		
		return;
	}

	struct Block* mergeBufferBlock = deleteBlock;
	mergeBufferBlock->isAllocated = FALSE;

	if (deleteBlock->prevBlock != NULL)
	{
		if (deleteBlock->prevBlock->isAllocated == FALSE)
		{
			deleteBlock->isAllocated = FALSE;
			size_t summarySize = 0;
			if (deleteBlock->nextBlock != NULL)
			{
				summarySize = (char*)deleteBlock->nextBlock - (char*)(deleteBlock->prevBlock + 1);
			}
			else
			{
				summarySize = (char*)(__Manager + 1) + __fullSize - (char*)(deleteBlock->prevBlock + 1);
			}
			
			deleteBlock->prevBlock->nextBlock = deleteBlock->nextBlock;
			if (deleteBlock->nextBlock != NULL)
			{
				deleteBlock->nextBlock->prevBlock = deleteBlock->prevBlock;
			}

			deleteBlock->prevBlock->blockSize = summarySize;

			mergeBufferBlock = deleteBlock->prevBlock;
		}
	}

	if (mergeBufferBlock->nextBlock != NULL)
	{
		if (mergeBufferBlock->nextBlock->isAllocated == FALSE)
		{
			mergeBufferBlock->isAllocated = FALSE;
			size_t summarySize = 0;
			if (mergeBufferBlock->nextBlock->nextBlock != NULL)
			{
				summarySize = (char*)mergeBufferBlock->nextBlock->nextBlock - (char*)(mergeBufferBlock + 1);
			}
			else
			{
				summarySize = (char*)(__Manager + 1) + __fullSize - (char*)(mergeBufferBlock + 1);
			}

			
			if (mergeBufferBlock->nextBlock->nextBlock != NULL)
			{
				mergeBufferBlock->nextBlock->nextBlock->prevBlock = mergeBufferBlock;
			}
			mergeBufferBlock->nextBlock = mergeBufferBlock->nextBlock->nextBlock;

			mergeBufferBlock->blockSize = summarySize;
		}
	}

	if (mergeBufferBlock->nextBlock != NULL)
	{
		if ((void*)((char*)(mergeBufferBlock + 1) + mergeBufferBlock->blockSize) != mergeBufferBlock->nextBlock)
		{
			void* unallocMemPtr = (void*)((char*)(mergeBufferBlock + 1) + mergeBufferBlock->blockSize);
			size_t unallocMemSize = (char*)mergeBufferBlock->nextBlock - (char*)unallocMemPtr;

			mergeBufferBlock->blockSize += unallocMemSize;
		}
	}
	else
	{
		if ((void*)((char*)__Manager + __fullSize) != (void*)((char*)(mergeBufferBlock + 1) + mergeBufferBlock->blockSize))
		{
			void* unallocMemPtr = (void*)((char*)(mergeBufferBlock + 1) + mergeBufferBlock->blockSize);
			size_t unallocMemSize = (char*)__Manager + __fullSize - (char*)unallocMemPtr;

			mergeBufferBlock->blockSize += unallocMemSize;
		}
	}
}

int memgetminimumsize()
{
	return sizeof(struct Block);
}

int memgetblocksize()
{
	return sizeof(struct Block);
}
