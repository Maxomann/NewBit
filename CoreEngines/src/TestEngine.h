#pragma once
#include "TestGameState.h"

namespace nb
{
	class TestEngine : public nb::CoreEngine
	{
		sf::RenderWindow window;
		sf::CircleShape shape;

	public:
		DLL_EXPORT TestEngine();

		DLL_EXPORT virtual void init( const CoreEngineManager& coreEngines,
									  GameStateManager& gameStates,
									  World& world )override;

		DLL_EXPORT virtual bool update( const CoreEngineManager& coreEngines,
										GameStateManager& gameStates,
										World& world )override;

		DLL_EXPORT virtual unsigned int getId()const override;
	};
}
