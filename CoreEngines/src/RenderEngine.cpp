#include "RenderEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::RenderEngine::init( const CoreEngineManager & coreEngines,
							 GameStateManager & gameStates,
							 World & world )
{
	window.create( sf::VideoMode( 1280, 720 ), "RenderEngine Window" );
	shape.setRadius( 100.f );
	shape.setFillColor( sf::Color::Black );
}

bool nb::RenderEngine::update( const CoreEngineManager & coreEngines,
							   GameStateManager & gameStates,
							   World & world )
{
	sf::Event event;
	while( window.pollEvent( event ) )
	{
		if( event.type == sf::Event::Closed )
			window.close();
		if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape )
			window.close();
	}

	window.clear( sf::Color::Green );
	window.draw( shape );
	window.display();

	return window.isOpen();
}

unsigned int nb::RenderEngine::getId() const
{
	return id::CORE_ENGINE::RENDER;
}
