#pragma once
#include "stdafx.h"
#include "GraphicsEngine.h"
#include "TerrainComponent.h"
#include "ResourceEngine.h"
#include "InputEngine.h"
#include "ChunkSystem.h"

namespace nb
{
	class TilePaintGameState : public GameState
	{
		tgui::Gui* r_gui;

		tgui::ChildWindow::Ptr childWindow;

		tgui::ListBox::Ptr tileListBox;

		Tile::ID tileToPaint = 0;

		bool isWindowOpen = true;

	public:

		virtual void init() override;

		virtual void update() override;

		virtual void destroy() override;

		virtual bool shouldDestroy() override;
	};
}
