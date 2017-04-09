#pragma once
#include "stdafx.h"
#include "Item.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"

namespace nb
{
	class ItemComponent : public Component
	{
		SpriteComponent* r_spriteComponent;
		PhysicsComponent* r_physicsComponent;

		const Item* item;

	public:
		ItemComponent( const Item* item );

		virtual void init() override;
		virtual void destroy() override;
	};
}
