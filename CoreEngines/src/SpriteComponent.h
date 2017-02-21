#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"

namespace nb
{
	class SpriteComponent : public nb::Component
	{
		int m_zValue = 0;

		sf::Sprite m_sprite;

		void onPositionChanged( const TransformationComponent& transform );
		void onSizeChanged( const TransformationComponent& transform );
		void onRotationChanged( const TransformationComponent& transform );
	public:

		DLL_EXPORT virtual void init( const Entity& entity )override;

		DLL_EXPORT virtual void destroy( const Entity& entity )override;

		int getZValue()const;
		void setZValue( int zValue );

		void setTexture( const sf::Texture& texture );

		const sf::Sprite& getSprite()const;
	};
}
