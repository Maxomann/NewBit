#include "PlayingGameState.h"
using namespace std;
using namespace sf;
using namespace nb;
using namespace tgui;

nb::PlayingGameState::PlayingGameState( World & world,
										Entity * camera )
	: world( world ),
	camera( camera )
{}

void nb::PlayingGameState::init( const CoreEngineManager & coreEngines,
								 GameStateManager & gameStates )
{
	gui = coreEngines.getEngine<GraphicsEngine>()->getGui();

	barContainer = HorizontalLayout::create();
	barContainer->setSize( {720, 20} );
	barContainer->setPosition( "( parent.width - width ) / 2", "parent.height - height - 40" );

	healthBar = ProgressBar::create();
	healthBar->setSize( 0, "parent.height" );
	healthBar->getRenderer()->setFillColor( sf::Color::Red );
	healthBar->setMinimum( 0 );
	healthBar->setMaximum( 100 );
	healthBar->setValue( 50 );

	barContainer->add( healthBar );
	barContainer->insertSpace( 1, 0.1f );

	thirstBar = ProgressBar::create();
	thirstBar->setSize( 0, "parent.height" );
	thirstBar->getRenderer()->setFillColor( sf::Color::Blue );
	thirstBar->setMinimum( 0 );
	thirstBar->setMaximum( 100 );
	thirstBar->setValue( 50 );

	barContainer->add( thirstBar );
	barContainer->insertSpace( 3, 0.1f );

	energyBar = ProgressBar::create();
	energyBar->setSize( 0, "parent.height" );
	energyBar->getRenderer()->setFillColor( sf::Color::Yellow );
	energyBar->setMinimum( 0 );
	energyBar->setMaximum( 100 );
	energyBar->setValue( 50 );

	barContainer->add( energyBar );

	gui->add( barContainer );
}

void nb::PlayingGameState::update( GameStateManager & gameStates )
{}

void nb::PlayingGameState::destroy( GameStateManager & gameStates )
{
	gui->remove( barContainer );
}
