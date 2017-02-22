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

		void setPosition( sf::Vector2i position );
		void move( sf::Vector2i offset );

		void setLayer( int layer );

		void setSize( sf::Vector2u size );
		void scale( float factor );

		void setRotation( float rotation );
		void rotate( float offset );

		//

		Signal<void, const TransformationComponent&> s_positionChanged;
		Signal<void, const TransformationComponent&> s_layerChanged;
		Signal<void, const TransformationComponent&> s_sizeChanged;
		Signal<void, const TransformationComponent&> s_rotationChanged;
	};
}
