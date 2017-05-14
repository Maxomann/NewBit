#include "ResourceEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

const std::string ResourceEngine::PATH_PACKAGES = "./Packages";

void nb::ResourceEngine::init( const CoreEngineManager& coreEngines )
{
	packages.initFromFolder( PATH_PACKAGES );
	packages.save();

	textures.init( packages );
	tiles.init( packages, textures );
	items.init( packages, textures );
	entitiyFactories.init( packages, textures, items );
}

bool nb::ResourceEngine::update()
{
	return true;
}
