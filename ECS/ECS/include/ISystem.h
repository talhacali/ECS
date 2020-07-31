#pragma once

#include "Entity.h"

namespace ECS
{
	using SystemID = unsigned int;

	class ISystem
	{
	public:
		virtual void Init() = 0;
		virtual void Update(float dt) = 0;

		SystemID systemID;

	private:

	};
}
