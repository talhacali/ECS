#include <stdlib.h>
#include "..\include\LinearAllocator.h"

namespace ECS
{
    namespace MemoryManager
    {
        LinearAllocator::LinearAllocator(size_t memSize) : IAllocator(memSize)
        {
            if (firstAddress != nullptr)
            {
                free(firstAddress);
            }

            firstAddress = malloc(memSize);
            usedMemorySize = 0;
        }

        LinearAllocator::~LinearAllocator()
        {
            free(firstAddress);
        }

        void* LinearAllocator::Allocate(const size_t size, uint8_t alignment)
        {
            size_t padding = 0;
            size_t nextAddress = (size_t)firstAddress + usedMemorySize;

            if (alignment != 0)
                padding = MemoryManager::CalculatePadding(nextAddress, alignment);

            nextAddress = nextAddress + padding;

            void* ptr = (void*)nextAddress;

            usedMemorySize += size + padding;

            return ptr;
        }

        void LinearAllocator::Free(void* ptr)
        {
            usedMemorySize = 0;
        }
    }
}




