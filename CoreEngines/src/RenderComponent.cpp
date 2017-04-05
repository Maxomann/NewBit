#include "RenderComponent.h"
using namespace std;
using namespace sf;
using namespace nb;

nb::RenderComponent::RenderComponent( int zValue )
	: m_zValue( zValue )
{
}

void RenderComponent::init()
{
	transformComponent = component<TransformationComponent>();

	return;
};

void RenderComponent::destroy()
{
	return;
};

const sf::Vector2i& nb::RenderComponent::getSortPositionXY() const
{
	return transformComponent->getPositionXY();
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

void RenderComponent::addDrawable( const sf::Drawable* drawable, const sf::FloatRect* globalBoundsPtr )
{
	m_drawables.push_back( drawable );
	globalBounds[drawable] = globalBoundsPtr;
};

void RenderComponent::removeDrawable( const sf::Drawable* drawable )
{
#ifdef _DEBUG
	m_drawables.erase( std::remove( m_drawables.begin(), m_drawables.end(), drawable ) );
#else
	m_drawables.erase( std::remove( m_drawables.begin(), m_drawables.end(), drawable ), m_drawables.end() );
#endif
};

const sf::FloatRect& nb::RenderComponent::getGlobalBounds() const
{
	// This should be replaced with a more sensible algorithm, but it works for now
	// If clipping issues occur, this might be the cause :D

	const sf::FloatRect* biggestRect = nullptr;
	for (const auto& el : globalBounds)
	{
		if (biggestRect == nullptr)
			biggestRect = el.second;
		else
		{
			auto areaA = el.second->width*el.second->height;
			auto areaB = biggestRect->width*biggestRect->height;
			if (areaA > areaB)
				biggestRect = el.second;
		}
	}

	if (biggestRect == nullptr)
		return defaultRect;
	else
		return *biggestRect;
}

const std::vector<const sf::Drawable*>& RenderComponent::getDrawingData()const
{
	return m_drawables;
};
