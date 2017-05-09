#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"

namespace nb
{
	class PositionTrackerComponent : public Component
	{
		TransformationComponent* r_transformation;

		TransformationComponent* r_track = nullptr;
		sf::Vector2f m_offset = {0,0};

		void onTrackedPositionChanged( const TransformationComponent* transform,
									   const Position& oldPosition );

		void applyPositionWithOffset( const Position& positionWithoutOffset );

		Connections m_connections;

	public:

		virtual void init()override;

		void trackEntity( Entity* entity );

		void setOffsetXY( sf::Vector2f offset );
	};
}
