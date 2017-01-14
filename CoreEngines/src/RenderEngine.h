#pragma once
#include "stdafx.h"
#include "id.h"

namespace nb
{
	class RenderEngine : public CoreEngine
	{
		sf::RenderWindow window;
		sf::CircleShape shape;

		std::vector<sf::Sprite*> m_toDraw;

	public:
		virtual void init( const CoreRefs& coreRefs ) override;

		virtual bool update( const CoreRefs& coreRefs ) override;

		virtual unsigned int getId()const override;

		void drawSpriteNextFrame( sf::Sprite& sprite );

		nb::Signal<void, const sf::Event&> s_onEvent;
	};
}
