#include "InputEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::InputEngine::init()
{
	r_graphicsEngine = getCore()->engines.getEngine<GraphicsEngine>();
	r_graphicsEngine->s_onEvent.connect( this, &InputEngine::onSfEvent );
}

bool nb::InputEngine::update()
{
	for (auto& el : s_whileKeyPressed)
		if (Keyboard::isKeyPressed( el.first ))
			el.second.call();

	return true;
}

void nb::InputEngine::onSfEvent( const sf::Event & event )
{
	if (event.type == sf::Event::KeyPressed)
		s_onKeyPressed[event.key.code].call();
	if (event.type == sf::Event::KeyReleased)
		s_onKeyReleased[event.key.code].call();
	if (event.type == sf::Event::MouseButtonPressed)
	{
		s_onMouseButtonPressed[event.mouseButton.button].call( { event.mouseButton.x, event.mouseButton.y } );
		const auto& windowSize = r_graphicsEngine->getWindow().getSize();
		if (event.mouseButton.x >= 0 &&
			 event.mouseButton.x < windowSize.x &&
			 event.mouseButton.y >= 0 &&
			 event.mouseButton.y < windowSize.y)
			s_onMouseButtonPressedInWindow[event.mouseButton.button].call( { event.mouseButton.x, event.mouseButton.y } );
	}
}
