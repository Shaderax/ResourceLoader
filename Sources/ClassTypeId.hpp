#pragma once

#include <cstdint>

typedef std::uint32_t TypeId;

template < typename TBase >
class ClassTypeId
{
public:
	template < typename T >
	static TypeId GetId(void)
	{
		static const TypeId id = mNextId++;
		return (id);
	}

private:
	static TypeId mNextId;
};

template < typename TBase >
TypeId ClassTypeId<TBase>::mNextId = 0;