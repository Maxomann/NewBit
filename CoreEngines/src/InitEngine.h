#pragma once
#include "stdafx.h"

namespace nb
{
	class InitEngine : public CoreEngine
	{
	public:
		virtual void init( const CoreRef& coreRefs ) override;

		virtual bool update( const CoreRef& coreRefs ) override;
	};
}
