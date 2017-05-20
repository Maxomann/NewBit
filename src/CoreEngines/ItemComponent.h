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

		std::unique_ptr<Item> moveItem();

		bool isEmpty()const;
	};
}
