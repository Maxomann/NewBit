#pragma once
#include "stdafx.h"

namespace nb
{
	class SpriteComponent : public nb::Component
	{
	public:
		sf::Sprite sprite;

		DLL_EXPORT virtual void init( const Entity& entity )override;

		DLL_EXPORT virtual void destroy( const Entity& entity )override;
	};
}
