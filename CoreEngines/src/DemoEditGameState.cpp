#include "DemoEditGameState.h"
using namespace std;
using namespace sf;
using namespace tgui;
using namespace nb;

void nb::DemoEditGameState::init()
{
	r_gui = getCore()->engines.getEngine<GraphicsEngine>()->getGui();
	r_inputEngine = getCore()->engines.getEngine<InputEngine>();
	r_graphicsEngine = getCore()->engines.getEngine<GraphicsEngine>();
	r_resourceEngine = getCore()->engines.getEngine<ResourceEngine>();

	m_childWindow = ChildWindow::create();
	m_childWindow->setSize( { 200,80 } );
	m_childWindow->setTitle( "Demo Edit" );
	m_childWindow->keepInParent( true );
	m_childWindow->connect( "Closed", [&]() {
		m_shouldDestroy = true;
	} );

	m_EntityCountLabel = Label::create();
	m_EntityCountLabel->setSize( { 140,40 } );
	m_EntityCountLabel->setText( "Entity count:" );
	m_childWindow->add( m_EntityCountLabel );

	m_EntityCountValueLabel = Label::create();
	m_EntityCountValueLabel->setSize( { 60,40 } );
	m_EntityCountValueLabel->setPosition( { 140,0 } );
	m_EntityCountValueLabel->setText( to_string( getCore()->world.getEntityCount() ) );
	m_childWindow->add( m_EntityCountValueLabel );

	r_gui->add( m_childWindow );

	getCore()->world.s_onEntityCountChanged.connect_track( m_connections, [&]( unsigned int newCount ) {
		m_EntityCountValueLabel->setText( to_string( newCount ) );
	} );

	r_inputEngine->s_onMouseButtonPressedInWindow[Mouse::Button::Left].connect_track( m_connections, [&]( Vector2i mousePosition ) {
		if (engine<GraphicsEngine>()->isGuiFocused())
			return;
		auto* camera = getCore()->world.getSystem<RenderSystem>()->getCamerasForDrawing().at( 0 );
		auto placementPositionXY = static_cast<sf::Vector2i>(r_graphicsEngine->getWindow().mapPixelToCoords( mousePosition, camera->getComponent<CameraComponent>()->getView() ));

		getCore()->world.addEntity( createTree( engines(), Vector3i( placementPositionXY.x,
																	 placementPositionXY.y,
																	 camera->getComponent<TransformationComponent>()->getLayer() ) ) );
	} );

	r_inputEngine->s_onMouseButtonPressedInWindow[Mouse::Button::Right].connect_track( m_connections, [&]( Vector2i mousePosition ) {
		if (engine<GraphicsEngine>()->isGuiFocused())
			return;
		auto* camera = getCore()->world.getSystem<RenderSystem>()->getCamerasForDrawing().at( 0 );
		auto placementPositionXY = static_cast<sf::Vector2i>(r_graphicsEngine->getWindow().mapPixelToCoords( mousePosition, camera->getComponent<CameraComponent>()->getView() ));

		const auto entity = getCore()->world.getSystem<PhysicsSystem>()->getFirstEntityAtPixelPosition( Vector3i( placementPositionXY.x,
																												  placementPositionXY.y,
																												  camera->getComponent<TransformationComponent>()->getLayer() ) );
		if (entity)
			world().removeEntity( entity );
	} );
}

void nb::DemoEditGameState::update()
{
}

void nb::DemoEditGameState::destroy()
{
	r_gui->remove( m_childWindow );
}

bool nb::DemoEditGameState::shouldDestroy()
{
	return m_shouldDestroy;
}
