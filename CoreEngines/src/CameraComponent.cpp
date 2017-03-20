#include "CameraComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::CameraComponent::onPositionXYChanged( const TransformationComponent*const transform, sf::Vector2i oldPositionXY )
{
	m_view.setCenter( Vector2f( transform->getPositionXY() ) );
}

void nb::CameraComponent::onSizeChanged( const TransformationComponent*const transform, sf::Vector2u oldSize )
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

void nb::CameraComponent::destroy()
{
}

const View & nb::CameraComponent::getView() const
{
	return m_view;
}
