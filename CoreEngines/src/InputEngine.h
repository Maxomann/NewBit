#pragma once
#include "stdafx.h"
#include "id.h"

namespace nb
{
	class InputEngine : public CoreEngine
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
