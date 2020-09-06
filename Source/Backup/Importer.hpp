#pragma once

#include <string>

namespace Soon
{
	struct Importer
	{
		Importer() : priority(0) {};
		uint32_t priority;
		virtual uint32_t IdValidType( void ) = 0;
		virtual bool Import( std::string path ) = 0;
		virtual bool Unload( std::string path ) = 0;
	};
}
