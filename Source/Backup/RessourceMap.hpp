#pragma once

#include <unordered_map>

namespace Soon
{
	template < typename T >
		std::unordered_map<std::string, T*>& GetRessourceMap( void )
		{
			static std::unordered_map<std::string, T*> _map;

			return (_map);
		}
}
