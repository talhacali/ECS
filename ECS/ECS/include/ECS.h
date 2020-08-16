#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include "../../Memory/include/PoolAllocator.h"
#include <memory>

namespace ECS
{
	class EntityComponentSystem
	{
	public:
		EntityComponentSystem() : entityManagerAllocator(sizeof(EntityManager),sizeof(EntityManager)),
			componentManagerAllocator(sizeof(ComponentManager), sizeof(ComponentManager)),
			systemManagerAllocator(sizeof(SystemManager),sizeof(SystemManager))
		{
			entityManager = MemoryManager::Allocate<EntityManager>(entityManagerAllocator);
			componentManager = MemoryManager::Allocate<ComponentManager>(componentManagerAllocator,this);
			systemManager = MemoryManager::Allocate<SystemManager>(systemManagerAllocator);

		}

		~EntityComponentSystem()
		{
			MemoryManager::Delete<EntityManager>(entityManagerAllocator, entityManager);
			MemoryManager::Delete<ComponentManager>(componentManagerAllocator, componentManager);
			MemoryManager::Delete<SystemManager>(systemManagerAllocator, systemManager);

		}



		template<class T, class... Args>
		EntityHandle CreateEntity(Args... args)
		{
			return entityManager->CreateEntity<T>(std::forward<Args>(args)...);
		}

		template<class E,class C,class S>
		void DeleteEntity(const EntityID& entityID,const ComponentHandle& componentHandle, const SystemID& systemID)
		{
			systemManager->UnregisterEntity<S>(systemID, entityID);
			componentManager->DeleteComponent<C>(componentHandle, entityID);
			entityManager->DeleteEntity<E>(entityID);
		}

		template<class T,class E, class... Args>
		ComponentHandle CreateComponent(EntityID entityID,Args... args)
		{
			return componentManager->CreateComponent<T,E>(entityID,std::forward<Args>(args)...);
		}

		template<class T,class... Args>
		SystemHandle CreateSystem(Args... args)
		{
			return systemManager->CreateSystem<T>(std::forward<Args>(args)...);
		}

		template<class T>
		IEntity* GetEntity(const EntityID& entityID)
		{
			return entityManager->GetEntity<T>(entityID);
		}

		template<class T>
		IComponent* GetComponent(const EntityID& entityID)
		{
			return componentManager->GetComponent<T>(entityID);
		}

		template<class T>
		ISystem* GetSystem(const SystemID& systemID)
		{
			return systemManager->GetSystem<T>(systemID);
		}

		template<class T>
		void RegisterEntity(const SystemID& systemID,const EntityID& entityID)
		{
			systemManager->RegisterEntity<T>(systemID, entityID);
		}

		template<class T>
		void UnregisterEntity(const SystemID& systemID, const EntityID& entityID)
		{
			systemManager->UnregisterEntity<T>(systemID, entityID);
		}

		void Init()
		{
			systemManager->Init();
		}

		void Update(float dt)
		{
			systemManager->Update(dt);
		}

	public:
		MemoryManager::PoolAllocator entityManagerAllocator;
		MemoryManager::PoolAllocator componentManagerAllocator;
		MemoryManager::PoolAllocator systemManagerAllocator;

		EntityManager* entityManager;
		ComponentManager* componentManager;
		SystemManager* systemManager;
	};
}
