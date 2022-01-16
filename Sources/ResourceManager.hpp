#pragma once

#include "Importer.hpp"
#include <list>
#include <unordered_map>
#include <iostream>
#include "ClassTypeId.hpp"

#define MAX_MAPS 64

#define TYPE_HANDLE(x) ClassTypeId<ResourceManager>::GetId<x>()

class ResourceManager
{
public:
    template< typename T>
    T* AddImporter()
    {
        IImporter* imp = new T;
		mImporters.push_back(imp);

		return static_cast<T*>(mImporters.back());
    }

    ~ResourceManager()
    {
    }

    template<typename T>
    T& Load(std::string path)
    {
        TResourceMap<T>* resMap = mMaps.Get<T>();
		T* resource = nullptr;

        if (resMap != nullptr)
        {
            std::unordered_map<std::string, T*>& map = resMap->GetMap();

            auto res = map.find(path);
			if (res != map.end())
                resource = map[path];
        }
        else
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
    			resource = static_cast<T*>(imp->_Import(path));

    			if (resource != nullptr)
    			{
                    std::unordered_map<std::string, T*>& map = mMaps.Add<T>()->GetMap();
    				map.emplace(std::make_pair(path, resource));
    			}
    			else
    			{
    				std::cout << "Fail Load" << std::endl;
    				exit(-1);
    			}
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
            TResourceMap<T>* resMap = mMaps.Get<T>();

            if (resMap)
            {
                std::unordered_map<std::string, T*>& map = resMap->GetMap();

				auto res = map.find(path);
                if (res != map.end())
                {
			        imp->_Unload(path, map[path]);
	    		    map.erase(path);
                }
            }
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

    ResourceMaps mMaps;
    std::list<IImporter*> mImporters;
};