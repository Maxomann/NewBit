#include "PhysicsDebugDraw.h"
using namespace std;
using namespace sf;
using namespace nb;

void PhysicsDebugDraw::setDrawContainer( std::vector<std::unique_ptr<sf::Drawable>>& debugDrawContainer )
{
	this->debugDrawContainer = &debugDrawContainer;
}

void PhysicsDebugDraw::DrawPolygon( const b2Vec2* vertices,
									int32 vertexCount,
									const b2Color& color )
{
	auto el = make_unique<sf::ConvexShape>();
	el->setPointCount( vertexCount );
	el->setFillColor( Color( color.r*255.f, color.g*255.f, color.b*255.f, color.a*255.f ) );

	for (int i = 0; i < vertexCount; ++i)
	{
		el->setPoint( i, Vector2f( vertices->x*METER_TO_PIXEL, vertices->y*METER_TO_PIXEL ) );
		vertices++;
	}

	debugDrawContainer->push_back( move( el ) );
}

void PhysicsDebugDraw::DrawSolidPolygon( const b2Vec2* vertices,
										 int32 vertexCount,
										 const b2Color& color )
{
	auto el = make_unique<sf::ConvexShape>();
	el->setPointCount( vertexCount );
	el->setFillColor( Color( color.r*255.f, color.g*255.f, color.b*255.f, color.a*255.f ) );

	for (int i = 0; i < vertexCount; ++i)
	{
		el->setPoint( i, Vector2f( vertices->x*METER_TO_PIXEL, vertices->y*METER_TO_PIXEL ) );
		vertices++;
	}

	debugDrawContainer->push_back( move( el ) );
}

void PhysicsDebugDraw::DrawCircle( const b2Vec2& center,
								   float32 radius,
								   const b2Color& color )
{
	auto el = make_unique<sf::CircleShape>();
	el->setRadius( radius*METER_TO_PIXEL );
	el->setPosition( Vector2f( (center.x + radius)*METER_TO_PIXEL, (center.y + radius)*METER_TO_PIXEL ) );
	el->setFillColor( Color( color.r*255.f, color.g*255.f, color.b*255.f, color.a*255.f ) );
	debugDrawContainer->push_back( move( el ) );
}

void PhysicsDebugDraw::DrawSolidCircle( const b2Vec2& center,
										float32 radius,
										const b2Vec2& axis,
										const b2Color& color )
{
	auto el = make_unique<sf::CircleShape>();
	el->setRadius( radius*METER_TO_PIXEL );
	el->setPosition( Vector2f( (center.x + radius)*METER_TO_PIXEL, (center.y + radius)*METER_TO_PIXEL ) );
	el->setFillColor( Color( color.r*255.f, color.g*255.f, color.b*255.f, color.a*255.f ) );
	debugDrawContainer->push_back( move( el ) );
}

void PhysicsDebugDraw::DrawSegment( const b2Vec2& p1,
									const b2Vec2& p2,
									const b2Color& color )
{
	auto el = make_unique<sf::VertexArray>( sf::Lines, 2 );
	(*el)[0] = Vertex( Vector2f( p1.x*METER_TO_PIXEL, p1.y*METER_TO_PIXEL ),
					   Color( color.r*255.f, color.g*255.f, color.b*255.f, color.a*255.f ) );
	(*el)[1] = Vertex( Vector2f( p2.x*METER_TO_PIXEL, p2.y*METER_TO_PIXEL ),
					   Color( color.r*255.f, color.g*255.f, color.b*255.f, color.a*255.f ) );
	debugDrawContainer->push_back( move( el ) );
}

void PhysicsDebugDraw::DrawTransform( const b2Transform& xf )
{
	b2Vec2 p1 = xf.p, p2;
	const float32 k_axisScale = 0.4f;

	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	DrawSegment( p1, p2, b2Color( 1, 0, 0 ) );

	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	DrawSegment( p1, p2, b2Color( 0, 1, 0 ) );
}

void PhysicsDebugDraw::DrawPoint( const b2Vec2& p,
								  float32 size,
								  const b2Color& color )
{
	auto el = make_unique<sf::CircleShape>();
	el->setRadius( (size / 2.f)*METER_TO_PIXEL );
	el->setPosition( Vector2f(
		(p.x + (size / 2.f))*METER_TO_PIXEL,
		(p.y + (size / 2.f))*METER_TO_PIXEL ) );
	el->setFillColor( Color( color.r*255.f, color.g*255.f, color.b*255.f, color.a*255.f ) );
	debugDrawContainer->push_back( move( el ) );
}
