#include "TransformationComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

void nb::TransformationComponent::init( const Entity & entity )
{
}

void nb::TransformationComponent::destroy( const Entity & entity )
{
}

const sf::Vector2i& nb::TransformationComponent::getPosition() const
{
	return m_position;
}

const int& nb::TransformationComponent::getLayer() const
{
	return m_layer;
}

const sf::Vector2u& nb::TransformationComponent::getSize() const
{
	return m_size;
}

const float& nb::TransformationComponent::getRotation() const
{
	return m_rotation;
}

void nb::TransformationComponent::setPosition( sf::Vector2i position )
{
	m_position = position;
	s_positionChanged.call( *this );
}

void nb::TransformationComponent::move( sf::Vector2i offset )
{
	setPosition( Vector2i( m_position.x + offset.x, m_position.y + offset.y ) );
}

void nb::TransformationComponent::setLayer( int layer )
{
	m_layer = layer;
	s_layerChanged.call( *this );
}

void nb::TransformationComponent::setSize( sf::Vector2u size )
{
	m_size = size;
	s_sizeChanged.call( *this );
}

void nb::TransformationComponent::setRotation( float rotation )
{
	m_rotation = rotation;
	s_rotationChanged.call( *this );
}

void nb::TransformationComponent::rotate( float offset )
{
	setRotation( m_rotation + offset );
}
