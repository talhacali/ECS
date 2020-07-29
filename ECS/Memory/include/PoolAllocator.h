#pragma once
#include "IAllocator.h"
#include <list>

namespace ECS
{
	namespace MemoryManager
	{
		class PoolAllocator : public IAllocator
		{
		public:
			PoolAllocator(size_t memSize, size_t _objectSize);
			~PoolAllocator();
			virtual void* Allocate(const size_t size, uint8_t alignment) override;
			virtual void Free(void* ptr) override;
		private:
			std::list<void*> freeList;
			size_t objectSize;
			int nodeNumber;
			int numberOfAllocs;
		};
	}

}

