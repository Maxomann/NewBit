#pragma once
#include "stdafx.h"
#include "id.h"
#include "GraphicsEngine.h"

namespace nb
{
	class InputEngine : public CoreEngine
	{
	public:
		virtual void init( const CoreRef& coreRefs ) override;

		virtual bool update( const CoreRef& coreRefs ) override;

		void onSfEvent( const sf::Event& event );

		std::map<sf::Keyboard::Key, Signal<void>> s_whileKeyPressed;
	};
}
