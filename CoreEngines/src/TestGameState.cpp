#include "TestGameState.h"
using namespace std;
using namespace sf;
using namespace nb;

void TestGameState::init( const CoreRef& core )
{
	cout << "TestGameState init()" << endl;
	r_graphicsEngine = core.engines.getEngine<GraphicsEngine>();
	r_inputEngine = core.engines.getEngine<InputEngine>();
	r_resourceEngine = core.engines.getEngine<ResourceEngine>();

	r_inputEngine->s_whileKeyPressed[Keyboard::Key::T].connect_mem_fn_auto_track( &TestGameState::drawTestsprite, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::W].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->move( Vector2i( 0, -1 * r_graphicsEngine->getFrameTime().asMilliseconds() ) );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::S].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->move( Vector2i( 0, r_graphicsEngine->getFrameTime().asMilliseconds() ) );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::A].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->move( Vector2i( -1 * r_graphicsEngine->getFrameTime().asMilliseconds(), 0 ) );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::D].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->move( Vector2i( r_graphicsEngine->getFrameTime().asMilliseconds(), 0 ) );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::Q].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->rotate( -1 * r_graphicsEngine->getFrameTime().asMilliseconds() );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::E].connect_track( [&]() {
		m_camera->getComponent<TransformationComponent>()->rotate( r_graphicsEngine->getFrameTime().asMilliseconds() );
	}, *this );
	r_inputEngine->s_whileKeyPressed[Keyboard::Key::R].connect_track( [&]() {
		auto transform = m_camera->getComponent<TransformationComponent>();
		transform->setPosition( { 0,0 } );
		transform->setRotation( 0 );
	}, *this );

	auto testimage_file = r_resourceEngine->packages.getMetaFileById( "default:testimage" )->getConnectedFilePath();
	if (!m_texture.loadFromFile( testimage_file ))
		throw std::exception();
	auto testimage2_file = r_resourceEngine->packages.getMetaFileById( "default:testimage2" )->getConnectedFilePath();
	if (!m_texture2.loadFromFile( testimage2_file ))
		throw std::exception();

	m_sprite.setTexture( m_texture );

	m_debugEntity = core.world.createEntity<TransformationComponent, SpriteComponent>();
	auto spriteComponent = m_debugEntity->getComponent<SpriteComponent>();
	spriteComponent->setTexture( m_texture2 );
	auto transformationComponent = m_debugEntity->getComponent<TransformationComponent>();
	transformationComponent->setPosition( Vector2i( 0, 0 ) );
	transformationComponent->setSize( Vector2u( 182 * 2, 337 * 2 ) );
	transformationComponent->setRotation( 20.f );

	m_camera = core.world.createEntity<TransformationComponent, CameraComponent>();
	auto transformationComponent2 = m_camera->getComponent<TransformationComponent>();
	transformationComponent2->setSize( r_graphicsEngine->getWindow().getSize() );
	transformationComponent2->setPosition( Vector2i( 0, 0 ) );
	core.world.getSystem<RenderSystem>()->setCamerasForDrawing( { m_camera } );

	return;
}

void TestGameState::destroy( const CoreRef& coreRef )
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
	transform->setPosition( Vector2i( transform->getPosition().x + 1, transform->getPosition().y ) );
}
