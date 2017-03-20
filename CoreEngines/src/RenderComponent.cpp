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
	return;
};

void RenderComponent::destroy()
{
	return;
};

int nb::RenderComponent::getZValue() const
{
	return m_zValue;
}

void nb::RenderComponent::setZValue( int zValue )
{
	m_zValue = move( zValue );
}

void RenderComponent::addDrawable( const sf::Drawable* drawable )
{
	m_drawables.push_back( drawable );
};

void RenderComponent::removeDrawable( const sf::Drawable* drawable )
{
#ifdef _DEBUG
	m_drawables.erase( std::remove( m_drawables.begin(), m_drawables.end(), drawable ) );
#else
	m_drawables.erase( std::remove( m_drawables.begin(), m_drawables.end(), drawable ), m_drawables.end() );
#endif
};

const std::vector<const sf::Drawable*>& RenderComponent::getDrawingData()const
{
	return m_drawables;
};
