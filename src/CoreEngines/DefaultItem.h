#pragma once
#include "stdafx.h"
#include "Item.h"

namespace nb
{
	class DefaultItem : public Item
	{
	public:
		DefaultItem( std::string name,
					 const TextureReference* texture );

		virtual bool use( World& world, Entity* entity )override;
	};
}
