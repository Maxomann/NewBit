#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"

namespace nb
{
	class CameraComponent : public Component
	{
		sf::View m_view;

		void onPositionXYChanged( const TransformationComponent*const transform, sf::Vector2i oldPositionXY );
		void onSizeChanged( const TransformationComponent*const transform, sf::Vector2u oldSize );
		void onRotationChanged( const TransformationComponent*const transform, float oldRotation );
	public:
		const sf::View& getView()const;

		virtual void init() override;
		virtual void destroy() override;
	};
}
