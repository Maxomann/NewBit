#pragma once
#include "stdafx.h"
#include "id.h"
#include "GraphicsEngine.h"

namespace nb
{
	class InputEngine : public CoreEngine
	{
	public:
		virtual void init() override;

		virtual bool update() override;

		void onSfEvent( const sf::Event& event );

		std::map<sf::Keyboard::Key, Signal<void>> s_whileKeyPressed;
	};
}
