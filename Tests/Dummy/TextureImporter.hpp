#pragma once

#include "ResourceManager.hpp"
#include "Importer.hpp"
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

class FakeTextureImporter : public TImporter<Image>
{
public:
	FakeTextureImporter(void)
    {

    };

	~FakeTextureImporter(void) {};

	Image* Import(std::string path)
	{
		Image* img = new Image(nullptr, 400);

		return (img);
	}

	void Unload(std::string path, Image* resource)
	{
		delete resource;
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