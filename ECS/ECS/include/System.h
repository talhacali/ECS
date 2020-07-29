#pragma once

#include "ISystem.h"
#include <vector>

namespace ECS
{
	class SystemHandle
	{
	public:
		SystemHandle(unsigned int systemID_, unsigned int classID_) : systemId(systemID_), classID(classID_) {}

		SystemID systemId;
		ClassID classID;
	};

	template<class T>
	class System : public ISystem
	{
	public:
		static const ClassID classID;

		std::vector<IEntity> entities;
		
		System() { systemID = STATIC_ID_COUNTER++; }

		virtual void Init() {};
		virtual void Update() {};

		void AddEntity(IEntity const &entity);
		void RemoveEntity(IEntity const &entity);

	private:
		static SystemID STATIC_ID_COUNTER;

	};

	template<class T>
	const ClassID System<T>::classID = FamilyID<ISystem>::Get<T>();

	template<class T>
	SystemID System<T>::STATIC_ID_COUNTER = 0;
	
	
}