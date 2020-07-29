#pragma once
#include "IEntity.h"
#include "FamilyId.h"

namespace ECS
{ 
	class EntityHandle
	{
	public:
		EntityHandle(unsigned int entityID_,unsigned int classID_) : entityId(entityID_), classID(classID_){}

		EntityID entityId;
		ClassID classID;
	};

	template<class T>
	class Entity : public IEntity
	{
	public:
		static const ClassID classID;
		Entity() { entityID = STATIC_ID_COUNTER++; }
	private:
		static EntityID STATIC_ID_COUNTER;
	};

	template<class T>
	const ClassID Entity<T>::classID = FamilyID<IEntity>::Get<T>();

	template<class T>
	EntityID Entity<T>::STATIC_ID_COUNTER = 0;
}