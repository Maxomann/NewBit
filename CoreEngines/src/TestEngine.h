#pragma once
#include "TestGameState.h"
#include "id.h"

namespace nb
{
	class TestEngine : public nb::CoreEngine
	{
	public:
		DLL_EXPORT TestEngine();

		DLL_EXPORT virtual void init( const CoreRefs& coreRefs )override;

		DLL_EXPORT virtual bool update( const CoreRefs& coreRefs )override;

		DLL_EXPORT virtual unsigned int getId()const override;
	};
}
