#pragma once
#include "stdafx.h"

namespace nb
{
	namespace exception
	{
		class ComponentDoesNotExistException : public std::runtime_error
		{
		public:
			DLL_EXPORT ComponentDoesNotExistException( const std::string& componentTypeName );
		};
	}
}
