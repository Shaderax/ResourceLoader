#include "ResourceManager.hpp"
#include "TextureImporter.hpp"

int main()
{
	ResourceManager manager;
	manager.AddImporter<FakeTextureImporter>();
	Image* img = manager.Load<Image>("../Image.png");
	std::cout << img->mData << std::endl;
	std::cout << img->mSize << std::endl;

	return 0;
}