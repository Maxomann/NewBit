#pragma once
#include "stdafx.h"
#include "id.h"

namespace nb
{
	namespace tp
	{
		class TexturePacker
		{
		public:
			void addPackedTexture( PackedTextureId id );
			void getPackedTexture( const PackedTextureId& id )const;
		};
	}
}
