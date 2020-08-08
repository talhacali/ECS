#pragma once

#include "../../Memory/include/PoolAllocator.h"
#include "Entity.h"
#include <unordered_map>


#include <iostream>

namespace ECS
{

	class IEntityCollection
	{
		
	public:
		MemoryManager::PoolAllocator entityAllocator;
		using EntityMap = std::unordered_map<EntityID, IEntity*>;
		EntityMap entityMap;

		IEntityCollection(size_t memsize, size_t objectsize) : entityAllocator(memsize,objectsize)
		{

		}

		~IEntityCollection()
		{
			for (auto it : entityMap)
			{
				std::cout << "Destructor" << std::endl;
				entityAllocator.Free(it.second);
			}
		}
	};

	template<class T>
	class EntityCollection : public IEntityCollection
	{
		
		//using EntityMap = std::unordered_map<EntityID, IEntity*>;

	public:
		EntityCollection() : IEntityCollection(sizeof(T) * 100,sizeof(T))  {}

		static const ClassID classID;

		template<class T, class... Args>
		EntityHandle CreateEntity(Args... args)
		{
			T* entity = MemoryManager::Allocate<T>(entityAllocator, std::forward<Args>(args)...);

			entityMap[entity->entityID] = entity;

			return EntityHandle(entity->entityID, entity->classID);
		}

		template<class T>
		void DeleteEntity(const EntityHandle& handle)
		{
			T* entity = static_cast<T*>(GetEntity<T>(handle));
			MemoryManager::Delete<T>(entityAllocator, entity);
			entityMap.erase(handle.entityId);
		}

		template<class T>
		IEntity* GetEntity(const EntityHandle& handle)
		{
			if (entityMap.find(handle.entityId) == entityMap.end())
				return nullptr;
			
			return entityMap[handle.entityId];
		}


	};

	template<class T>
	const ClassID EntityCollection<T>::classID = FamilyID<IEntityCollection>::Get<T>();


	class EntityManager
	{		

		using EntityCollectionMap = std::unordered_map<ClassID, IEntityCollection*>;

		EntityCollectionMap collectionMap;

		template<class T>
		EntityCollection<T>* GetEntityCollection()
		{
			auto it = collectionMap.find(T::classID);
			EntityCollection<T>* collection = nullptr;

			if (it == collectionMap.end())
			{
				collection = new EntityCollection<T>();
				collectionMap[T::classID] = collection;
			}
			else
			{
				collection = static_cast<EntityCollection<T>*>(it->second);
			}

			return collection;
		}

		

	public:
		~EntityManager()
		{
			for (auto it : collectionMap)
			{
				delete it.second;
			}
		}

		template<class T, class... Args>
		EntityHandle CreateEntity(Args... args)
		{
			EntityCollection<T>* collection = GetEntityCollection<T>();

			return collection->CreateEntity<T>(std::forward<Args>(args)...);
		}

		template<class T>
		void DeleteEntity(const EntityHandle& handle)
		{
			EntityCollection<T>* collection = GetEntityCollection<T>();

			collection->DeleteEntity<T>(handle);
		}

		template<class T>
		IEntity* GetEntity(const EntityHandle& handle)
		{
			EntityCollection<T>* collection = GetEntityCollection<T>();
			return collection->GetEntity<T>(handle);
		}
	};
}