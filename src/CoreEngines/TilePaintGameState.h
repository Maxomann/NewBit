#pragma once
#include "stdafx.h"
#include "GraphicsEngine.h"
#include "TileMapComponent.h"
#include "ResourceEngine.h"
#include "InputEngine.h"
#include "ChunkSystem.h"

namespace nb
{
	class TilePaintGameState : public GameState
	{
		ResourceEngine* r_resourceEngine;
		InputEngine* r_inputEngine;
		GraphicsEngine* r_graphicsEngine;
		tgui::Gui* r_gui;

		World& world;
		Entity* camera;

		tgui::ChildWindow::Ptr childWindow;

		tgui::ListBox::Ptr tileListBox;

		Tile::ID tileToPaint = 0;

		bool isWindowOpen = true;

		Connections connections;

	public:
		TilePaintGameState( World& world,
							Entity* camera );

		virtual void init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates ) override;

		virtual void update( GameStateManager& gameStates ) override;

		virtual void destroy( GameStateManager& gameStates ) override;
	};
}
