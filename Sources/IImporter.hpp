#pragma once

#include <string>

class IImporter
{
public:
	virtual uint32_t GetTypeId(void) = 0;
	virtual void* Import(std::string path) = 0;
	// Resource destroy after this function
	virtual void Unload(std::string path) = 0;
	virtual bool IsExtSupported(std::string& ext) = 0;
	virtual bool IsExtMandatory() = 0;
};