#pragma once
#include "stdafx.h"
#include "Item.h"

namespace nb
{
	class Inventory
	{
	public:
		using ContainerType = std::vector<std::unique_ptr<Item>>;

	private:
		ContainerType items;

	public:
		void addItem( std::unique_ptr<Item> item );

		const ContainerType& getContent()const;

		Signal<void( const Inventory& )> s_contentChange;
	};
}
