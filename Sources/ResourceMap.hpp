#pragma once

#include <unordered_map>

template < typename T >
	std::unordered_map<std::string, T*>& GetResourceMap( void )
	{
	static std::unordered_map<std::string, T*> mMap;
	return (mMap);
}