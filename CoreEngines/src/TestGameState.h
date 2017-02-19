#pragma once
#include "stdafx.h"
#include "InputEngine.h"
#include "ResourceEngine.h"

namespace nb
{
	class TestGameState : public nb::GameState
	{
		sf::Texture m_texture;
		sf::Texture m_texture2;

		sf::Sprite m_sprite;

	public:
		DLL_EXPORT virtual void init( const CoreRef& coreRefs ) override;

		DLL_EXPORT virtual void destroy( const CoreRef& coreRefs ) override;

		DLL_EXPORT virtual bool shouldDestroy() override;

		void drawTestsprite( const CoreRef& core );
	};
}
