#pragma once
#include "stdafx.h"

namespace nb
{
	class InitEngine : public CoreEngine
	{
	public:
		virtual void init( const CoreRefs& coreRefs ) override;

		virtual bool update( const CoreRefs& coreRefs ) override;

		virtual unsigned int getId()const override;
	};
}
