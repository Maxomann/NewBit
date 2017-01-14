#include "RenderEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::RenderEngine::init( const CoreRefs& coreRefs )
{
	window.create( sf::VideoMode( 1280, 720 ), "RenderEngine Window" );
	shape.setRadius( 100.f );
	shape.setFillColor( sf::Color::Black );
}

bool nb::RenderEngine::update( const CoreRefs& coreRefs )
{
	sf::Event event;
	while( window.pollEvent( event ) )
	{
		if( event.type == sf::Event::Closed )
			window.close();
		if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape )
			window.close();

		s_onEvent.call( event );
	}

	window.clear( sf::Color::Green );
	window.draw( shape );

	for( const auto& sprite : m_toDraw )
		window.draw( *sprite );
	m_toDraw.clear();

	window.display();

	return window.isOpen();
}

unsigned int nb::RenderEngine::getId() const
{
	return id::CORE_ENGINE::RENDER;
}

void nb::RenderEngine::drawSpriteNextFrame( sf::Sprite& sprite )
{
	m_toDraw.push_back( &sprite );
}
