#pragma once
#include "stdafx.h"

namespace nb
{
	class CoreEngine
	{
	public:
		DLL_EXPORT virtual ~CoreEngine() = default;

		DLL_EXPORT virtual void init() = 0;

		// return false to terminate process
		DLL_EXPORT virtual bool update() = 0;

		DLL_EXPORT virtual unsigned int getId()const = 0;
	};
}