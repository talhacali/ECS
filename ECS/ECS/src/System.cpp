#include "System.h"

namespace ECS
{
	template<class T>
	void System<T>::AddEntity(IEntity const &entity)
	{
		entities.push_back(entity);
	}

	template<class T>
	void System<T>::RemoveEntity(IEntity const& entity)
	{
		for (auto it : entities.begin())
		{
			IEntity e = *it;

			if (entity.entityID == e.entityID)
			{
				entities.erase(it);
				return;
			}
		}
	}

}