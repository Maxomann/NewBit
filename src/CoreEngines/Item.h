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
		const ID id;

		const TextureReference*const texref;

		const std::string name;

	public:
		Item( ID id,
			  std::string name,
			  const TextureReference* texture );
		Item( const Item& item ) = delete;
		Item( Item&& item ) = default;

		ID getId()const;
		const std::string& getName()const;

		const TextureReference* getTextureReference()const;
	};
}
