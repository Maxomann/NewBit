#pragma once
#include "stdafx.h"
#include "id.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"

namespace nb
{
	class GraphicsEngine : public CoreEngine
	{
		RenderSystem* r_renderSystem;

		sf::RenderWindow m_window;
		tgui::Gui m_gui;

		std::vector<sf::Drawable*> m_toDrawNextFrame;

		sf::Clock m_clock;
		sf::Time m_frameTime;

	public:
		virtual void init() override;

		virtual bool update() override;

		void drawNextFrame( sf::Drawable& drawable );

		nb::Signal<void( const sf::Event& )> s_onEvent;

		sf::RenderWindow& getWindow();
		const sf::RenderWindow& getWindow()const;

		const sf::Time& getFrameTime()const;

		tgui::Gui* getGui();
		bool isGuiFocused()const;
	};
}
