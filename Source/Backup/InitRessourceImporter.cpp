#include "RessourceImporter.hpp"

namespace Soon
{
	void InitRessourceImporter( void )
	{
		RessourceImporter::GetSingleton().AddImporter<MeshImporter>();
		RessourceImporter::GetSingleton().AddImporter<Texture2DImporter>();
	}
}
