#pragma once
#include "stdafx.h"

namespace nb
{
	class PackageEngine : public CoreEngine
	{
	public:
		virtual void init(const CoreRefs& coreRefs)override;

		virtual bool update(const CoreRefs& coreRefs)override;
	};
}
