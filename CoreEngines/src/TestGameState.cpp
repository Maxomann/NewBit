#include "TestGameState.h"
using namespace std;
using namespace nb;

void TestGameState::init( const CoreRef& core )
{
	cout << "TestGameState init()" << endl;

	core.engines.getEngine<InputEngine>()->s_whileQPressed.connect_mem_fn_auto( &TestGameState::drawTestsprite, *this );

	auto testimage_file = core.engines.getEngine<ResourceEngine>()->packages.getMetaFileById( "default:testimage" )->getConnectedFilePath();
	if (!m_texture.loadFromFile( testimage_file ))
		throw std::exception();
	auto testimage2_file = core.engines.getEngine<ResourceEngine>()->packages.getMetaFileById( "default:testimage2" )->getConnectedFilePath();
	if (!m_texture2.loadFromFile( testimage2_file ))
		throw std::exception();

	m_sprite.setTexture( m_texture );

	m_debugEntity = core.world.createEntity<SpriteComponent>();
	auto spriteComponent = m_debugEntity->getComponent<SpriteComponent>();
	spriteComponent->sprite.setTexture( m_texture2 );
	spriteComponent->sprite.setPosition( 100, 100 );

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

void nb::TestGameState::drawTestsprite( const CoreRef & core )
{
	core.engines.getEngine<GraphicsEngine>()->drawSpriteNextFrame( m_sprite );
	m_debugEntity->getComponent<SpriteComponent>()->sprite.move( 1, 0 );
}
