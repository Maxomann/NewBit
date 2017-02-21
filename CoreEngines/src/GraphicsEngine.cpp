#include "GraphicsEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::GraphicsEngine::init( const CoreRef& core )
{
	window.create( sf::VideoMode( 1280, 720 ), "GraphicsEngine Window" );
	window.setVerticalSyncEnabled( true );

	shape.setRadius( 100.f );
	shape.setFillColor( sf::Color::Black );

	r_renderSystem = core.world.addSystem<RenderSystem>();
}

bool nb::GraphicsEngine::update( const CoreRef& core )
{
	// events
	sf::Event event;
	while (window.pollEvent( event ))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)
			window.close();

		s_onEvent.call( event );
	}

	// draw
	window.clear( sf::Color::Green );
	window.draw( shape );

	for (const auto& spriteComponent : r_renderSystem->getSpriteComponentsToDraw())
		window.draw( spriteComponent->sprite );
	for (const auto& sprite : m_toDrawNextFrame)
		window.draw( *sprite );

	window.display();
	m_toDrawNextFrame.clear();

	return window.isOpen();
}

void nb::GraphicsEngine::drawSpriteNextFrame( sf::Sprite& sprite )
{
	m_toDrawNextFrame.push_back( &sprite );
}
