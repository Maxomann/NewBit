#include "PositionTrackerComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::PositionTrackerComponent::onTrackedPositionChanged( const TransformationComponent * transform,
															 sf::Vector3i oldPosition )
{
	applyPositionWithOffset( transform->getPosition() );
}

void nb::PositionTrackerComponent::applyPositionWithOffset( const sf::Vector3i & positionWithoutOffset )
{
	Vector3i finalPosition;
	finalPosition.x = positionWithoutOffset.x + m_offset.x;
	finalPosition.y = positionWithoutOffset.y + m_offset.y;
	finalPosition.z = positionWithoutOffset.z;

	r_transformation->setPosition( finalPosition );
}

void nb::PositionTrackerComponent::init()
{
	r_transformation = getEntity()->getComponent<TransformationComponent>();
}

void nb::PositionTrackerComponent::destroy()
{
}

void nb::PositionTrackerComponent::trackEntity( nb::Entity * entity )
{
	m_connections.clear();
	if (entity)
	{
		r_track = entity->getComponent_try<TransformationComponent>();
		if (r_track)
		{
			applyPositionWithOffset( r_track->getPosition() );
			r_track->s_positionChanged.connect_track( m_connections,
													  this,
													  &PositionTrackerComponent::onTrackedPositionChanged );
		}
	}
	else
		r_track = nullptr;
}

void nb::PositionTrackerComponent::setOffsetXY( sf::Vector2i offset )
{
	m_offset = move( offset );
	if (r_track)
		applyPositionWithOffset( r_track->getPosition() );
}
