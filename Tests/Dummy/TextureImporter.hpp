#pragma once
#include "ResourceManager.hpp"
#include "ResourceMap.hpp"
#include "IImporter.hpp"
#include "ClassTypeId.hpp"

struct Image
{
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

	bool Import(std::string path)
	{
		Image* img = new Image{nullptr, 400};

		GetResourceMap<Image>().emplace(std::make_pair(path, img));

		return (true);
	}

	bool Unload(std::string path)
	{
		try
		{
			Image* texture = GetResourceMap<Image>().at(path);
			if (!texture)
				return false;
			delete texture;
			GetResourceMap<Image>().erase(path);
		}
		catch (std::out_of_range&)
		{
			std::cout << "Error : GetRessourceMap : Out of range" << std::endl;
			return false;
		}
		return (true);
	}
};