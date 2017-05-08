#include "InputEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::InputEngine::init( const CoreEngineManager& coreEngines )
{
	r_graphicsEngine = coreEngines.getEngine<GraphicsEngine>();
	r_graphicsEngine->s_onEvent.connect( this, &InputEngine::onSfEvent );

	mousePosition = sf::Mouse::getPosition( r_graphicsEngine->getWindow() );
}

bool nb::InputEngine::update()
{
	for( auto& el : s_whileKeyPressed )
		if( pressedKeys[ el.first ] )
			el.second.call();

	const auto& window = r_graphicsEngine->getWindow();
	const auto& windowSize = window.getSize();

	for( auto& el : s_whileMouseButtonPressed )
		if( isMouseButtonPressed[ el.first ] )
			el.second.call( mousePosition );
	for( auto& el : s_whileMouseButtonPressedInWindow )
		if( isMouseButtonPressed[ el.first ] )
			if( mousePosition.x >= 0 &&
				mousePosition.x < windowSize.x &&
				mousePosition.y >= 0 &&
				mousePosition.y < windowSize.y )
				el.second.call( mousePosition );

	return true;
}

void nb::InputEngine::onSfEvent( const sf::Event & event )
{
	if( event.type == sf::Event::KeyPressed )
	{
		pressedKeys[ event.key.code ] = true;
		s_onKeyPressed[ event.key.code ].call();
	}
	if( event.type == sf::Event::KeyReleased )
	{
		pressedKeys[ event.key.code ] = false;
		s_onKeyReleased[ event.key.code ].call();
	}
	if( event.type == sf::Event::MouseMoved )
	{
		mousePosition = Vector2i( event.mouseMove.x, event.mouseMove.y );
	}
	if( event.type == sf::Event::MouseButtonPressed )
	{
		isMouseButtonPressed[ event.mouseButton.button ] = true;
		s_onMouseButtonPressed[ event.mouseButton.button ].call( {event.mouseButton.x, event.mouseButton.y} );
		const auto& windowSize = r_graphicsEngine->getWindow().getSize();
		if( event.mouseButton.x >= 0 &&
			event.mouseButton.x < windowSize.x &&
			event.mouseButton.y >= 0 &&
			event.mouseButton.y < windowSize.y )
			s_onMouseButtonPressedInWindow[ event.mouseButton.button ].call( {event.mouseButton.x, event.mouseButton.y} );
	}
	if( event.type == sf::Event::MouseButtonReleased )
	{
		isMouseButtonPressed[ event.mouseButton.button ] = false;
		s_onMouseButtonReleased[ event.mouseButton.button ].call( {event.mouseButton.x, event.mouseButton.y} );
		const auto& windowSize = r_graphicsEngine->getWindow().getSize();
		if( event.mouseButton.x >= 0 &&
			event.mouseButton.x < windowSize.x &&
			event.mouseButton.y >= 0 &&
			event.mouseButton.y < windowSize.y )
			s_onMouseButtonReleasedInWindow[ event.mouseButton.button ].call( {event.mouseButton.x, event.mouseButton.y} );
	}
}

bool nb::InputEngine::isKeyPressed( sf::Keyboard::Key key ) const
{
	auto found = pressedKeys.find( key );
	if( found != pressedKeys.end() )
		return found->second;
	else
		return false;
}
