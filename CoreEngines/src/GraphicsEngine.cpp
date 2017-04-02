#include "GraphicsEngine.h"
using namespace std;
using namespace sf;
using namespace tgui;
using namespace nb;

void nb::GraphicsEngine::init()
{
	m_window.create( sf::VideoMode( 1280, 720 ), "GraphicsEngine Window", Style::Titlebar | Style::Close );
	m_window.setVerticalSyncEnabled( true );

	m_gui.setWindow( m_window );

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

		m_gui.handleEvent( event );
		s_onEvent.call( event );
	}

	// draw
	m_window.clear( sf::Color::Green );

	r_renderSystem->sort();
	for (const auto& cam : r_renderSystem->getCamerasForDrawing())
	{
		auto camLayer = cam->getComponent<TransformationComponent>()->getLayer();
		m_window.setView( cam->getComponent<CameraComponent>()->getView() );

		for (const auto& el : r_renderSystem->getEntitiesWithRenderComponentSorted())
		{
			if (el->getComponent<TransformationComponent>()->getLayer() == camLayer)
				for (const auto& drawable : el->getComponent<RenderComponent>()->getDrawingData())
					m_window.draw( *drawable );
		}

		for (const auto& debugEl : r_renderSystem->getDebugDrawingDataForLayer( camLayer ))
			m_window.draw( *debugEl );

		m_window.setView( m_window.getDefaultView() );
		for (const auto& drawable : m_toDrawNextFrame)
			m_window.draw( *drawable );
	}

	m_gui.draw();

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

tgui::Gui * nb::GraphicsEngine::getGui()
{
	return &m_gui;;
}

bool nb::GraphicsEngine::isGuiFocused() const
{
	const auto& widgets = m_gui.getWidgets();
	return any_of( widgets.begin(), widgets.end(), [&]( const shared_ptr<Widget>& el ) {return el->isFocused(); } );
}
