#pragma once

#include "IComponent.h"
#include "FamilyId.h"

namespace ECS
{
	class ComponentHandle
	{
	public:
		ComponentHandle(unsigned int componentID_,unsigned int classID_) : componentId(componentID_), classID(classID_){}
		ComponentID componentId;
		ClassID classID;
	};

	template<class T>
	class Component : public IComponent
	{
	public:
		static const ClassID classID;

		Component() { componentID = STATIC_ID_COUNTER++; }
	private:
		static ComponentID STATIC_ID_COUNTER;
	};

	template<class T>
	const ClassID Component<T>::classID = FamilyID<IComponent>::Get<T>();

	template<class T>
	ComponentID Component<T>::STATIC_ID_COUNTER = 0;

	
}