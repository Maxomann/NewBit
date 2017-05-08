#pragma once
#include "stdafx.h"
#include "id.h"

namespace nb
{
	namespace tp
	{
		namespace exception
		{
			class PackedTextureGenerationStateException : public std::runtime_error
			{
			public:
				PackedTextureGenerationStateException( bool state );
			};
		}
	}
}