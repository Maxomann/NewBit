#pragma once
#include "stdafx.h"
#include "Item.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"

namespace nb
{
	class ItemComponent : public Component
	{
		std::unique_ptr<Item> item;

	public:
		ItemComponent( std::unique_ptr<Item> item );

		virtual void init() override;

		const std::unique_ptr<Item>& getItem()const;

		// this component is in an invalid state after calling moveItem()
		// it should no longer be used and deleted imediately
		std::unique_ptr<Item> moveItem();
	};
}
