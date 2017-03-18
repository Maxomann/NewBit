#include "EntityTrackerScreenGameState.h"
using namespace std;
using namespace sf;
using namespace tgui;
using namespace nb;

void nb::EntityTrackerScreenGameState::init()
{
	r_gui = getCore()->engines.getEngine<GuiEngine>()->getGui();

	// GUI
	m_playerStatsWindow = ChildWindow::create();
	m_playerStatsWindow->setTitle( "Entity Stats" );
	m_playerStatsWindow->setSize( Layout2d( 400, 200 ) );
	m_playerStatsWindow->setPosition( Layout2d( 0, 0 ) );
	m_playerStatsWindow->keepInParent( true );
	m_playerStatsWindow->setTitleButtons( ChildWindow::TitleButton::None );

	m_playerPositionLabel = Label::create();
	m_playerPositionLabel->setSize( Layout2d( 200, 40 ) );
	m_playerPositionLabel->setPosition( Layout2d( 0, 0 ) );
	m_playerPositionLabel->setText( "Position:" );
	m_playerStatsWindow->add( m_playerPositionLabel );

	m_playerPositionValueLabel = Label::create();
	m_playerPositionValueLabel->setSize( Layout2d( 200, 40 ) );
	m_playerPositionValueLabel->setPosition( Layout2d( 200, 0 ) );
	m_playerPositionValueLabel->setText( "Not Available" );
	m_playerStatsWindow->add( m_playerPositionValueLabel );

	m_playerSpritePathLabel = Label::create();
	m_playerSpritePathLabel->setSize( Layout2d( 200, 40 ) );
	m_playerSpritePathLabel->setPosition( Layout2d( 0, 40 ) );
	m_playerSpritePathLabel->setText( "GlTextureHandle:" );
	m_playerStatsWindow->add( m_playerSpritePathLabel );

	m_playerSpritePathValueLabel = Label::create();
	m_playerSpritePathValueLabel->setSize( Layout2d( 200, 40 ) );
	m_playerSpritePathValueLabel->setPosition( Layout2d( 200, 40 ) );
	m_playerSpritePathValueLabel->setText( "Not Available" );
	m_playerStatsWindow->add( m_playerSpritePathValueLabel );

	m_playerHealthLabel = Label::create();
	m_playerHealthLabel->setSize( Layout2d( 200, 40 ) );
	m_playerHealthLabel->setPosition( Layout2d( 0, 80 ) );
	m_playerHealthLabel->setText( "Health:" );
	m_playerStatsWindow->add( m_playerHealthLabel );

	m_playerHealthValueLabel = Label::create();
	m_playerHealthValueLabel->setSize( Layout2d( 200, 40 ) );
	m_playerHealthValueLabel->setPosition( Layout2d( 200, 80 ) );
	m_playerHealthValueLabel->setText( "Not Available" );
	m_playerStatsWindow->add( m_playerHealthValueLabel );

	r_gui->add( m_playerStatsWindow );
}

void nb::EntityTrackerScreenGameState::update()
{
}

void nb::EntityTrackerScreenGameState::destroy()
{
	r_gui->remove( m_playerStatsWindow );
}

bool nb::EntityTrackerScreenGameState::shouldDestroy()
{
	return false;
}

void nb::EntityTrackerScreenGameState::track( const Entity* entity )
{
	auto transform = entity->getComponent_try<TransformationComponent>();
	if (transform)
	{
		auto position = transform->getPosition();
		m_playerPositionValueLabel->setText( "X: " + to_string( position.x ) +
											 " Y: " + to_string( position.y ) +
											 " Z: " + to_string( position.z ) );
		transform->s_positionChanged.connect_track( m_connections, [&]( const TransformationComponent* const comp,
																		sf::Vector3i oldPosition ) {
			auto position = comp->getPosition();
			m_playerPositionValueLabel->setText( "X: " + to_string( position.x ) +
												 " Y: " + to_string( position.y ) +
												 " Z: " + to_string( position.z ) );
		} );
	}

	auto sprite = entity->getComponent_try<SpriteComponent>();
	if (sprite)
	{
		m_playerSpritePathValueLabel->setText( to_string( sprite->getSprite().getTexture()->getNativeHandle() ) );
	}

	auto health = entity->getComponent_try<HealthComponent>();
	if (health)
	{
		auto val = health->getHealth();
		m_playerHealthValueLabel->setText( to_string( val ) );
		health->s_onChange.connect_track( m_connections, [&]( const HealthComponent* const comp,
															  int health ) {
			m_playerHealthValueLabel->setText( to_string( health ) );
		} );
	}
}
