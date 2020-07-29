#include "..\include\PoolAllocator.h"

namespace ECS
{
	namespace MemoryManager
	{
		PoolAllocator::PoolAllocator(size_t memSize, size_t _objectSize) : IAllocator(memSize), objectSize(_objectSize)
		{
			if (firstAddress != nullptr)
			{
				free(firstAddress);
			}

			firstAddress = malloc(memSize);
			usedMemorySize = 0;
			numberOfAllocs = 0;

			nodeNumber = memSize / objectSize;
			void* address = firstAddress;
			size_t nextAddress = (size_t)address;

			for (int i = 0; i < nodeNumber; i++)
			{
				freeList.push_back(address);
				nextAddress = nextAddress + objectSize;
				address = (void*)nextAddress;
				numberOfAllocs++;
			}
		}

		PoolAllocator::~PoolAllocator()
		{
			free(firstAddress);
			freeList.empty();
			usedMemorySize = 0;
			numberOfAllocs = 0;
		}

		void* PoolAllocator::Allocate(const size_t size, uint8_t alignment)
		{
			assert(size == objectSize);
			void* nextAddress = freeList.back();
			freeList.pop_back();
			numberOfAllocs--;
			usedMemorySize += objectSize;
			return nextAddress;
		}

		void PoolAllocator::Free(void* ptr)
		{
			assert(numberOfAllocs < nodeNumber);
			freeList.push_back(ptr);
			numberOfAllocs++;
			usedMemorySize -= objectSize;
		}

	}
}


