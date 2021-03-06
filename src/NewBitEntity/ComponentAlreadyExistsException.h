#pragma once
#include "stdafx.h"

namespace nb
{
	namespace exception
	{
		class ComponentAlreadyExistsException : public std::runtime_error
		{
		public:
			DLL_EXPORT ComponentAlreadyExistsException( const std::string& componentTypeName );
		};
	}
}
