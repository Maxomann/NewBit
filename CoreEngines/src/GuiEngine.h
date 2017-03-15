#pragma once
#include "stdafx.h"
#include "GraphicsEngine.h"

namespace nb
{
	class GuiEngine : public CoreEngine
	{
		GraphicsEngine* r_graphicsEngine;

		tgui::Gui m_gui;

	public:

		virtual void init() override;

		// return false to terminate process
		virtual bool update() override;
	};
}
