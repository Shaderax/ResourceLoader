#include "ResourceManager.hpp"
#include "TextureImporter.hpp"

int main()
{
	ResourceManager manager;

	manager.AddImporter<FakeTextureImporter>();

	Image& img = manager.Load<Image>("../Image.png");

	std::cout << img.mData << std::endl;
	std::cout << img.mSize << std::endl;

	manager.Unload<Image>("../Image.png");

	return 0;
}
/*
	Quand [0]'/' : On colle post RESOURCE_PATH/()
	Quand [0-1]"./" : On colle post RESOURCE_PATH/()
	En vrai a quelle moment on fait autre chose que juste paste pre path ?
*/