#include "GraphicsEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::GraphicsEngine::onEntityAdded( Entity * entity )
{
	auto spriteComponent = entity->getComponent_try<SpriteComponent>();

	if (spriteComponent)
		m_spriteComponentsToDraw.push_back( spriteComponent );
}

void nb::GraphicsEngine::onEntitiesRemoved( const std::vector<Entity*>& entities )
{
	std::vector<const SpriteComponent*> toRemove;

	for (const auto& entity : entities)
	{
		auto spriteComponent = entity->getComponent_try<SpriteComponent>();

		if (spriteComponent)
			toRemove.push_back( spriteComponent );
	}

	m_spriteComponentsToDraw.erase(
		std::remove_if( m_spriteComponentsToDraw.begin(),
						m_spriteComponentsToDraw.end(), [&]( const SpriteComponent* el ) -> bool {
		return std::any_of( toRemove.begin(), toRemove.end(), [&]( const SpriteComponent* el2 ) -> bool {
			return (el == el2);
		} );
	} ), m_spriteComponentsToDraw.end() );
}

void nb::GraphicsEngine::init( const CoreRef& core )
{
	core.world.s_onEntityAdded.connect_mem_fn_auto( &GraphicsEngine::onEntityAdded, *this );
	core.world.s_onEntitiesRemoved.connect_mem_fn_auto( &GraphicsEngine::onEntitiesRemoved, *this );

	window.create( sf::VideoMode( 1280, 720 ), "GraphicsEngine Window" );
	window.setVerticalSyncEnabled( true );

	shape.setRadius( 100.f );
	shape.setFillColor( sf::Color::Black );
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

	// sort?

	// draw
	window.clear( sf::Color::Green );
	window.draw( shape );

	for (const auto& spriteComponent : m_spriteComponentsToDraw)
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
