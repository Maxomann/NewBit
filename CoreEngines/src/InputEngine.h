#pragma once
#include "stdafx.h"
#include "id.h"

namespace nb
{
	class InputEngine : public CoreEngine
	{
	public:
		virtual void init( const CoreRefs& coreRefs ) override;

		virtual bool update( const CoreRefs& coreRefs ) override;

		virtual unsigned int getId()const override;
	};
}
