#pragma once
#include "stdafx.h"
#include "id.h"

namespace nb
{
	class RenderEngine : public CoreEngine
	{
		sf::RenderWindow window;
		sf::CircleShape shape;

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
