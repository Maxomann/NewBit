#include "DemoEditGameState.h"
using namespace std;
using namespace sf;
using namespace tgui;
using namespace nb;

nb::DemoEditGameState::DemoEditGameState( World & world, Entity* camera )
	: world( world ),
	camera( camera )
{}

void nb::DemoEditGameState::init( const CoreEngineManager & coreEngines,
								  GameStateManager & gameStates )
{
	r_graphicsEngine = coreEngines.getEngine<GraphicsEngine>();
	r_gui = r_graphicsEngine->getGui();
	r_inputEngine = coreEngines.getEngine<InputEngine>();
	r_resourceEngine = coreEngines.getEngine<ResourceEngine>();

	m_childWindow = ChildWindow::create();
	m_childWindow->setSize( {200,240} );
	m_childWindow->setTitle( "Demo Edit" );
	m_childWindow->keepInParent( true );
	m_childWindow->connect( "Closed", [&] (){
		this->close();
	} );

	m_EntityCountLabel = Label::create();
	m_EntityCountLabel->setSize( {140,40} );
	m_EntityCountLabel->setText( "Entity count:" );
	m_childWindow->add( m_EntityCountLabel );

	m_EntityCountValueLabel = Label::create();
	m_EntityCountValueLabel->setSize( {60,40} );
	m_EntityCountValueLabel->setPosition( {140,0} );
	m_EntityCountValueLabel->setText( to_string( world.getEntityCount() ) );
	m_childWindow->add( m_EntityCountValueLabel );

	objectListBox = ListBox::create();
	objectListBox->setSize( {200, 200} );
	objectListBox->setPosition( {0, 40} );
	m_childWindow->add( objectListBox );

	for( const auto& el : r_resourceEngine->entitiyFactories.getAllFactories() )
		objectListBox->addItem( el.second->getName() + "(id:" + to_string( el.second->getId() ) + ")", to_string( el.second->getId() ) );

	r_gui->add( m_childWindow );

	// logic

	world.s_onEntityCountChanged.connect_track( m_connections, [&] ( unsigned int newCount ){
		m_EntityCountValueLabel->setText( to_string( newCount ) );
	} );

	r_inputEngine->s_onMouseButtonPressedInWindow[ Mouse::Button::Left ].connect_track( m_connections, [&] ( Vector2i mousePosition ){
		if( r_graphicsEngine->isGuiFocused() )
			return;
		auto selectedObjectIdString = objectListBox->getSelectedItemId();
		if( !selectedObjectIdString.getSize() )
			return;
		auto selectedObjectId = atoi( selectedObjectIdString.toAnsiString().c_str() );

		auto placementPositionXY = static_cast<sf::Vector2i>( r_graphicsEngine->getWindow().mapPixelToCoords( mousePosition, camera->getComponent<CameraComponent>()->getView() ) );
		auto placementLayer = camera->getComponent<TransformationComponent>()->getLayer();

		auto entity = r_resourceEngine->entitiyFactories.getFactoryById( selectedObjectId )->create( *r_resourceEngine );
		auto transformComponent = entity.getComponent_try<TransformationComponent>();
		if( transformComponent )
		{
			if( r_inputEngine->isKeyPressed( sf::Keyboard::LShift ) )
			{
				// snap to grid
				auto newPosition = Tile::calculateTilePositionForPixelPosition( sf::Vector3i( placementPositionXY.x,
																							  placementPositionXY.y,
																							  placementLayer ) );
				newPosition.x =
					( newPosition.x * Tile::TILE_SIZE_IN_PIXEL ) +
					Tile::TILE_SIZE_IN_PIXEL / 2;
				newPosition.y =
					( newPosition.y * Tile::TILE_SIZE_IN_PIXEL ) +
					Tile::TILE_SIZE_IN_PIXEL;

				transformComponent->setPosition( newPosition );
			}
			else
			{
				transformComponent->setPosition( sf::Vector3i( placementPositionXY.x,
															   placementPositionXY.y,
															   placementLayer ) );
			}
		}
		world.addEntity( move( entity ) );
	} );

	r_inputEngine->s_onMouseButtonPressedInWindow[ Mouse::Button::Right ].connect_track( m_connections, [&] ( Vector2i mousePosition ){
		if( r_graphicsEngine->isGuiFocused() )
			return;
		auto placementPositionXY = static_cast<sf::Vector2i>( r_graphicsEngine->getWindow().mapPixelToCoords( mousePosition, camera->getComponent<CameraComponent>()->getView() ) );

		const auto entity = world.getSystem<PhysicsSystem>()->getFirstEntityAtPixelPosition( Vector3i( placementPositionXY.x,
																									   placementPositionXY.y,
																									   camera->getComponent<TransformationComponent>()->getLayer() ) );
		if( entity )
			world.removeEntity( entity );
	} );
}

void nb::DemoEditGameState::update( GameStateManager & gameStates )
{}

void nb::DemoEditGameState::destroy( GameStateManager & gameStates )
{
	r_gui->remove( m_childWindow );
}
