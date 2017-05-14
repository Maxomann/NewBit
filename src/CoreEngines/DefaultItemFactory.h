#pragma once
#include "stdafx.h"
#include "ItemFactory.h"
#include "DefaultItem.h"

namespace nb
{
	class DefaultItemFactory : public ItemFactory
	{
		const TextureReference* texture;

	public:
		DefaultItemFactory( ID id,
							NAME name,
							LABELS labels,
							const TextureReference* texture );

		virtual std::unique_ptr<Item> create()const override;
	};
}
