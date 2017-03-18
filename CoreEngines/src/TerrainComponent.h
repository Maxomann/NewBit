#pragma once
#include "stdafx.h"
#include "TransformationComponent.h"
#include "RenderComponent.h"
#include "TextureReference.h"

namespace nb
{
	class TerrainComponent : public Component
	{
		sf::Sprite m_debugSprite;

		void onPositionXYChanged( const TransformationComponent*const transform,
								  sf::Vector2i oldPositionXY );
		void onSizeChanged( const TransformationComponent*const transform,
							sf::Vector2u oldSize );
		void onRotationChanged( const TransformationComponent*const transform,
								float oldRotation );
	public:
		virtual void init() override;
		virtual void destroy() override;

		void setDebugTexture( const TextureReference& texture );

		static const int TILE_SIZE_IN_PIXEL;
	};
}
