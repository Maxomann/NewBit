#include "stdafx.h"
#include "id.h"

namespace nb
{
	namespace tp
	{
		namespace exception
		{
			class TextureTooLargeException : public std::logic_error
			{
			public:
				TextureTooLargeException( TextureId textureId );
			};
		}
	}
}