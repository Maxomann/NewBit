#include "Core.h"
using namespace std;

namespace nb
{
	void Core::run()
	{
		sf::RenderWindow window( sf::VideoMode( 200, 200 ), "SFML works!" );
		sf::CircleShape shape( 100.f );
		shape.setFillColor( sf::Color::Black );

		while ( window.isOpen() )
		{
			sf::Event event;
			while ( window.pollEvent( event ) )
			{
				if ( event.type == sf::Event::Closed )
					window.close();
			}

			window.clear( sf::Color::Green );
			window.draw( shape );
			window.display();
		}
	}
}