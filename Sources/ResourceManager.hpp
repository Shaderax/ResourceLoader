#pragma once

#include "IImporter.hpp"
#include <list>
#include <unordered_map>
#include <iostream>
#include "ClassTypeId.hpp"

class ResourceManager
{
public:

	ResourceManager(void)
	{
	}

	template<class T>
	IImporter* AddImporter(void)
	{
		IImporter* imp = new T;
		mImporters.push_back(imp);

		return (mImporters.back());
	}

	template<class T>
	T& Load(std::string path)
	{
		std::string ext = path.substr(path.find_last_of(".") + 1);

		T* resource = nullptr;
		IImporter* imp = GetValidImporter<T>(ext);

		if (!imp)
		{
			std::cout << "Not found valid Importer for : " << path << std::endl;
			exit(-1);
		}
		else
		{
			resource = static_cast<T*>(imp->Import(path));
			if (resource != nullptr)
			{
				GetResourceMap<T>().emplace(std::make_pair(path, resource));
			}
			else
			{
				std::cout << "Fail Load" << std::endl;
				exit(-1);
			}
		}
		return (*resource);
	}

	template<class T>
	void Unload(std::string path)
	{
		std::string ext = path.substr(path.find_last_of(".") + 1);

		IImporter* imp = GetValidImporter<T>(ext);

		if (!imp)
		{
			std::cout << "Not found valid Importer for : " << path << std::endl;
			exit(-1);
		}
		else
		{
			imp->Unload(path);
			delete GetResourceMap<T>()[path];
			GetResourceMap<T>().erase(path);
		}
	}

private:

	template<class T>
	IImporter* GetValidImporter(std::string& ext)
	{
		for (IImporter* imp : mImporters)
		{
			if (imp->GetTypeId() == ClassTypeId<ResourceManager>::GetId<T>())
			{
				if (imp->IsExtMandatory())
				{
					if (imp->IsExtSupported(ext))
						return imp;
				}
				else
				{
					return imp;
				}
			}
		}

		return (nullptr);
	}

	template < typename T >
		std::unordered_map<std::string, T*>& GetResourceMap(void)
		{
			static std::unordered_map<std::string, T*> mMap;
			return (mMap);
		}

	std::list<IImporter*>	mImporters;
};