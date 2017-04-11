#pragma once
#include "stdafx.h"
#include "GraphicsEngine.h"
#include "TransformationComponent.h"
#include "SpriteComponent.h"
#include "HealthComponent.h"
#include "NeedsComponent.h"
#include "InventoryComponent.h"

namespace nb
{
	class EntityTrackerScreenGameState : public GameState
	{
		tgui::Gui* r_gui;

		Entity* r_tracked = nullptr;

		// Gui
		tgui::ChildWindow::Ptr m_playerStatsWindow;
		tgui::Label::Ptr m_playerPositionLabel;
		tgui::Label::Ptr m_playerPositionValueLabel;

		tgui::Label::Ptr m_playerSpritePathLabel;
		tgui::Label::Ptr m_playerSpritePathValueLabel;

		tgui::Label::Ptr m_playerHealthLabel;
		tgui::Label::Ptr m_playerHealthValueLabel;

		tgui::Label::Ptr m_playerHungerLabel;
		tgui::Label::Ptr m_playerHungerValueLabel;

		tgui::ListBox::Ptr inventoryList;

		Connections m_connections;
	public:

		virtual void init() override;

		virtual void update() override;

		virtual void destroy() override;

		virtual bool shouldDestroy() override;

		void track( const Entity* entity );
	};
}
