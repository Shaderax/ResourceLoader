#include <iostream>
#include <list>
#include <array>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <string>

#define MAX_MAPS 64

//
typedef std::uint32_t TypeId;

template < typename TBase >
class ClassTypeId
{
public:
	template < typename T >
	static TypeId GetId(void)
	{
		static const TypeId id = mNextId++;
		return (id);
	}

private:
	static TypeId mNextId;
};

template < typename TBase >
TypeId ClassTypeId<TBase>::mNextId = 0;
//

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

#define TYPE_HANDLE(x) ClassTypeId<ResourceManager>::GetId<x>()

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

/////////////////////////////////////////////

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
/////////////////////////////////
int main()
{
    ResourceManager manager;

    manager.AddImporter<FakeTextureImporter>();

    Image& img = manager.Load<Image>("viv");

    img.mSize = 32;

    manager.Unload<Image>("viv");

	return 0;
}
/*
	Me faut le define du path. 
*/