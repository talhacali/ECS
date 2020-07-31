#pragma once

#include "System.h"
#include "../../Memory/include/PoolAllocator.h"
#include <unordered_map>


namespace ECS
{
	/*class SystemManager
	{
		MemoryManager::PoolAllocator systemAllocator;

	public:


		template<class T,class... Args>
		SystemHandle CreateSystem(Args... args)
		{

		}

	};*/


	class ISystemCollection
	{

	};

	template<class T>
	class SystemCollection : public ISystemCollection
	{
		MemoryManager::PoolAllocator systemAllocator;
		using SystemMap = std::unordered_map<SystemID, ISystem*>;

	public:
		SystemCollection() : systemAllocator(sizeof(T) * 100, sizeof(T)) {}

		static const ClassID classID;


		SystemMap systemMap;

		template<class T, class... Args>
		SystemHandle CreateSystem(Args... args)
		{
			T* system = MemoryManager::Allocate<T>(systemAllocator, std::forward<Args>(args)...);

			systemMap[system->systemID] = system;

			return SystemHandle(system->systemID, system->classID);
		}

		template<class T>
		ISystem* GetSystem(SystemHandle handle)
		{
			return systemMap[handle.systemId];
		}

		/*template<class T>
		void RegisterEntity(EntityHandle const& handle)
		{
			
			((T*)(systemMap[handle.systemId]))->RegisterEntity(handle);
		}*/

	};

	template<class T>
	const ClassID SystemCollection<T>::classID = FamilyID<ISystemCollection>::Get<T>();


	class SystemManager
	{

		using SystemCollectionMap = std::unordered_map<ClassID, ISystemCollection*>;

		SystemCollectionMap collectionMap;

		template<class T>
		SystemCollection<T>* GetSystemCollection()
		{
			auto it = collectionMap.find(T::classID);
			SystemCollection<T>* collection = nullptr;

			if (it == collectionMap.end())
			{
				collection = new SystemCollection<T>();
				collectionMap[T::classID] = collection;
			}
			else
			{
				collection = static_cast<SystemCollection<T>*>(it->second);
			}

			return collection;
		}



	public:
		template<class T, class... Args>
		SystemHandle CreateSystem(Args... args)
		{
			SystemCollection<T>* collection = GetSystemCollection<T>();

			return collection->CreateSystem<T>(std::forward<Args>(args)...);
		}

		template<class T>
		ISystem* GetSystem(SystemHandle handle)
		{
			SystemCollection<T>* collection = GetSystemCollection<T>();
			return collection->GetSystem<T>(handle);
		}

		template<class T>
		void RegisterEntity(SystemHandle systemHandle,EntityHandle entityHandle)
		{
			SystemCollection<T>* collection = GetSystemCollection<T>();
			T* system =  (T*)collection->GetSystem<T>(systemHandle);

			system->RegisterEntity(entityHandle);
		}

		template<class T>
		void UnregisterEntity(SystemHandle systemHandle, EntityHandle entityHandle)
		{
			SystemCollection<T>* collection = GetSystemCollection<T>();
			T* system = (T*)collection->GetSystem<T>(systemHandle);

			system->UnregisterEntity(entityHandle);
		}

	};
}

