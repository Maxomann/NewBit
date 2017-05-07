#include "GraphicsEngine.h"
#include "InputEngine.h"
#include "ResourceEngine.h"
#include "WorldGenerationEngine.h"
#include "ChunkCacheEngine.h"

#include "BaseGameState.h"

using namespace std;

extern "C" {
	DLL_EXPORT void nbConnectCore( nb::CoreEngineManager* manager, nb::GameStateManager* gameStates )
	{
		manager->addEngine<nb::ResourceEngine>();
		manager->addEngine<nb::GraphicsEngine>();
		manager->addEngine<nb::InputEngine>();

		manager->addEngine<nb::ChunkCache>();
		manager->addEngine<nb::WorldGenerationEngine>();

		gameStates->pushState( std::make_unique<nb::BaseGameState>() );
	}
}
