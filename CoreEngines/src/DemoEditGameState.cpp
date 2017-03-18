#include "DemoEditGameState.h"
using namespace std;
using namespace sf;
using namespace tgui;
using namespace nb;

void nb::DemoEditGameState::init()
{
	r_gui = getCore()->engines.getEngine<GuiEngine>()->getGui();
	r_inputEngine = getCore()->engines.getEngine<InputEngine>();
	r_graphicsEngine = getCore()->engines.getEngine<GraphicsEngine>();
	r_resourceEngine = getCore()->engines.getEngine<ResourceEngine>();

	m_childWindow = ChildWindow::create();
	m_childWindow->setSize( { 200,80 } );
	m_childWindow->setTitle( "Demo Edit" );
	m_childWindow->keepInParent( true );

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

	m_childWindow->connect( "Closed", [&]() {
		m_shouldDestroy = true;
	} );

	getCore()->world.s_onEntityCountChanged.connect_track( m_connections, [&]( unsigned int newCount ) {
		m_EntityCountValueLabel->setText( to_string( newCount ) );
	} );

	r_inputEngine->s_onMouseButtonPressedInWindow[Mouse::Button::Left].connect_track( m_connections, [&]( Vector2i mousePosition ) {
		auto& widgets = r_gui->getWidgets();
		if (any_of( widgets.begin(), widgets.end(), [&]( const shared_ptr<Widget>& el ) {return el->isFocused(); } ))
			return;
		auto* camera = getCore()->world.getSystem<RenderSystem>()->getCamerasForDrawing().at( 0 )->getComponent<CameraComponent>();
		auto placementPosition = static_cast<sf::Vector2i>(r_graphicsEngine->getWindow().mapPixelToCoords( mousePosition, camera->getView() ));

		auto entity = getCore()->world.createEntity<
			TransformationComponent,
			RenderComponent,
			SpriteComponent>();
		auto spriteComponent = entity->getComponent<SpriteComponent>();
		spriteComponent->setTexture( *r_resourceEngine->textures.getTextureReference( "default:texture:object_tree" ) );
		auto transformationComponent = entity->getComponent<TransformationComponent>();
		transformationComponent->setSize( Vector2u( 48 * 2, 64 * 2 ) );
		transformationComponent->setPositionXY( placementPosition );
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
