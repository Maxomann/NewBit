#pragma once
#include "stdafx.h"
#include "TextureManager.h"
#include "Item.h"

namespace nb
{
	class ItemManager
	{
		std::list<Item> items;

		void parseFile( const std::string& path,
						const TextureManager& textures );

	public:
		void init( const PackageManager& packages,
				   const TextureManager& textures );

		// The returned value is thread safe
		// It will not be modified after init() has been called
		const Item* getItem( Item::ID id )const;

		const std::list<Item>& getAllItems()const;
	};
}
