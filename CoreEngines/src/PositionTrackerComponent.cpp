#include "PositionTrackerComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::PositionTrackerComponent::onTrackedPositionChanged( const TransformationComponent * transform,
															 sf::Vector3i oldPosition )
{
	r_transformation->setPosition( transform->getPosition() );
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
	auto track = entity->getComponent_try<TransformationComponent>();

	if (track)
	{
		r_transformation->setPosition( track->getPosition() );
		track->s_positionChanged.connect_track( m_connections,
												this,
												&PositionTrackerComponent::onTrackedPositionChanged );
	}
}
