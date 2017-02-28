#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"

namespace nb
{
	class SpriteComponent : public nb::Component
	{
		int m_zValue = 0;

		sf::Sprite m_sprite;

		void onPositionXYChanged( const TransformationComponent*const transform, sf::Vector2i oldPositionXY );
		void onSizeChanged( const TransformationComponent*const transform, sf::Vector2u oldSize );
		void onRotationChanged( const TransformationComponent*const transform, float oldRotation );
	public:

		DLL_EXPORT virtual void init()override;

		DLL_EXPORT virtual void destroy()override;

		int getZValue()const;
		void setZValue( int zValue );

		void setTexture( const sf::Texture& texture );

		const sf::Sprite& getSprite()const;
	};
}
