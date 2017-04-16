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

		tgui::ChildWindow::Ptr m_childWindow;

		tgui::Label::Ptr m_EntityCountLabel;
		tgui::Label::Ptr m_EntityCountValueLabel;

		tgui::ListBox::Ptr objectListBox;

		bool m_shouldDestroy = false;

		Connections m_connections;

	public:
		virtual void init() override;

		virtual void update() override;

		virtual void destroy() override;

		virtual bool shouldDestroy() override;
	};
}
