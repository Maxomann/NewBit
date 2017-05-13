#pragma once
#include "stdafx.h"
#include "ItemFactory.h"
#include "DefaultItem.h"

namespace nb
{
	class DefaultItemFactory : public ItemFactory
	{
		GlobalId textureId;

	public:
		DefaultItemFactory( ID id,
							NAME name,
							LABELS labels,
							GlobalId textureId );

		virtual std::unique_ptr<Item> create( const ResourceEngine& resources )const override;
	};
}
