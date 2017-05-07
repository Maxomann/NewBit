#pragma once
#include "stdafx.h"
#include "GraphicsEngine.h"
#include "InputEngine.h"
#include "ResourceEngine.h"
#include "PhysicsComponent.h"
#include "EntityFactories.h"
#include "PhysicsSystem.h"
#include "ItemManager.h"

namespace nb
{
	class DemoEditGameState : public GameState
	{
		tgui::Gui* r_gui;
		InputEngine* r_inputEngine;
		GraphicsEngine* r_graphicsEngine;
		ResourceEngine* r_resourceEngine;

		World& world;
		Entity* camera;

		tgui::ChildWindow::Ptr m_childWindow;

		tgui::Label::Ptr m_EntityCountLabel;
		tgui::Label::Ptr m_EntityCountValueLabel;

		tgui::ListBox::Ptr objectListBox;

		Connections m_connections;

	public:
		DemoEditGameState( World& world, Entity* camera );

		virtual void init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates ) override;

		virtual void update( GameStateManager& gameStates ) override;

		virtual void destroy( GameStateManager& gameStates ) override;
	};
}
