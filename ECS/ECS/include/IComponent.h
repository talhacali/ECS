#pragma once

namespace ECS
{
	using ComponentID = unsigned int;

	class IComponent
	{
	public:
		ComponentID componentID;
	};
}
