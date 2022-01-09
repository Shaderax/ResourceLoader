#pragma once

#include "ResourceMap.hpp"
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
	IImporter* GetValidImporter(void)
	{
		for (IImporter* imp : mImporters)
		{
			if (imp->GetTypeId() == ClassTypeId<ResourceManager>::GetId<T>())
				return (imp);
		}

		return (nullptr);
	}

	template<class T>
	T* Load(std::string path)
	{
		T* ret = nullptr;
		IImporter* imp = GetValidImporter<T>();

		if (!imp)
		{
			std::cout << "Not found valid Importer for : " << path << std::endl;
			exit(-1);
		}
		else
		{
			if (imp->Import(path))
				ret = GetResourceMap<T>()[path];
			else
			{
				std::cout << "Fail Load" << std::endl;
				exit(-1);
			}
		}
		return (ret);
	}

	template<class T>
	void Unload(std::string path)
	{
		IImporter* imp = GetValidImporter<T>();

		if (!imp)
		{
			std::cout << "Not found valid Importer for : " << path << std::endl;
			exit(-1);
		}
		else
		{
			if (imp->Unload(path))
			{
			}
			else
			{
				std::cout << "Fail UnLoad" << std::endl;
				exit(-1);
			}
		}
	}

	std::list<IImporter*>	mImporters;
};