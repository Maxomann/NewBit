#include "GraphicsEngine.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::GraphicsEngine::init()
{
	m_window.create( sf::VideoMode( 1280, 720 ), "GraphicsEngine Window", Style::Titlebar | Style::Close );
	m_window.setVerticalSyncEnabled( true );

	r_renderSystem = getCore()->world.addSystem<RenderSystem>();
}

bool nb::GraphicsEngine::update()
{
	m_frameTime = m_clock.restart();

	// events
	sf::Event event;
	while (m_window.pollEvent( event ))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)
			m_window.close();

		s_onEvent.call( event );
	}

	// draw
	m_window.clear( sf::Color::Green );

	for (const auto& el : r_renderSystem->getCurrentDrawingData())
	{
		m_window.setView( *el.first );
		for (const auto& drawable : el.second)
			m_window.draw( *drawable );
	}
	m_window.setView( m_window.getDefaultView() );
	for (const auto& drawable : m_toDrawNextFrame)
		m_window.draw( *drawable );

	s_beforeDisplay.call( m_window );

	m_window.display();
	m_toDrawNextFrame.clear();

	return m_window.isOpen();
}

void nb::GraphicsEngine::drawNextFrame( sf::Drawable& drawable )
{
	m_toDrawNextFrame.push_back( &drawable );
}

sf::RenderWindow & nb::GraphicsEngine::getWindow()
{
	return m_window;
}

const sf::RenderWindow & nb::GraphicsEngine::getWindow() const
{
	return m_window;
}

const sf::Time & nb::GraphicsEngine::getFrameTime() const
{
	return m_frameTime;
}
