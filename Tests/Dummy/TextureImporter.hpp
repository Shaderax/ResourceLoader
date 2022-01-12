#pragma once

#include "ResourceManager.hpp"
#include "IImporter.hpp"
#include "ClassTypeId.hpp"

struct Image
{
	Image(void* data, unsigned int size) : mData(data), mSize(size) {}
	virtual ~Image()
	{
		mData = nullptr;
		mSize = 0;
	};
	void* mData;
	unsigned int mSize;
};

class FakeTextureImporter : public IImporter
{
public:
	FakeTextureImporter(void) { };
	~FakeTextureImporter(void) {};

	uint32_t GetTypeId(void)
	{
		return (ClassTypeId<ResourceManager>::GetId<Image>());
	}

	void* Import(std::string path)
	{
		Image* img = new Image(nullptr, 400);

		return (img);
	}

	void Unload(std::string path)
	{
		//Image* img = ResourceMap::Get<Image>()[path];
	}

	bool IsExtSupported(std::string& ext)
	{
		return true;
	}

	bool IsExtMandatory()
	{
		return true;
	}

};