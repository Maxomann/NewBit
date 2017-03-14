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
	auto transform = getEntity()->getComponent<TransformationComponent>();
	m_connections.push_back( transform->s_positionXYChanged.connect( this, &onPositionXYChanged ) );
	m_connections.connect( transform->s_sizeChanged, this, &onSizeChanged );
	m_connections.connect( transform->s_rotationChanged, this, &onRotationChanged );
}

void nb::CameraComponent::destroy()
{
}

const View & nb::CameraComponent::getView() const
{
	return m_view;
}
