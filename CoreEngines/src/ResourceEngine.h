#pragma once
#include "stdafx.h"

namespace nb
{
	class ResourceEngine : public CoreEngine
	{
	public:
		virtual void init( const CoreRef& coreRefs )override;

		virtual bool update( const CoreRef& coreRefs )override;

		PackageManager packages;

		static const std::string PATH_PACKAGES;
	};
}
