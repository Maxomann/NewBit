#pragma once
#include "stdafx.h"

namespace nb
{
	class TransformationComponent : public Component
	{
		sf::Vector2i m_position;
		int m_layer = 0;
		sf::Vector2u m_size;
		float m_rotation;

	public:

		virtual void init()override;

		virtual void destroy()override;

		//

		sf::Vector3i getPosition()const;
		sf::Vector2i getPositionXY()const;

		int getLayer()const;

		sf::Vector2u getSize()const;

		float getRotation()const;

		//

		void setPosition( sf::Vector3i position );
		void setPositionXY( sf::Vector2i position );
		void moveXY( sf::Vector2i offset );

		void setLayer( int layer );
		void moveLayer( int offset );

		void setSize( sf::Vector2u size );
		void scale( float factor );

		void setRotation( float rotation );
		void rotate( float offset );

		//

		// Second parameter is old value
		Signal<void( const TransformationComponent* const, sf::Vector3i )> s_positionChanged;
		// Second parameter is old value
		Signal<void( const TransformationComponent* const, sf::Vector2i )> s_positionXYChanged;
		// Second parameter is old value
		Signal<void( const TransformationComponent* const, int )> s_layerChanged;
		// Second parameter is old value
		Signal<void( const TransformationComponent* const, sf::Vector2u )> s_sizeChanged;
		// Second parameter is old value
		Signal<void( const TransformationComponent* const, float )> s_rotationChanged;
	};
}
