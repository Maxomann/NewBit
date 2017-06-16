#pragma once
#include "stdafx.h"
#include "EntityRenderer.h"

#include "TileMapComponent.h"

namespace nb
{
	class TileMapRenderer : public EntityRenderer
	{
		TransformationComponent* transform;
		TileMapComponent* tileMap;

		mutable std::mutex vertexArraysMutex;
		std::map<const sf::Texture*, std::vector<sf::Vertex>> vertexArrays;
		sf::FloatRect globalBounds;
		void calculateGlobalBounds();

		std::future<void> generationFuture;
		void generate( const TileMapComponent::TileData& data );
		void generate_internal( const TileMapComponent::TileData tiles );

	public:
		~TileMapRenderer();

		virtual void init( const Entity* entity ) override;

		virtual const sf::FloatRect& getGlobalBounds()const override;

		virtual void draw( sf::RenderTarget& target, sf::RenderStates states )const override;
	};
}
