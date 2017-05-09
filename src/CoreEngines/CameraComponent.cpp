#include "CameraComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::CameraComponent::onPositionXYChanged( const TransformationComponent*const transform,
											   sf::Vector2f oldPositionXY )
{
	m_view.setCenter( transform->getPositionXY() );
}

void nb::CameraComponent::onSizeChanged( const TransformationComponent*const transform, sf::Vector2f oldSize )
{
	m_view.setSize( Vector2f( transform->getSize() ) );
}

void nb::CameraComponent::onRotationChanged( const TransformationComponent*const transform, float oldRotation )
{
	m_view.setRotation( transform->getRotation() );
}

void nb::CameraComponent::init()
{
	auto transform = component<TransformationComponent>();

	//default values
	m_view.setCenter( Vector2f( transform->getPositionXY() ) );
	m_view.setSize( Vector2f( transform->getSize() ) );
	m_view.setRotation( transform->getRotation() );

	//connections
	transform->s_positionXYChanged.connect( this, &CameraComponent::onPositionXYChanged );
	transform->s_sizeChanged.connect( this, &CameraComponent::onSizeChanged );
	transform->s_rotationChanged.connect( this, &CameraComponent::onRotationChanged );
}

const View & nb::CameraComponent::getView() const
{
	return m_view;
}

sf::FloatRect nb::CameraComponent::getGlobalBounds() const
{
	sf::Vector2f size = m_view.getSize();
	sf::Vector2f center = m_view.getCenter();

	sf::RectangleShape shape;
	shape.setPosition( center.x - ( size.x / 2 ), center.y - ( size.y / 2 ) );
	shape.setSize( size );
	shape.setRotation( m_view.getRotation() );

	return shape.getGlobalBounds();
}
