#pragma once
#include "InputEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::InputEngine::init( const CoreRef & coreRefs )
{
	auto* renderEngine = coreRefs.engines.getEngine<GraphicsEngine>();
	renderEngine->s_onEvent.connect_mem_fn_auto( &InputEngine::onSfEvent, *this );
}

bool nb::InputEngine::update( const CoreRef & coreRefs )
{
	for (auto& el : s_whileKeyPressed)
		if (Keyboard::isKeyPressed( el.first ))
			el.second.call();

	return true;
}

void nb::InputEngine::onSfEvent( const sf::Event & event )
{
}
