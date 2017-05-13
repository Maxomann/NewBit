#pragma once
#include "stdafx.h"
#include "TextureReference.h"

namespace nb
{
	class Item
	{
	public:
		using ID = unsigned int;

	private:
		const TextureReference*const texref;

		const std::string name;

		bool usePossible;

		std::string useActionName;

	public:
		Item( std::string name,
			  const TextureReference* texture,
			  bool usePossible,
			  std::string useActionName );
		Item( const Item& item ) = delete;
		Item( Item&& item ) = default;
		virtual ~Item() = default;

		const std::string& getName()const;

		const TextureReference* getTextureReference()const;

		bool canBeUsed()const;

		const std::string& getUseActionName()const;

		// return true if this item should be deleted after use
		virtual bool use( World& world, Entity* entity ) = 0;
	};
}
