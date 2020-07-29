#pragma once

namespace ECS
{
	using ClassID = unsigned int;

	template<class T>
	class FamilyID
	{
	private:
		static ClassID classCount;

	public:

		template<class C>
		static const ClassID Get()
		{
			static const ClassID id = classCount++;
			return id;
		}

		static const ClassID GetCount()
		{
			return classCount;
		}
	};
}
