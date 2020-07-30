#include "System.h"

namespace ECS
{
	/*template<class T>
	void System<T>::RegisterEntity(EntityHandle entityHandle)
	{
		entities.push_back(entityHandle);
	}*/

	template<class T>
	void System<T>::UnRegisterEntity(EntityHandle const& entityHandle)
	{
		for (auto it : entities.begin())
		{
			EntityHandle e = *it;

			if (entityHandle.entityId == e.entityId)
			{
				entities.erase(it);
				return;
			}
		}
	}

}