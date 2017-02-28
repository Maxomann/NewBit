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
	transform->s_positionXYChanged.connect_mem_fn_auto( &CameraComponent::onPositionXYChanged, *this );
	transform->s_sizeChanged.connect_mem_fn_auto( &CameraComponent::onSizeChanged, *this );
	transform->s_rotationChanged.connect_mem_fn_auto( &CameraComponent::onRotationChanged, *this );
}

void nb::CameraComponent::destroy()
{
}

const View & nb::CameraComponent::getView() const
{
	return m_view;
}
