#include "RenderComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::RenderComponent::RenderComponent( int zValue )
	: m_zValue( zValue )
{}

nb::RenderComponent::RenderComponent( std::vector<std::unique_ptr<EntityRenderer>> renderers,
									  int zValue )
{
	for( auto& el : renderers )
		addRenderer( move( el ) );
}

void RenderComponent::init()
{
	isInit = true;
	transformComponent = component<TransformationComponent>();

	for( auto& el : renderers )
		el->init( entity() );

	return;
};

sf::Vector2i nb::RenderComponent::getSortPositionXY() const
{
	return Vector2i( transformComponent->getPositionXY() );
}

const int nb::RenderComponent::getDrawingLayer() const
{
	return transformComponent->getLayer();
}

const int& nb::RenderComponent::getZValue() const
{
	return m_zValue;
}

void nb::RenderComponent::setZValue( int zValue )
{
	m_zValue = move( zValue );
}

void nb::RenderComponent::addRenderer( std::unique_ptr<EntityRenderer> renderer )
{
	if( isInit )
		renderer->init( entity() );
	renderers.push_back( move( renderer ) );
	drawables.push_back( renderers.back().get() );
}

const sf::FloatRect& nb::RenderComponent::getGlobalBounds() const
{
	// This should be replaced with a more sensible algorithm, but it works for now
	// If clipping issues occur, this might be the cause :D

	const sf::FloatRect* biggestRect = &defaultRect;
	for( const auto& el : renderers )
	{
		const auto& thisRect = el->getGlobalBounds();

		auto areaA = thisRect.width * thisRect.height;
		auto areaB = biggestRect->width * biggestRect->height;
		if( areaA > areaB )
			biggestRect = &thisRect;
	}

	return *biggestRect;
}

const std::vector<const sf::Drawable*>& RenderComponent::getDrawingData()const
{
	return drawables;
};
