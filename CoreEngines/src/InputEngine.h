#pragma once
#include "stdafx.h"
#include "id.h"
#include "RenderEngine.h"

namespace nb
{
	class InputEngine : public CoreEngine
	{
	public:
		virtual void init( const CoreRefs& coreRefs ) override;

		virtual bool update( const CoreRefs& coreRefs ) override;

		void forwardSfEvent( const sf::Event& event );

		Signal<void, const CoreRefs&> s_whileQPressed;
	};
}
