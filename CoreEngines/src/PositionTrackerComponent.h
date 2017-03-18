#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"

namespace nb
{
	class PositionTrackerComponent : public Component
	{
		TransformationComponent* r_transformation;

		TransformationComponent* r_track = nullptr;
		sf::Vector2i m_offset;

		void onTrackedPositionChanged( const TransformationComponent* transform,
									   sf::Vector3i oldPosition );

		void applyPositionWithOffset( const sf::Vector3i& positionWithoutOffset );

		Connections m_connections;

	public:
		virtual void init()override;

		virtual void destroy()override;

		void trackEntity( Entity* entity );

		void setOffsetXY( sf::Vector2i offset );
	};
}
