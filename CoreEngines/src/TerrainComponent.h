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

		void setSize( sf::Vector2u size );
	public:
		TerrainComponent( const TextureReference& debugTexture );

		virtual void init() override;
		virtual void destroy() override;

		void setDebugTexture( const TextureReference& texture );

		static const int TILE_SIZE_IN_PIXEL;
	};
}
