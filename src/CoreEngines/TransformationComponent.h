#pragma once
#include "stdafx.h"
#include "Position.h"

namespace nb
{
	class TransformationComponent : public Component
	{
	private:

		Position position;
		sf::Vector2f size = {0.f, 0.f};
		float rotation = 0.f;

	public:
		TransformationComponent( sf::Vector2f positionXY,
								 int layer,
								 sf::Vector2f size,
								 float rotation = 0 );

		virtual void init()override;

		//

		Position getPosition()const;
		const sf::Vector2f& getPositionXY()const;

		int getLayer()const;

		sf::Vector2f getSize()const;

		float getRotation()const;

		//

		void setPosition( Position newPosition );
		void setPositionXY( sf::Vector2f newPosition );
		void setPositionXY( sf::Vector2i newPosition );
		void moveXY( sf::Vector2f offset );
		void moveXY( sf::Vector2i offset );

		void setLayer( int layer );
		void moveLayer( int offset );

		void setSize( sf::Vector2f newSize );
		void scale( float factor );

		void setRotation( float newRotation );
		void rotate( float offset );

		//

		// Second parameter is old value
		Signal<void( const TransformationComponent* const, const Position& )> s_positionChanged;
		// Second parameter is old value
		Signal<void( const TransformationComponent* const, sf::Vector2f )> s_positionXYChanged;
		// Second parameter is old value
		Signal<void( const TransformationComponent* const, int )> s_layerChanged;
		// Second parameter is old value
		Signal<void( const TransformationComponent* const, sf::Vector2f )> s_sizeChanged;
		// Second parameter is old value
		Signal<void( const TransformationComponent* const, float )> s_rotationChanged;
	};
}
