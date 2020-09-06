#pragma once

#include "RessourceMap.hpp"
#include "ECS/ClassTypeId.hpp"
#include "Importer.hpp"
#include <list>
#include <unordered_map>
#include <iostream>

namespace Soon
{
	class RessourceImporter
	{
		private:
			RessourceImporter( void )
			{
			}

		public:

			static RessourceImporter& GetSingleton( void )
			{
				static RessourceImporter singleton;

				return (singleton);
			}

			template<class T>
				Importer* AddImporter( void )
				{
					Importer* imp = new T;
					_importers.push_back(imp);

					return (_importers.back());
				}

			template<class T>
				Importer* GetValidImporter( void )
				{
					for (Importer* ok : _importers)
					{
						if (ok->IdValidType() == ClassTypeId<RessourceImporter>::GetId<T>())
							return (ok);
					}

					return (nullptr);
				}

			template<class T>
				T* Load( std::string path )
				{
					T* ret = nullptr;
					Importer* imp = GetValidImporter<T>();

					if (!imp)
					{
						std::cout << "Not found valid Importer for : " << path << std::endl;
						exit(-1);
					}
					else
					{
						if (imp->Import(path))
							ret = GetRessourceMap<T>()[path];
						else
						{
							std::cout << "Fail Load" << std::endl;
							exit(-1);
						}
					}
					return (ret);
				}

			template<class T>
				void Unload( std::string path )
				{
					Importer* imp = GetValidImporter<T>();

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

			std::list<Importer*>	_importers;
	};
}
