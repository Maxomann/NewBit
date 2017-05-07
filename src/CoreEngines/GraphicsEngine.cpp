#include "GraphicsEngine.h"
using namespace std;
using namespace sf;
using namespace tgui;
using namespace nb;

void nb::GraphicsEngine::init( const CoreEngineManager& coreEngines )
{
	m_window.create( sf::VideoMode( 1280, 720 ), "GraphicsEngine Window", Style::Titlebar | Style::Close );
	m_window.setVerticalSyncEnabled( true );

	m_gui.setWindow( m_window );
}

bool nb::GraphicsEngine::update()
{
	m_frameTime = m_clock.restart();

	// events
	sf::Event event;
	while( m_window.pollEvent( event ) )
	{
		if( event.type == sf::Event::Closed )
			m_window.close();
		if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape )
			m_window.close();

		m_gui.handleEvent( event );
		s_onEvent.call( event );
	}

	// draw
	m_window.clear( sf::Color::Green );

	for( const auto& el : m_toDrawNextFrameWithView )
	{
		//draw
		m_window.setView( el.first );

		for( const auto& drawable : el.second )
			m_window.draw( *drawable );
	}
	m_window.setView( m_window.getDefaultView() );

	for( const auto& drawable : m_toDrawNextFrame )
		m_window.draw( *drawable );

	m_gui.draw();

	m_window.display();
	m_toDrawNextFrame.clear();

	return m_window.isOpen();
}

void nb::GraphicsEngine::drawNextFrame( sf::Drawable& drawable )
{
	m_toDrawNextFrame.push_back( &drawable );
}

void nb::GraphicsEngine::drawNextFrame( std::vector<const sf::Drawable*const> drawables, sf::View view )
{
	m_toDrawNextFrameWithView.push_back( make_pair( move( view ), move( drawables ) ) );
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

tgui::Gui * nb::GraphicsEngine::getGui()
{
	return &m_gui;;
}

bool nb::GraphicsEngine::isGuiFocused() const
{
	const auto& widgets = m_gui.getWidgets();
	return any_of( widgets.begin(), widgets.end(), [&] ( const shared_ptr<Widget>& el ){return el->isFocused(); } );
}
