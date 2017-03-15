#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"

namespace nb
{
	class PositionTrackerComponent : public Component
	{
		TransformationComponent* r_transformation;

		void onTrackedPositionChanged( const TransformationComponent* transform,
									   sf::Vector3i oldPosition );

		Connections m_connections;

	public:
		virtual void init()override;

		virtual void destroy()override;

		void trackEntity( Entity* entity );
	};
}
