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

		virtual void init( const Entity& entity )override;

		virtual void destroy( const Entity& entity )override;

		const sf::Vector2i& getPosition()const;
		const int& getLayer()const;
		const sf::Vector2u& getSize()const;
		const float& getRotation()const;

		void setPosition( sf::Vector2i position );
		void setLayer( int layer );
		void setSize( sf::Vector2u size );
		void setRotation( float rotation );

		Signal<void, const TransformationComponent&> s_positionChanged;
		Signal<void, const TransformationComponent&> s_layerChanged;
		Signal<void, const TransformationComponent&> s_sizeChanged;
		Signal<void, const TransformationComponent&> s_rotationChanged;
	};
}
