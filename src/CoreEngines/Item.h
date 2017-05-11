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

	public:
		Item( std::string name,
			  const TextureReference* texture );
		Item( const Item& item ) = delete;
		Item( Item&& item ) = default;
		virtual ~Item() = default;

		const std::string& getName()const;

		const TextureReference* getTextureReference()const;

		virtual void use( Entity* entity ) = 0;
	};
}
