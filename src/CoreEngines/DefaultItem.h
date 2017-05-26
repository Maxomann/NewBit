#pragma once
#include "stdafx.h"
#include "Item.h"

namespace nb
{
	class DefaultItem : public Item
	{
	public:
		DefaultItem( const std::string name,
					 const TextureReference* texture );

		virtual void use( World& world, Entity* entity )override;
	};
}
