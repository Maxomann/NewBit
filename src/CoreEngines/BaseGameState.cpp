#include "BaseGameState.h"

void nb::BaseGameState::init( const CoreEngineManager & coreEngines,
							  GameStateManager & gameStates )
{
	world.addSystem<RenderSystem>();
	world.addSystem<TimeSystem>();
	world.addSystem<ChunkSystem>();
	world.addSystem<PhysicsSystem>();
	world.addSystem<WorldLoadStateSystem>();
	world.addSystem<NeedsSystem>();
}

void nb::BaseGameState::update( const CoreEngineManager & coreEngines,
								GameStateManager & gameStates )
{}

void nb::BaseGameState::destroy( const CoreEngineManager & coreEngines,
								 GameStateManager & gameStates )
{}

bool nb::BaseGameState::shouldDestroy( const CoreEngineManager & coreEngines,
									   GameStateManager & gameStates )
{
	return false;
}
