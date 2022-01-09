#pragma once

#include <string>

class IImporter
{
public:
	virtual uint32_t GetTypeId(void) = 0;
	virtual bool Import(std::string path) = 0;
	virtual bool Unload(std::string path) = 0;

protected:
	uint32_t mPriority;
};