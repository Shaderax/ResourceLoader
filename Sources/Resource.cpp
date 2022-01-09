#include "Resource.hpp"
#include "ResourceManager.hpp"

template< typename T >
Resource<T>::Resource()
{
	++mCounter;
}

template< typename T >
Resource<T>::~Resource()
{
	--mCounter;
	if (mCounter == 0)
	{
		ResourceManager::Unload<T>(mPath);
	}
}