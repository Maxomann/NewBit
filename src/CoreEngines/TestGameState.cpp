#include "TestGameState.h"
using namespace std;
using namespace sf;
using namespace tgui;
using namespace nb;

nb::TestGameState::TestGameState( World & world, Entity * camera )
	: world( world ),
	camera( camera )
{}

void TestGameState::init( const CoreEngineManager& coreEngines,
						  GameStateManager& gameStates )
{
	cout << "TestGameState init()" << endl;

	r_graphicsEngine = coreEngines.getEngine<GraphicsEngine>();
	r_gui = r_graphicsEngine->getGui();
	r_inputEngine = coreEngines.getEngine<InputEngine>();
	r_resourceEngine = coreEngines.getEngine<ResourceEngine>();

	r_chunkSystem = world.getSystem<ChunkSystem>();
	r_physicsSystem = world.getSystem<PhysicsSystem>();

	fpsLabel = Label::create();
	fpsLabel->setSize( Layout2d( 100, 40 ) );
	fpsLabel->setPosition( "{parent.width-width, 0}" );
	fpsLabel->setText( "0" );
	fpsLabel->setTextSize( 30 );
	r_gui->add( fpsLabel );

	// Input
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::Tab ].connect_track( m_connections, this, &TestGameState::drawTestsprite );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::Up ].connect_track( m_connections, [&] (){
		camera->getComponent<TransformationComponent>()->moveXY( Vector2i( 0, -1 * r_graphicsEngine->getFrameTime().asMilliseconds() ) );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::Down ].connect_track( m_connections, [&] (){
		camera->getComponent<TransformationComponent>()->moveXY( Vector2i( 0, r_graphicsEngine->getFrameTime().asMilliseconds() ) );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::Left ].connect_track( m_connections, [&] (){
		camera->getComponent<TransformationComponent>()->moveXY( Vector2i( -1 * r_graphicsEngine->getFrameTime().asMilliseconds(), 0 ) );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::Right ].connect_track( m_connections, [&] (){
		camera->getComponent<TransformationComponent>()->moveXY( Vector2i( r_graphicsEngine->getFrameTime().asMilliseconds(), 0 ) );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::Q ].connect_track( m_connections, [&] (){
		camera->getComponent<TransformationComponent>()->rotate( -1 * r_graphicsEngine->getFrameTime().asMilliseconds() );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::E ].connect_track( m_connections, [&] (){
		camera->getComponent<TransformationComponent>()->rotate( r_graphicsEngine->getFrameTime().asMilliseconds() );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::Add ].connect_track( m_connections, [&] (){
		auto size = camera->getComponent<TransformationComponent>()->getSize();
		//if (size.x > 200 && size.y > 200)
		camera->getComponent<TransformationComponent>()->scale( abs( 1.f - ( r_graphicsEngine->getFrameTime().asMilliseconds() / 120.f ) ) );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::Subtract ].connect_track( m_connections, [&] (){
		auto size = camera->getComponent<TransformationComponent>()->getSize();
		//if (size.x < 10000 && size.y < 10000)
		camera->getComponent<TransformationComponent>()->scale( abs( 1.f + ( r_graphicsEngine->getFrameTime().asMilliseconds() / 120.f ) ) );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::Z ].connect_track( m_connections, [&] (){
		auto cameraTransform = camera->getComponent<TransformationComponent>();
		cameraTransform->setSize( {1280,720} );
		cameraTransform->setRotation( 0 );

		if( m_debugEntity )
		{
			auto playerTransform = m_debugEntity->getComponent<TransformationComponent>();
			playerTransform->setPosition( {0,0,0} );
			playerTransform->setRotation( 0 );
		}
		else
		{
			cameraTransform->setPosition( {0,0,0} );
		}
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::R ].connect_track( m_connections, [&] (){
		auto cameraTransform = camera->getComponent<TransformationComponent>();
		cameraTransform->setSize( {1280,720} );
		cameraTransform->setRotation( 0 );
	} );
	r_inputEngine->s_onKeyPressed[ Keyboard::Key::T ].connect_track( m_connections, [&] (){
		auto chunkSystem = world.getSystem<ChunkSystem>();
		chunkSystem->removeEntitiesInChunk_if( {0,0,0}, [&] ( const Entity* entity ){
			if( entity != m_debugEntity && entity != camera )
				return true;
			else
				return false;
		} );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::W ].connect_track( m_connections, [&] (){
		if( !m_debugEntity )
			return;
		/*auto transform = m_debugEntity->getComponent<TransformationComponent>();
		auto offset = (int)(0.5f * static_cast<float>(r_graphicsEngine->getFrameTime().asMilliseconds()));
		transform->moveXY( Vector2i( 0, -offset ) );*/
		auto physics = m_debugEntity->getComponent<PhysicsComponent>();
		auto force = 0.0003f * static_cast<float>( r_graphicsEngine->getFrameTime().asMilliseconds() );
		if( r_inputEngine->isKeyPressed( Keyboard::Key::LShift ) )
			force *= 3.f;
		physics->getBody()->ApplyForceToCenter( b2Vec2( 0, -force ), true );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::S ].connect_track( m_connections, [&] (){
		if( !m_debugEntity )
			return;
		/*auto transform = m_debugEntity->getComponent<TransformationComponent>();
		auto offset = (int)(0.5f * static_cast<float>(r_graphicsEngine->getFrameTime().asMilliseconds()));
		transform->moveXY( Vector2i( 0, offset ) );*/
		auto physics = m_debugEntity->getComponent<PhysicsComponent>();
		auto force = 0.0003f * static_cast<float>( r_graphicsEngine->getFrameTime().asMilliseconds() );
		if( r_inputEngine->isKeyPressed( Keyboard::Key::LShift ) )
			force *= 3.f;
		physics->getBody()->ApplyForceToCenter( b2Vec2( 0, force ), true );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::A ].connect_track( m_connections, [&] (){
		if( !m_debugEntity )
			return;
		/*auto transform = m_debugEntity->getComponent<TransformationComponent>();
		auto offset = (int)(0.5f * static_cast<float>(r_graphicsEngine->getFrameTime().asMilliseconds()));
		transform->moveXY( Vector2i( -offset, 0 ) );*/
		auto physics = m_debugEntity->getComponent<PhysicsComponent>();
		auto force = 0.0003f * static_cast<float>( r_graphicsEngine->getFrameTime().asMilliseconds() );
		if( r_inputEngine->isKeyPressed( Keyboard::Key::LShift ) )
			force *= 3.f;
		physics->getBody()->ApplyForceToCenter( b2Vec2( -force, 0 ), true );
	} );
	r_inputEngine->s_whileKeyPressed[ Keyboard::Key::D ].connect_track( m_connections, [&] (){
		if( !m_debugEntity )
			return;
		/*auto transform = m_debugEntity->getComponent<TransformationComponent>();
		auto offset = (int)(0.5f * static_cast<float>(r_graphicsEngine->getFrameTime().asMilliseconds()));
		transform->moveXY( Vector2i( offset, 0 ) );*/
		auto physics = m_debugEntity->getComponent<PhysicsComponent>();
		auto force = 0.0003f * static_cast<float>( r_graphicsEngine->getFrameTime().asMilliseconds() );
		if( r_inputEngine->isKeyPressed( Keyboard::Key::LShift ) )
			force *= 3.f;
		physics->getBody()->ApplyForceToCenter( b2Vec2( force, 0 ), true );
	} );
	r_inputEngine->s_onKeyPressed[ Keyboard::Key::K ].connect_track( m_connections, [&] (){
		if( !m_debugEntity )
			return;
		auto transform = m_debugEntity->getComponent<TransformationComponent>();
		transform->moveLayer( 1 );
	} );
	r_inputEngine->s_onKeyPressed[ Keyboard::Key::L ].connect_track( m_connections, [&] (){
		if( !m_debugEntity )
			return;
		auto transform = m_debugEntity->getComponent<TransformationComponent>();
		transform->moveLayer( -1 );
	} );

	r_inputEngine->s_onKeyPressed[ Keyboard::Key::Return ].connect_track( m_connections, [&] (){
		m_debugEntity = world.addEntity( createHuman( r_resourceEngine ) );

		m_debugEntity->getComponent<PhysicsComponent>()->s_beginCollision.connect_track( m_connections, [&] ( auto physics ){
			auto& inventory = m_debugEntity->getComponent<InventoryComponent>()->inventory;
			auto entity = physics->entity();
			auto itemComp = entity->getComponent_try<ItemComponent>();
			if( itemComp )
			{
				if( inventory.addItem( itemComp->getItem() ) )
					world.removeEntity( entity );
			}
		} );

		auto cameraPositionTracker = camera->getComponent<PositionTrackerComponent>();
		cameraPositionTracker->setOffsetXY( {0, -32} );
		cameraPositionTracker->trackEntity( m_debugEntity );

		// EntityTrackerScreenGameState
		if( !r_entityTrackerScreenGameState )
			r_entityTrackerScreenGameState = gameStates.pushState_instant( make_unique<EntityTrackerScreenGameState>() );
		r_entityTrackerScreenGameState->track( m_debugEntity );
	} );

	r_inputEngine->s_onKeyPressed[ Keyboard::Key::O ].connect_track( m_connections, [&] (){
		gameStates.pushState_instant( make_unique<DemoEditGameState>( world, camera ) );
	} );
	r_inputEngine->s_onKeyPressed[ Keyboard::Key::P ].connect_track( m_connections, [&] (){
		gameStates.pushState_instant( make_unique<TilePaintGameState>( world, camera ) );
	} );

	r_inputEngine->s_onKeyPressed[ Keyboard::Key::Home ].connect_track( m_connections, [&] (){
		auto physics = world.getSystem<PhysicsSystem>();
		physics->setDebugDrawEnabled( !physics->isDebugDrawEnabled() );
	} );

	r_inputEngine->s_onMouseButtonPressedInWindow[ Mouse::Button::Middle ].connect_track( m_connections, [&] ( sf::Vector2i pixelPositionInWindow ){
		auto cameraComponent = camera->getComponent<CameraComponent>();
		auto transformationComponent = camera->getComponent<TransformationComponent>();
		auto placementPositionXY = sf::Vector2i( r_graphicsEngine->getWindow().mapPixelToCoords( pixelPositionInWindow, cameraComponent->getView() ) );
		auto entity = r_physicsSystem->getFirstEntityAtPixelPosition( Vector3i( placementPositionXY.x,
																				placementPositionXY.y,
																				transformationComponent->getLayer() ) );

		if( entity )
		{
			auto entityBounds = entity->getComponent<RenderComponent>()->getGlobalBounds();
			cout << entityBounds.left << ":" << entityBounds.top << "::" << entityBounds.width << ":" << entityBounds.height << endl;
		}
	} );

	r_inputEngine->s_onKeyPressed[ Keyboard::Key::H ].connect_track( m_connections, [&] (){
		if( m_debugEntity )
			m_debugEntity->getComponent<NeedsComponent>()->changeHunger( 10 );
	} );

	// logic
	r_resourceEngine->textures.getTextureReference( "default:texture:crosshair" )->applyTextureAndDefaultTextureRectToSprite( m_sprite );
	m_sprite.setOrigin( 8, 8 );
	auto windowSize = r_graphicsEngine->getWindow().getSize();
	m_sprite.setPosition( windowSize.x / 2.f, windowSize.y / 2.f );

	auto item = r_resourceEngine->items.getItem( 1 );
	for( int i = 0; i < 2; i++ )
	{
		auto itemEntity = ItemManager::createItemEntity( item, {60,60,0} );
		world.addEntity( move( itemEntity ) );
	}

	/*world().addEntities( r_worldGenerationEngine->generateChunk( { 0,0,0 } ) );
	world().addEntities( r_worldGenerationEngine->generateChunk( { 1,0,0 } ) );
	world().addEntities( r_worldGenerationEngine->generateChunk( { 2,0,0 } ) );
	world().addEntities( r_worldGenerationEngine->generateChunk( { 3,0,0 } ) );*/

	return;
}

void nb::TestGameState::update( GameStateManager& gameStates )
{
	const auto frameTimeAsMilliseconds = r_graphicsEngine->getFrameTime().asMilliseconds();
	fpsLabel->setText( to_string( frameTimeAsMilliseconds ) );

	return;
}

void TestGameState::destroy( GameStateManager& gameStates )
{
	r_gui->remove( fpsLabel );
	cout << "TestGameState destroy()" << endl;
}

void nb::TestGameState::drawTestsprite()
{
	r_graphicsEngine->drawNextFrame( m_sprite );
}
