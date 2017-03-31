#pragma once
#include "stdafx.h"
#include "TextureManager.h"
#include "TileManager.h"

namespace nb
{
	class ResourceEngine : public CoreEngine
	{
	public:
		virtual void init()override;

		virtual bool update()override;

		PackageManager packages;
		TextureManager textures;
		TileManager tiles;

		static const std::string PATH_PACKAGES;
	};
}
