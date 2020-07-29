#pragma once


namespace ECS
{
	using EntityID = unsigned int;

	class IEntity
	{
	public:
		EntityID entityID;
	};
}