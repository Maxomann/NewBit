#include "stdafx.h"
#include "id.h"

namespace nb
{
	namespace tp
	{
		namespace exception
		{
			class PackedTextureDuplicateException : public std::logic_error
			{
				const std::vector<TextureId> m_textureIds;

			public:
				PackedTextureDuplicateException( std::vector<TextureId> duplicateIds );

				static std::string generateErrorMessage( std::vector<TextureId> duplicateIds );
			};
		}
	}
}