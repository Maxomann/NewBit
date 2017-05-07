#include "BaseGameState.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::BaseGameState::init( const CoreEngineManager & coreEngines,
							  GameStateManager & gameStates )
{
	r_graphicsEngine = coreEngines.getEngine<GraphicsEngine>();

	world.addSystem<RenderSystem>();
	world.addSystem<TimeSystem>();
	world.addSystem<ChunkSystem>();
	world.addSystem<PhysicsSystem>();
	world.addSystem<WorldLoadStateSystem>();
	world.addSystem<NeedsSystem>();

	r_renderSystem = world.getSystem<RenderSystem>();

	gameStates.pushState( make_unique<WorldLoadingGameState>() );
	gameStates.pushState( make_unique<TestGameState>() );

	Entity cameraEntity;
	cameraEntity.addComponent<TransformationComponent>(
		Vector2i( 0, 0 ),
		0,
		Vector2f( 1280, 720 ) );
	cameraEntity.addComponent<CameraComponent>();
	cameraEntity.addComponent<PositionTrackerComponent>();
	cam = world.addEntity( move( cameraEntity ) );
}

void nb::BaseGameState::update( GameStateManager & gameStates )
{
	world.update();

	// draw
	const auto& camLayer = cam->getComponent<TransformationComponent>()->getLayer();
	const auto& camComponent = cam->getComponent<CameraComponent>();
	const auto& camView = camComponent->getView();
	const auto& camGlobalBounds = camComponent->getGlobalBounds();

	std::vector<RenderComponent*> componentsToDraw;

	//get to draw
	for( const auto& el : r_renderSystem->getRenderComponentsInWorld() )
	{
		if( el->getDrawingLayer() == camLayer &&
			el->getGlobalBounds().intersects( camGlobalBounds ) )
			componentsToDraw.push_back( el );
	}

	//sort
	std::sort( componentsToDraw.begin(), componentsToDraw.end(), [&] ( const RenderComponent* lhs, const RenderComponent* rhs ){
		// order: z^-1,y,x
		const auto& posLhs = lhs->getSortPositionXY();
		const auto& posRhs = rhs->getSortPositionXY();
		const auto& zVlaueLhs = lhs->getZValue();
		const auto& zVlaueRhs = rhs->getZValue();

		if( zVlaueRhs > zVlaueLhs )
			return true;
		else if( zVlaueRhs < zVlaueLhs )
			return false;
		else if( posRhs.y > posLhs.y )
			return true;
		else if( posRhs.y < posLhs.y )
			return false;
		else if( posRhs.x > posLhs.x )
			return true;
		else
			return false;
	} );

	std::vector<const sf::Drawable*const> toDraw;
	for( const auto& el : componentsToDraw )
		for( const auto& drawable : el->getDrawingData() )
			toDraw.push_back( drawable );

	for( const auto& debugEl : r_renderSystem->getDebugDrawingDataForLayer( camLayer ) )
		toDraw.push_back( debugEl.get() );

	r_graphicsEngine->drawNextFrame( move( toDraw ), camView );
}

void nb::BaseGameState::destroy( GameStateManager & gameStates )
{}
