#pragma once

#include <map>
#include "../../Memory/include/PoolAllocator.h"
#include <unordered_map>
#include "Component.h"
#include "Entity.h"


namespace ECS
{
	class IComponentCollection
	{
		
	};

	class EntityComponentSystem;

	template<class T>
	class ComponentCollection : public IComponentCollection
	{
	private:
		MemoryManager::PoolAllocator componentAllocator;
		EntityComponentSystem* ecsInstance;
	public:
		ComponentCollection(EntityComponentSystem* ecsInstance_) : componentAllocator(sizeof(T) * 100, sizeof(T)) { ecsInstance = ecsInstance_; }


		static const ClassID classID;

		using EntityComponentMap = std::map<EntityID, IComponent*>;
		using ComponentEntityMap = std::map<ComponentID, IEntity*>;

		EntityComponentMap entityComponentMap;
		ComponentEntityMap componentEntityMap;


		template<class T,class E, class... Args>
		ComponentHandle CreateComponent(EntityHandle eHandle,Args... args)
		{
			T* component = MemoryManager::Allocate<T>(componentAllocator, std::forward<Args>(args)...);
			entityComponentMap[eHandle.entityId] = component;
			componentEntityMap[component->componentID] = ecsInstance->GetEntity<E>(eHandle);

			return ComponentHandle(component->componentID, component->classID);
		}

		template<class T>
		IComponent* GetComponent(EntityHandle handle)
		{
			return entityComponentMap[handle.entityId];
		}

	};

	template<class T>
	const ClassID ComponentCollection<T>::classID = FamilyID<IComponentCollection>::Get<T>();

	class ComponentManager
	{
	private:
		EntityComponentSystem* ecsInstance;
	public:
		ComponentManager(EntityComponentSystem* ecsInstance_) { ecsInstance = ecsInstance_; }

		using ComponentCollectionMap = std::unordered_map<ClassID, IComponentCollection*>;

		ComponentCollectionMap collectionMap;

		template<class T>
		ComponentCollection<T>* GetComponentCollection()
		{
			auto it = collectionMap.find(T::classID);
			ComponentCollection<T>* collection = nullptr;

			if (it == collectionMap.end())
			{
				collection = new ComponentCollection<T>(ecsInstance);
				collectionMap[T::classID] = collection;
			}
			else
			{
				collection = static_cast<ComponentCollection<T>*>(it->second);
			}

			return collection;
		}

	public:
	
		template<class T,class E,class... Args>
		ComponentHandle CreateComponent(EntityHandle eHandle,Args... args)
		{
			ComponentCollection<T>* collection = GetComponentCollection<T>();
			return collection->CreateComponent<T,E>(eHandle,std::forward<Args>(args)...);
		}
		
		template<class T>
		IComponent* GetComponent(EntityHandle handle)
		{
			ComponentCollection<T>* collection = GetComponentCollection<T>();
			return collection->GetComponent<T>(handle);
		}

	};

	
}