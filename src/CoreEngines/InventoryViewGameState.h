#pragma once
#include "stdafx.h"

#include "Inventory.h"

#include "ResourceEngine.h"
#include "GraphicsEngine.h"

namespace nb
{
	class InventoryViewGameState : public GameState
	{
		GraphicsEngine* graphics;
		ResourceEngine* resources;

		World& world;
		Entity* entityToApplyActions;
		Inventory& inventory;

		tgui::ChildWindow::Ptr inventoryListContainer;
		tgui::ListBox::Ptr itemList;
		tgui::Button::Ptr useButton;

		int selectedItemId = -1;

		static const tgui::Color inactiveColor;
		static const tgui::Color activeColor;

		Connections connections;

		void updateView( const Inventory& inventoryForUpdate );

	public:
		InventoryViewGameState( World& world,
								Entity* entityToApplyActions,
								Inventory& inventory );

		virtual void init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates ) override;

		virtual void update( GameStateManager& gameStates ) override;

		virtual void destroy( GameStateManager& gameStates ) override;
	};
}
