#include "TestEngine.h"

using namespace std;

nb::TestEngine::TestEngine()
{
	cout << "TestEngine()" << endl;
}

void nb::TestEngine::init( const CoreEngineManager& coreEngines,
						   GameStateManager& gameStates,
						   World& world )
{
	window.create( sf::VideoMode( 200, 200 ), "MyWindow" );
	shape.setRadius( 100.f );
	shape.setFillColor( sf::Color::Black );

	return;
}

bool nb::TestEngine::update( const CoreEngineManager& coreEngines,
							 GameStateManager& gameStates,
							 World& world )
{
	sf::Event event;
	while( window.pollEvent( event ) )
	{
		if( event.type == sf::Event::Closed )
			window.close();
	}

	window.clear( sf::Color::Green );
	window.draw( shape );
	window.display();

	return window.isOpen();
}

unsigned int nb::TestEngine::getId() const
{
	cout << "getId()" << endl;
	return 0;
}
