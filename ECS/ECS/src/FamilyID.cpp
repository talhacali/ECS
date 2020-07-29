#include "FamilyID.h"

namespace ECS
{
	class IEntity;
	class IComponent;
	class ISystem;

	unsigned int FamilyID<IEntity>::classCount = 0u;
	unsigned int FamilyID<IComponent>::classCount = 0u;
	unsigned int FamilyID<ISystem>::classCount = 0u;

	template class FamilyID<IEntity>;
	template class FamilyID<IComponent>;
	template class FamilyID<ISystem>;
}





