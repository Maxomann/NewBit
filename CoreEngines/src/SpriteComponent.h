#pragma once
#include "stdafx.h"
#include "GraphicsEngine.h"

namespace nb
{
	class SpriteComponent : public nb::Component
	{
	public:
		sf::Sprite sprite;

		virtual void init( const Entity& entity )override;

		virtual void destroy( const Entity& entity )override;
	};
}
