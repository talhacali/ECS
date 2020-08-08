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
		void DeleteEntity(const EntityHandle& entityHandle,const ComponentHandle& componentHandle, const SystemHandle& systemHandle)
		{
			systemManager->UnregisterEntity<S>(systemHandle, entityHandle);
			componentManager->DeleteComponent<C>(componentHandle, entityHandle);
			entityManager->DeleteEntity<E>(entityHandle);
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
		IEntity* GetEntity(const EntityHandle& handle)
		{
			return entityManager->GetEntity<T>(handle);
		}

		template<class T>
		IComponent* GetComponent(const EntityHandle& handle)
		{
			return componentManager->GetComponent<T>(handle);
		}

		template<class T>
		ISystem* GetSystem(const SystemHandle& handle)
		{
			return systemManager->GetSystem<T>(handle);
		}

		template<class T>
		void RegisterEntity(const SystemHandle& systemHandle,const EntityHandle& entityHandle)
		{
			systemManager->RegisterEntity<T>(systemHandle,entityHandle);
		}

		template<class T>
		void UnregisterEntity(const SystemHandle& systemHandle, const EntityHandle& entityHandle)
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
