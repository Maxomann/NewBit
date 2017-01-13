#pragma once
#include "TestGameState.h"
#include "id.h"

namespace nb
{
	class TestEngine : public nb::CoreEngine
	{
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
