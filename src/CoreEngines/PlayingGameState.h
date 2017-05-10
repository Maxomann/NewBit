#pragma once
#include "stdafx.h"
#include "GraphicsEngine.h"

namespace nb
{
	class PlayingGameState : public GameState
	{
		tgui::Gui* gui;

		World& world;
		Entity* camera;

		tgui::HorizontalLayout::Ptr barContainer;
		tgui::ProgressBar::Ptr healthBar;
		tgui::ProgressBar::Ptr thirstBar;
		tgui::ProgressBar::Ptr energyBar;

		Entity* player;

	public:
		PlayingGameState( World& world,
						  Entity* camera );

		virtual void init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates ) override;

		virtual void update( GameStateManager& gameStates ) override;

		virtual void destroy( GameStateManager& gameStates ) override;
	};
}
