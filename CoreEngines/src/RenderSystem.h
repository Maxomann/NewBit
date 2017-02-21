#pragma once
#include "stdafx.h"
#include "SpriteComponent.h"

namespace nb
{
	class RenderSystem : public System
	{
		std::vector<SpriteComponent*> m_spriteComponentsToDraw;

		void onEntityAdded( Entity* entity );
		void onEntitiesRemoved( const std::vector<Entity*>& entities );
	public:

		virtual void init( World& world ) override;
		virtual void update( World& world ) override;
		virtual void destroy( World& world ) override;

		const std::vector<SpriteComponent*>& getSpriteComponentsToDraw()const;
	};
}
