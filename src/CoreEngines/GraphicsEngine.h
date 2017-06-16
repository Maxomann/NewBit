#pragma once
#include "stdafx.h"
#include "id.h"
#include "RenderSystem.h"

namespace nb
{
	class GraphicsEngine : public CoreEngine
	{
		sf::RenderWindow m_window;
		tgui::Gui m_gui;

		std::vector<sf::Drawable*> m_toDrawNextFrame;
		std::vector<std::pair<sf::View, std::vector<const sf::Drawable*>>> m_toDrawNextFrameWithView;

		sf::Clock m_clock;
		sf::Time m_frameTime;

	public:
		virtual void init( const CoreEngineManager& coreEngines ) override;

		virtual bool update() override;

		void drawNextFrame( sf::Drawable& drawable );
		void drawNextFrame( std::vector<const sf::Drawable*> drawables, sf::View view );

		nb::Signal<void( const sf::Event& )> s_onEvent;

		sf::RenderWindow& getWindow();
		const sf::RenderWindow& getWindow()const;

		const sf::Time& getFrameTime()const;

		tgui::Gui* getGui();
		bool isGuiFocused()const;
	};
}
