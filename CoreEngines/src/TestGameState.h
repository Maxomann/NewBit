#pragma once
#include "stdafx.h"
#include "InputEngine.h"

namespace nb
{
	class TestGameState : public nb::GameState
	{
		sf::Texture m_texture;
		sf::Sprite m_sprite;

	public:
		DLL_EXPORT virtual void init( const CoreRefs& coreRefs ) override;

		DLL_EXPORT virtual void destroy( const CoreRefs& coreRefs ) override;

		DLL_EXPORT virtual bool shouldDestroy() override;

		void drawTestsprite( const CoreRefs& core );
	};
}
