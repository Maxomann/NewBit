#pragma once
#include "stdafx.h"
#include "TextureReference.h"
#include "id.h"

namespace nb
{
	class TextureManager
	{
		std::list<sf::Texture> m_textureCache;
		std::map<std::string, TextureReference> m_textureReferencesByGlobalId;

	public:

		void init( PackageManager& packages );

		const TextureReference* getTextureReference( const GlobalId& globalId )const;

		static const std::vector<std::string> AUTO_CACHE_ID_COMPONENTS;
		static const std::string META_ATTR_TYPE_VALUE_TEXTURE;
	};
}
