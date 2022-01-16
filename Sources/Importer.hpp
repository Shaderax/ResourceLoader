#pragma once

#include "ClassTypeId.hpp"
#include <string>

class ResourceManager;

#define TYPE_HANDLE(x) ClassTypeId<ResourceManager>::GetId<x>()

class IImporter
{
public:
    virtual ~IImporter() {};
	virtual TypeId GetTypeId(void) = 0;
	virtual void* _Import(std::string path) = 0;
	virtual void _Unload(std::string path, void* resource) = 0;
	virtual bool IsExtSupported(std::string& ext) = 0;
	virtual bool IsExtMandatory() = 0;
};

template<typename T>
class TImporter : public IImporter
{
	typedef T TType;
    TypeId HandledType;

	void* _Import(std::string path)
	{
		return Import(path);
	}

	virtual void _Unload(std::string path, void* resource)
	{
		Unload(path, static_cast<TType*>(resource));
	}

public:
    TImporter() : HandledType(TYPE_HANDLE(T)) {}
    virtual ~TImporter() {};

	TypeId GetTypeId(void) {return HandledType;};

	virtual TType* Import(std::string path) = 0;
	virtual void Unload(std::string path, TType* resource) = 0;

	virtual bool IsExtSupported(std::string& ext) = 0;
	virtual bool IsExtMandatory() = 0;
};