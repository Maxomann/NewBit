#pragma once
#include "stdafx.h"
#include "TextureManager.h"

namespace nb
{
	class ResourceEngine : public CoreEngine
	{
	public:
		virtual void init()override;

		virtual bool update()override;

		PackageManager packages;

		static const std::string PATH_PACKAGES;
	};
}
