#pragma once

#include "RessourceMap.hpp"
#include "Importer.hpp"
#include "RessourceImporter.hpp"

#include "Core/Scene/Common/Texture2D.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Soon
{
	class Texture2DImporter : public Importer
	{
		public:
			std::string _path;
			Texture2DImporter( void ) { };
			~Texture2DImporter( void ) {};

			uint32_t IdValidType( void )
			{
				return (ClassTypeId<RessourceImporter>::GetId<Texture2D>());
			}

			bool Import( std::string path )
			{
				Texture2D* texture = new Texture2D();

				int format;
				texture->_data = stbi_load(path.c_str(), &texture->_width, &texture->_height, &format, STBI_rgb_alpha);
				texture->_format = TextureFormat::RGBA;
				if (texture->_data)
				{
					std::cout << "Open Texture : " << path << std::endl;
					std::cout << texture->_width << " " << texture->_height << std::endl;
					std::cout << format << std::endl;
					texture->_path = path;

					//	texture->_format = format;
					//if (format == 0)
					//	texture->_format = TextureFormat::UNDEFINED;
					//else if (format == 1)
					//	texture->_format = TextureFormat::G;
					//else if (format == 2)
					//	texture->_format = TextureFormat::GA;
					//else if (format == 3)
					//	texture->_format = TextureFormat::RGB;
					//else if (format == 4)
					//	texture->_format = TextureFormat::RGBA;
					// stbi_image_free(data);
				}
				else
				{
					std::cout << "Texture2D failed to load at path: " << path << std::endl;
					//stbi_image_free(texture->_data);
					//texture->_data = stbi_load("../Ressources/Textures/white.png", &texture->_width, &texture->_height, &format, 0);
					//if (!texture->_data)
					exit(-1);
				}
				//texture->_format = TextureFormat::RGBA;
				texture->_format = static_cast<TextureFormat>(format);

				GetRessourceMap<Texture2D>().emplace(std::make_pair(path, texture));

				return (true);
			}

			bool Unload( std::string path )
			{
				try
				{
					Texture2D* texture = GetRessourceMap<Texture2D>().at(path);
					if (!texture)
						return false;
					stbi_image_free(texture->_data);
					delete texture;
					GetRessourceMap<Texture2D>().erase(path);
				}
				catch (std::out_of_range & )
				{
					std::cout << "Error : GetRessourceMap : Out of range" << std::endl; 
					return false;
				}
				return (true);
			}
	};
}
