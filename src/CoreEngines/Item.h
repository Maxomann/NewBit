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
		Item( const std::string name,
			  const TextureReference* texture,
			  std::string useActionName,
			  bool isUsePossible = true );
		/* Item use IS NOT possible */
		Item( const std::string name,
			  const TextureReference* texture );
		Item( const Item& item ) = delete;
		Item( Item&& item ) = default;
		virtual ~Item() = default;

		const std::string& getName()const;

		const TextureReference* getTextureReference()const;

		bool canBeUsed()const;

		const std::string& getUseActionName()const;

		// return true if this item should be deleted after use
		virtual void use( World& world, Entity* entity ) = 0;
	};
}
