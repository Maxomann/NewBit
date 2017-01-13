#pragma once
#include "stdafx.h"

namespace nb
{
	class InitEngine : public CoreEngine
	{
	public:
		virtual void init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates,
						   World& world ) override;

		virtual bool update( const CoreEngineManager& coreEngines,
							 GameStateManager& gameStates,
							 World& world ) override;

		virtual unsigned int getId()const override;
	};
}
