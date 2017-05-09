#include "PositionTrackerComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::PositionTrackerComponent::onTrackedPositionChanged( const TransformationComponent * transform,
															 const Position& oldPosition )
{
	applyPositionWithOffset( transform->getPosition() );
}

void nb::PositionTrackerComponent::applyPositionWithOffset( const Position& positionWithoutOffset )
{
	Position finalPosition;
	finalPosition.xy.x = positionWithoutOffset.xy.x + m_offset.x;
	finalPosition.xy.y = positionWithoutOffset.xy.y + m_offset.y;
	finalPosition.layer = positionWithoutOffset.layer;

	r_transformation->setPosition( finalPosition );
}

void nb::PositionTrackerComponent::init()
{
	r_transformation = getEntity()->getComponent<TransformationComponent>();
}

void nb::PositionTrackerComponent::trackEntity( nb::Entity * entity )
{
	m_connections.clear();
	if( entity )
	{
		r_track = entity->getComponent_try<TransformationComponent>();
		if( r_track )
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

void nb::PositionTrackerComponent::setOffsetXY( sf::Vector2f offset )
{
	m_offset = move( offset );
	if( r_track )
		applyPositionWithOffset( r_track->getPosition() );
}
