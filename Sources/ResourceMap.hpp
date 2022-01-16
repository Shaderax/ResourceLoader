#pragma once

#include "ClassTypeId.hpp"
#include "ResourceManager.hpp"
#include <unordered_map>
#include <vector>
#include <array>

class IResourceMap
{
public:
    virtual ~IResourceMap() {};
    virtual TypeId GetTypeId() = 0;
};

template<typename T>
class TResourceMap : public IResourceMap
{
    std::unordered_map<std::string, T*>  mMap;

public:
    inline std::unordered_map<std::string, T*>& GetMap()
    {
        return mMap;
    }

    TypeId GetTypeId()
    {
        return ClassTypeId<IResourceMap>::GetId<T>();
    }
};

class ResourceMaps
{
    std::array<IResourceMap*, MAX_MAPS> mMaps{0};
    std::vector<std::uint32_t> Available;
    std::uint32_t mLoaderCounter = 0;
public:
    ResourceMaps()
    {
        Available.reserve(MAX_MAPS);
    }

    template<typename T>
    TResourceMap<T>* Add()
    {
        TResourceMap<T>* map = Get<T>();

        if (map)
            return map;

        /*check limit reach mLoaderCounter < MAX_MAPS*/

        mMaps[mLoaderCounter] = new TResourceMap<T>();

        return static_cast<TResourceMap<T>*>(mMaps[mLoaderCounter++]);
    }

    template<typename T>
    void Remove()
    {
        for (std::uint32_t index = 0 ; index < MAX_MAPS ; ++index)
        {
            if (ClassTypeId<IResourceMap>::GetId<T>() == mMaps[index]->GetTypeId())
            {
                Available.push_back(index);
                delete mMaps[index];
                mMaps[index] = nullptr;
                return ;
            }
        }
    }

    template<typename T>
    TResourceMap<T>* Get()
    {
        // Chek in mMaps, soit tab soit unordermap 
        for (std::uint32_t index = 0 ; index < MAX_MAPS ; ++index)
        {
            if (mMaps[index] && ClassTypeId<IResourceMap>::GetId<T>() == mMaps[index]->GetTypeId())
                return static_cast<TResourceMap<T>*>(mMaps[index]);
        }
        return nullptr;
    }

    ~ResourceMaps()
    {
        Available.clear();
        for (std::uint32_t index = 0 ; index < MAX_MAPS ; ++index)
        {
            if (mMaps[index] != nullptr)
            {
                delete mMaps[index];
                mMaps[index] = nullptr;
            }
        }
        mLoaderCounter = 0;
    }
};
