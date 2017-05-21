#include "TransformationComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::TransformationComponent::TransformationComponent( sf::Vector2f positionXY,
													  int layer,
													  sf::Vector2f size,
													  float rotation )
	: position( move( positionXY ), layer ),
	size( size ),
	rotation( rotation )
{}

void nb::TransformationComponent::init()
{}

nb::Position nb::TransformationComponent::getPosition() const
{
	return position;
}

const sf::Vector2f& nb::TransformationComponent::getPositionXY() const
{
	return position.xy;
}

int nb::TransformationComponent::getLayer() const
{
	return position.layer;
}

sf::Vector2f nb::TransformationComponent::getSize() const
{
	return size;
}

float nb::TransformationComponent::getRotation() const
{
	return rotation;
}

void nb::TransformationComponent::setPosition( Position newPosition )
{
	auto oldPosition = getPosition();
	auto oldPositionXY = getPositionXY();
	auto oldLayer = getLayer();

	this->position = move( newPosition );

	if( oldPosition != getPosition() )
	{
		s_positionChanged.call( this, oldPosition );
		if( oldPositionXY != getPositionXY() )
			s_positionXYChanged.call( this, oldPositionXY );
		if( oldLayer != getLayer() )
			s_layerChanged.call( this, oldLayer );
	}
}

void nb::TransformationComponent::setPositionXY( sf::Vector2f newPosition )
{
	auto oldPosition = getPosition();
	auto oldPositionXY = getPositionXY();

	this->position.xy = move( newPosition );

	if( oldPositionXY != getPositionXY() )
	{
		s_positionChanged.call( this, oldPosition );
		s_positionXYChanged.call( this, oldPositionXY );
	}
}

void nb::TransformationComponent::setPositionXY( sf::Vector2i newPosition )
{
	setPositionXY( sf::Vector2f( newPosition ) );
}

void nb::TransformationComponent::moveXY( sf::Vector2f offset )
{
	setPositionXY( Vector2f( position.xy.x + offset.x,
							 position.xy.y + offset.y ) );
}

void nb::TransformationComponent::moveXY( sf::Vector2i offset )
{
	moveXY( sf::Vector2f( offset ) );
}

void nb::TransformationComponent::setLayer( int layer )
{
	auto oldPosition = getPosition();
	auto oldLayer = getLayer();

	this->position.layer = layer;

	if( oldLayer != getLayer() )
	{
		s_positionChanged.call( this, oldPosition );
		s_layerChanged.call( this, oldLayer );
	}
}

void nb::TransformationComponent::moveLayer( int offset )
{
	setLayer( getLayer() + offset );
}

void nb::TransformationComponent::setSize( sf::Vector2f newSize )
{
	auto oldSize = getSize();

	this->size = newSize;

	if( oldSize != getSize() )
		s_sizeChanged.call( this, oldSize );
}

void nb::TransformationComponent::scale( float factor )
{
	auto newSize = Vector2f(
		size.x*factor,
		size.y*factor );
	setSize( newSize );
}

void nb::TransformationComponent::setRotation( float newRotation )
{
	auto oldRotation = getRotation();

	this->rotation = newRotation;

	if( oldRotation != getRotation() )
		s_rotationChanged.call( this, oldRotation );
}

void nb::TransformationComponent::rotate( float offset )
{
	setRotation( rotation + offset );
}
