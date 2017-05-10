#include "PlayingGameState.h"
using namespace std;
using namespace sf;
using namespace nb;
using namespace tgui;

std::pair<bool, float> PlayingGameState::getWSADMovement( bool w, bool s, bool a, bool d )const
{
	bool shouldMove = false;
	float angle = 0;

	if( w && s && a && d )
	{
		shouldMove = false;
	}
	else if( w && s && a )
	{
		shouldMove = true;
		angle = 270.f;
	}
	else if( w && s && d )
	{
		shouldMove = true;
		angle = 90.f;
	}
	else if( a && s && d )
	{
		shouldMove = true;
		angle = 180.f;
	}
	else if( a && w && d )
	{
		shouldMove = true;
		angle = 0;
	}
	else if( w && a )
	{
		shouldMove = true;
		angle = 315.f;
	}
	else if( w && s )
	{
		shouldMove = false;
	}
	else if( w && d )
	{
		shouldMove = true;
		angle = 45.f;
	}
	else if( a && s )
	{
		shouldMove = true;
		angle = 225.f;
	}
	else if( a && d )
	{
		shouldMove = false;
	}
	else if( s && d )
	{
		shouldMove = true;
		angle = 135.f;
	}
	else if( w )
	{
		shouldMove = true;
		angle = 0.f;
	}
	else if( s )
	{
		shouldMove = true;
		angle = 180.f;
	}
	else if( a )
	{
		shouldMove = true;
		angle = 270.f;
	}
	else if( d )
	{
		shouldMove = true;
		angle = 90.f;
	}

	return {shouldMove, angle};
}

nb::PlayingGameState::PlayingGameState( World & world,
										Entity * camera )
	: world( world ),
	camera( camera )
{}

void nb::PlayingGameState::init( const CoreEngineManager & coreEngines,
								 GameStateManager & gameStates )
{
	// References

	graphicsEngine = coreEngines.getEngine<GraphicsEngine>();
	gui = graphicsEngine->getGui();
	resourceEngine = coreEngines.getEngine<ResourceEngine>();
	inputEngine = coreEngines.getEngine<InputEngine>();

	// UI

	barContainer = VerticalLayout::create();
	barContainer->setSize( {200, 120} );
	barContainer->setPosition( 20, 20 );

	healthBar = ProgressBar::create();
	healthBar->setSize( "parent.width", "parent.height" );
	healthBar->getRenderer()->setFillColor( sf::Color::Red );
	healthBar->setMinimum( 0 );
	healthBar->setMaximum( 100 );
	healthBar->setValue( 50 );

	barContainer->add( healthBar );
	barContainer->insertSpace( 1, 0.4f );

	hungerBar = ProgressBar::create();
	hungerBar->setSize( "parent.width", "parent.height" );
	hungerBar->getRenderer()->setFillColor( sf::Color::Magenta );
	hungerBar->setMinimum( 0 );
	hungerBar->setMaximum( 100 );
	hungerBar->setValue( 50 );

	barContainer->add( hungerBar );
	barContainer->insertSpace( 3, 0.4f );

	thirstBar = ProgressBar::create();
	thirstBar->setSize( "parent.width", "parent.height" );
	thirstBar->getRenderer()->setFillColor( sf::Color::Blue );
	thirstBar->setMinimum( 0 );
	thirstBar->setMaximum( 100 );
	thirstBar->setValue( 50 );

	barContainer->add( thirstBar );
	barContainer->insertSpace( 5, 0.4f );

	energyBar = ProgressBar::create();
	energyBar->setSize( "parent.width", "parent.height" );
	energyBar->getRenderer()->setFillColor( sf::Color::Yellow );
	energyBar->setMinimum( 0 );
	energyBar->setMaximum( 100 );
	energyBar->setValue( 50 );

	barContainer->add( energyBar );

	gui->add( barContainer );

	// Player

	player = world.addEntity( createHuman( resourceEngine ) );
	playerPhysics = player->getComponent<PhysicsComponent>();

	auto cameraPositionTracker = camera->getComponent<PositionTrackerComponent>();
	cameraPositionTracker->setOffsetXY( {0, -32} );
	cameraPositionTracker->trackEntity( player );

	// UI Callbacks

	auto healthComponent = player->getComponent<HealthComponent>();
	auto needsComponent = player->getComponent<NeedsComponent>();

	healthBar->setValue( static_cast<unsigned int>( healthComponent->getHealth() ) );
	healthComponent->s_onChange.connect_track( connections, [&] ( auto comp, float amount ){
		healthBar->setValue( static_cast<unsigned int>( round( comp->getHealth() ) ) );
	} );

	hungerBar->setValue( static_cast<unsigned int>( needsComponent->getHunger() ) );
	needsComponent->s_hungerChanged.connect_track( connections, [&] ( auto comp, float amount ){
		hungerBar->setValue( static_cast<unsigned int>( round( comp->getHunger() ) ) );
	} );

	thirstBar->setValue( static_cast<unsigned int>( needsComponent->getThirst() ) );
	needsComponent->s_thirstChanged.connect_track( connections, [&] ( auto comp, float amount ){
		thirstBar->setValue( static_cast<unsigned int>( round( comp->getThirst() ) ) );
	} );

	energyBar->setValue( static_cast<unsigned int>( needsComponent->getEnergy() ) );
	needsComponent->s_energyChanged.connect_track( connections, [&] ( auto comp, float amount ){
		energyBar->setValue( static_cast<unsigned int>( round( comp->getEnergy() ) ) );
	} );

	// Input Callbacks
}

void nb::PlayingGameState::update( GameStateManager & gameStates )
{
	float frameTimeAsMilliseconds = static_cast<float>( graphicsEngine->getFrameTime().asMilliseconds() );

	// Movement

	bool shouldMove = false;
	float angle = 0;

	float force = 0.0003f * frameTimeAsMilliseconds;
	if( inputEngine->isKeyPressed( Keyboard::Key::LShift ) )
		force *= 3.f;

	bool w = inputEngine->isKeyPressed( Keyboard::Key::W );
	bool s = inputEngine->isKeyPressed( Keyboard::Key::S );
	bool a = inputEngine->isKeyPressed( Keyboard::Key::A );
	bool d = inputEngine->isKeyPressed( Keyboard::Key::D );

	auto moveResult = getWSADMovement( w, s, a, d );
	shouldMove = moveResult.first;
	angle = moveResult.second;

	sf::Vector2f movementVector( 0, -1.f * force );
	auto newVec = rotateVector( movementVector, angle );

	if( shouldMove )
		playerPhysics->getBody()->ApplyForceToCenter( b2Vec2( newVec.x,
															  newVec.y ), true );
}

void nb::PlayingGameState::destroy( GameStateManager & gameStates )
{
	gui->remove( barContainer );
}
