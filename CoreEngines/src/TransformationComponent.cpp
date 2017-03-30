#include "TransformationComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::TransformationComponent::TransformationComponent( sf::Vector2i position,
													  int layer,
													  sf::Vector2u size,
													  float rotation )
	: m_position( position ),
	m_layer( layer ),
	m_size( size ),
	m_rotation( rotation )
{
}

void nb::TransformationComponent::init()
{
}

void nb::TransformationComponent::destroy()
{
}

sf::Vector3i nb::TransformationComponent::getPosition() const
{
	return Vector3i( m_position.x,
					 m_position.y,
					 m_layer );
}

sf::Vector2i nb::TransformationComponent::getPositionXY() const
{
	return m_position;
}

int nb::TransformationComponent::getLayer() const
{
	return m_layer;
}

sf::Vector2u nb::TransformationComponent::getSize() const
{
	return m_size;
}

float nb::TransformationComponent::getRotation() const
{
	return m_rotation;
}

void nb::TransformationComponent::setPosition( sf::Vector3i position )
{
	auto oldPosition = getPosition();
	auto oldPositionXY = getPositionXY();
	auto oldLayer = m_layer;

	m_position = Vector2i( position.x, position.y );
	m_layer = position.z;

	if (oldPosition != position)
	{
		s_positionChanged.call( this, oldPosition );
		if (oldPositionXY != Vector2i( position.x, position.y ))
			s_positionXYChanged.call( this, oldPositionXY );
		if (oldLayer != position.z)
			s_layerChanged.call( this, oldLayer );
	}
}

void nb::TransformationComponent::setPositionXY( sf::Vector2i position )
{
	auto oldPosition = getPosition();
	auto oldPositionXY = getPositionXY();

	m_position = position;

	if (oldPositionXY != Vector2i( position.x, position.y ))
	{
		s_positionChanged.call( this, oldPosition );
		s_positionXYChanged.call( this, oldPositionXY );
	}
}

void nb::TransformationComponent::moveXY( sf::Vector2i offset )
{
	setPositionXY( Vector2i( m_position.x + offset.x, m_position.y + offset.y ) );
}

void nb::TransformationComponent::setLayer( int layer )
{
	auto oldPosition = getPosition();
	auto oldLayer = m_layer;

	m_layer = layer;

	if (oldLayer != layer)
	{
		s_positionChanged.call( this, oldPosition );
		s_layerChanged.call( this, oldLayer );
	}
}

void nb::TransformationComponent::moveLayer( int offset )
{
	setLayer( m_layer + offset );
}

void nb::TransformationComponent::setSize( sf::Vector2u size )
{
	auto oldSize = m_size;

	m_size = size;

	if (oldSize != size)
		s_sizeChanged.call( this, oldSize );
}

void nb::TransformationComponent::scale( float factor )
{
	setSize( Vector2u( ((float)m_size.x)*factor, ((float)m_size.y)*factor ) );
}

void nb::TransformationComponent::setRotation( float rotation )
{
	auto oldRotation = m_rotation;

	m_rotation = rotation;

	if (oldRotation != rotation)
		s_rotationChanged.call( this, oldRotation );
}

void nb::TransformationComponent::rotate( float offset )
{
	setRotation( m_rotation + offset );
}
