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

		std::vector<sf::Drawable*> m_toDrawNextFrame;

	public:
		virtual void init( const CoreRef& core ) override;

		virtual bool update( const CoreRef& core ) override;

		void drawNextFrame( sf::Drawable& drawable );

		nb::Signal<void, const sf::Event&> s_onEvent;

		const sf::RenderWindow& getWindow()const;
	};
}
