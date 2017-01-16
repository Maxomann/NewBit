#include "TestGameState.h"
using namespace std;
using namespace nb;

void TestGameState::init( const CoreRefs& coreRefs )
{
	cout << "TestGameState init()" << endl;

	coreRefs.engines.getEngine<InputEngine>()->s_whileQPressed.connect_mem_fn_auto( &TestGameState::drawTestsprite, *this );

	if( !m_texture.loadFromFile( "./data/debug_CoreEngines/mario.png" ) )
		throw std::exception();
	m_sprite.setTexture( m_texture );

	volatile int a = 0;
}

void TestGameState::destroy( const CoreRefs& coreRefs )
{
	cout << "TestGameState destroy()" << endl;
}

bool TestGameState::shouldDestroy()
{
	return false;
}

void nb::TestGameState::drawTestsprite( const CoreRefs & core )
{
	core.engines.getEngine<RenderEngine>()->drawSpriteNextFrame( m_sprite );
}
