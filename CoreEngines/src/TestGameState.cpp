#include "TestGameState.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::TestGameState::addALotOfEntities( const CoreRef & core )
{
	int min = -20;
	int max = 20;

	bool b = true;

	for (int x = min; x < max; x++)
	{
		for (int y = min; y < max; y++)
		{
			auto ent = core.world.createEntity<TransformationComponent, SpriteComponent>();
			auto spriteComponent = ent->getComponent<SpriteComponent>();
			if (b)
				spriteComponent->setTexture( m_texture_grass );
			else
				spriteComponent->setTexture( m_texture_sand );
			b = !b;
			auto transformationComponent = ent->getComponent<TransformationComponent>();
			transformationComponent->setPositionXY( Vector2i( x * 32, y * 32 ) );
			transformationComponent->setSize( Vector2u( 32, 32 ) );
			transformationComponent->setRotation( 0.f );
		}
	}
}

void TestGameState::init()
{
	auto core = getCore();
	r_core = core;

	cout << "TestGameState init()" << endl;
	r_graphicsEngine = core->engines.getEngine<GraphicsEngine>();
	r_inputEngine = core->engines.getEngine<InputEngine>();
	r_resourceEngine = core->engines.getEngine<ResourceEngine>();

	r_inputEngine->s_whileKeyPressed[Keyboard::Key::T].connect_mem_fn_auto_track( &TestGameState::drawTestsprite, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::W].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->moveXY( Vector2i( 0, -1 * r_graphicsEngine->getFrameTime().asMilliseconds() ) );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::S].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->moveXY( Vector2i( 0, r_graphicsEngine->getFrameTime().asMilliseconds() ) );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::A].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->moveXY( Vector2i( -1 * r_graphicsEngine->getFrameTime().asMilliseconds(), 0 ) );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::D].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->moveXY( Vector2i( r_graphicsEngine->getFrameTime().asMilliseconds(), 0 ) );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::Q].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->rotate( -1 * r_graphicsEngine->getFrameTime().asMilliseconds() );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::E].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->rotate( r_graphicsEngine->getFrameTime().asMilliseconds() );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::Add].connect_track( [&]() {
		auto size = m_camera->getComponent<TransformationComponent>()->getSize();
		if (size.x > 200 && size.y > 200)
			m_camera->getComponent<TransformationComponent>()->scale( 1.f - (r_graphicsEngine->getFrameTime().asMilliseconds() / 120.f) );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::Subtract].connect_track( [&]() {
		auto size = m_camera->getComponent<TransformationComponent>()->getSize();
		if (size.x < 10000 && size.y < 10000)
			m_camera->getComponent<TransformationComponent>()->scale( 1.f + (r_graphicsEngine->getFrameTime().asMilliseconds() / 120.f) );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::R].connect_track( [&]() {
		auto transform = m_camera->getComponent<TransformationComponent>();
		transform->setPositionXY( { 0,0 } );
		transform->setRotation( 0 );
		transform->setSize( r_graphicsEngine->getWindow().getSize() );

		transform = m_debugEntity->getComponent<TransformationComponent>();
		transform->setPositionXY( { 0,0 } );
	}, *this );
	r_inputEngine->s_onKeyPressed[Keyboard::Key::T].connect_track( [&]() {
		auto chunkSystem = r_core->world.getSystem<ChunkSystem>();
		chunkSystem->removeEntitiesInChunk_if( { 0,0,0 }, [&]( const Entity* entity ) {
			if (entity != m_debugEntity && entity != m_camera)
				return true;
			else
				return false;
		} );
	}, *this );

	auto testimage_file = r_resourceEngine->packages.getMetaFileById( "default:testimage" )->getConnectedFilePath();
	if (!m_texture.loadFromFile( testimage_file ))
		throw std::exception();
	auto testimage2_file = r_resourceEngine->packages.getMetaFileById( "default:testimage2" )->getConnectedFilePath();
	if (!m_texture2.loadFromFile( testimage2_file ))
		throw std::exception();
	auto grass_file = r_resourceEngine->packages.getMetaFileById( "default:field_grass" )->getConnectedFilePath();
	if (!m_texture_grass.loadFromFile( grass_file ))
		throw std::exception();
	auto sand_file = r_resourceEngine->packages.getMetaFileById( "default:field_sand" )->getConnectedFilePath();
	if (!m_texture_sand.loadFromFile( sand_file ))
		throw std::exception();

	m_sprite.setTexture( m_texture );

	m_debugEntity = core->world.createEntity<TransformationComponent, SpriteComponent>();
	auto spriteComponent = m_debugEntity->getComponent<SpriteComponent>();
	spriteComponent->setTexture( m_texture2 );
	auto transformationComponent = m_debugEntity->getComponent<TransformationComponent>();
	transformationComponent->setPositionXY( Vector2i( 0, 0 ) );
	transformationComponent->setSize( Vector2u( 182 * 2, 337 * 2 ) );
	transformationComponent->setRotation( 20.f );

	m_camera = core->world.createEntity<TransformationComponent, CameraComponent>();
	auto transformationComponent2 = m_camera->getComponent<TransformationComponent>();
	transformationComponent2->setSize( r_graphicsEngine->getWindow().getSize() );
	transformationComponent2->setPositionXY( Vector2i( 0, 0 ) );
	core->world.getSystem<RenderSystem>()->setCamerasForDrawing( { m_camera } );

	addALotOfEntities( *core );

	return;
}

void TestGameState::destroy()
{
	cout << "TestGameState destroy()" << endl;
}

bool TestGameState::shouldDestroy()
{
	return false;
}

void nb::TestGameState::drawTestsprite()
{
	r_graphicsEngine->drawNextFrame( m_sprite );

	auto transform = m_debugEntity->getComponent<TransformationComponent>();
	transform->setPositionXY( Vector2i( transform->getPositionXY().x + 1, transform->getPositionXY().y ) );
}
