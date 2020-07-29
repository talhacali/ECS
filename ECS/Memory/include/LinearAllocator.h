#pragma once
#include "IAllocator.h"

namespace ECS
{
	namespace MemoryManager
	{
		class LinearAllocator : public IAllocator
		{
		public:
			LinearAllocator(size_t memSize);
			~LinearAllocator();
			virtual void* Allocate(const size_t size, uint8_t alignment) override;
			virtual void Free(void* ptr) override;
		};
	}

}

