#pragma once
#include "stdafx.h"
#include "TextureManager.h"
#include "TileManager.h"
#include "ItemManager.h"
#include "EntityFactoryManager.h"

namespace nb
{
	class ResourceEngine : public CoreEngine
	{
	public:
		virtual void init( const CoreEngineManager& coreEngines )override;

		virtual bool update()override;

		PackageManager packages;
		TextureManager textures;
		TileManager tiles;
		ItemManager items;
		EntityFactoryManager entitiyFactories;

		static const std::string PATH_PACKAGES;
	};
}
