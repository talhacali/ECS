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

		template<class T,class E, class... Args>
		ComponentHandle CreateComponent(EntityHandle eHandle,Args... args)
		{
			return componentManager->CreateComponent<T,E>(eHandle,std::forward<Args>(args)...);
		}

		template<class T,class... Args>
		SystemHandle CreateSystem(Args... args)
		{
			return systemManager->CreateSystem<T>(std::forward<Args>(args)...);
		}

		template<class T>
		IEntity* GetEntity(EntityHandle handle)
		{
			return entityManager->GetEntity<T>(handle);
		}

		template<class T>
		IComponent* GetComponent(EntityHandle handle)
		{
			return componentManager->GetComponent<T>(handle);
		}

		template<class T>
		ISystem* GetSystem(SystemHandle handle)
		{
			return systemManager->GetSystem<T>(handle);
		}

		template<class T>
		void RegisterEntity(SystemHandle systemHandle,EntityHandle entityHandle)
		{
			systemManager->RegisterEntity<T>(systemHandle,entityHandle);
		}

		template<class T>
		void UnregisterEntity(SystemHandle systemHandle, EntityHandle entityHandle)
		{
			systemManager->UnregisterEntity<T>(systemHandle, entityHandle);
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
