#pragma once
#include "stdafx.h"
#include "TextureReference.h"

namespace nb
{
	class Tile
	{
	public:
		using ID = unsigned int;

	private:
		const TextureReference*const texref;

		const ID id;

	public:

		Tile( ID tileId, const TextureReference* texture );
		Tile( const Tile& ) = delete;//no copy
		Tile( Tile&& ) = default;

		ID getId()const;

		const TextureReference* getTextureReference()const;
	};
}
