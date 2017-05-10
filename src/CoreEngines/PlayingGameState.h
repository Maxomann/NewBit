#pragma once
#include "stdafx.h"

#include "EntityFactories.h"

#include "GraphicsEngine.h"
#include "InputEngine.h"
#include "ResourceEngine.h"

namespace nb
{
	class PlayingGameState : public GameState
	{
		tgui::Gui* gui;
		ResourceEngine* resourceEngine;
		InputEngine* inputEngine;
		GraphicsEngine* graphicsEngine;

		World& world;
		Entity* camera;

		tgui::VerticalLayout::Ptr barContainer;
		tgui::ProgressBar::Ptr healthBar;
		tgui::ProgressBar::Ptr hungerBar;
		tgui::ProgressBar::Ptr thirstBar;
		tgui::ProgressBar::Ptr energyBar;

		Entity* player;
		PhysicsComponent* playerPhysics;

		Connections connections;

	public:
		PlayingGameState( World& world,
						  Entity* camera );

		virtual void init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates ) override;

		virtual void update( GameStateManager& gameStates ) override;

		virtual void destroy( GameStateManager& gameStates ) override;
	};
}
