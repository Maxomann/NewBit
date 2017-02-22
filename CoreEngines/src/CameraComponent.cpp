#include "CameraComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::CameraComponent::onPositionChanged( const TransformationComponent & transform )
{
	m_view.setCenter( Vector2f( transform.getPositionXY() ) );
}

void nb::CameraComponent::onSizeChanged( const TransformationComponent & transform )
{
	m_view.setSize( Vector2f( transform.getSize() ) );
}

void nb::CameraComponent::onRotationChanged( const TransformationComponent & transform )
{
	m_view.setRotation( transform.getRotation() );
}

void nb::CameraComponent::init()
{
	auto transform = getEntity()->getComponent<TransformationComponent>();
	transform->s_positionChanged.connect_mem_fn_auto( &CameraComponent::onPositionChanged, *this );
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
