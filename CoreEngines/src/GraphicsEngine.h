#pragma once
#include "stdafx.h"
#include "id.h"
#include "SpriteComponent.h"

namespace nb
{
	class GraphicsEngine : public CoreEngine
	{
		sf::RenderWindow window;
		sf::CircleShape shape;

		std::vector<SpriteComponent*> m_spriteComponentsToDraw;
		std::vector<sf::Sprite*> m_toDrawNextFrame;

		void onEntityAdded( Entity* entity );
		void onEntitiesRemoved( const std::vector<Entity*> entities );

	public:
		virtual void init( const CoreRef& coreRefs ) override;

		virtual bool update( const CoreRef& coreRefs ) override;

		void drawSpriteNextFrame( sf::Sprite& sprite );

		nb::Signal<void, const sf::Event&> s_onEvent;
	};
}
