#include "PositionTrackerComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::PositionTrackerComponent::onTrackedPositionChanged( const TransformationComponent * transform,
															 sf::Vector3i oldPosition )
{
	r_transformation->setPosition( transform->getPosition() );
}

void nb::PositionTrackerComponent::trackEntity( nb::Entity * entity )
{
	auto track = entity->getComponent_try<TransformationComponent>();

	if (track)
	{
		track->s_positionChanged.connect_mem_fn_auto_track( &PositionTrackerComponent::onTrackedPositionChanged, *this );
	}
}
