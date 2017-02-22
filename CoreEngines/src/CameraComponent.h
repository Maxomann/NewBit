#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"

namespace nb
{
	class CameraComponent : public Component
	{
		sf::View m_view;

		void onPositionChanged( const TransformationComponent& transform );
		void onSizeChanged( const TransformationComponent& transform );
		void onRotationChanged( const TransformationComponent& transform );
	public:
		const sf::View& getView()const;

		virtual void init() override;
		virtual void destroy() override;
	};
}
