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

		sf::RenderWindow window;
		sf::CircleShape shape;

		std::vector<sf::Sprite*> m_toDrawNextFrame;

	public:
		virtual void init( const CoreRef& core ) override;

		virtual bool update( const CoreRef& core ) override;

		void drawSpriteNextFrame( sf::Sprite& sprite );

		nb::Signal<void, const sf::Event&> s_onEvent;
	};
}
