#pragma once
#include "stdafx.h"
#include "TextureReference.h"
#include "PackedTextureGenerationStateException.h"
#include "PackedTextureDuplicateException.h"
#include "TextureTooLargeException.h"

namespace nb
{
	namespace tp
	{
		struct PackingElement
		{
			TextureId id;
			sf::Texture* texture;
			sf::IntRect rect;
			unsigned int destinationTextureId;

			bool operator== (const PackingElement& rhs)const
			{
				return this->id == rhs.id;
			};
			bool operator!= (const PackingElement& rhs)const
			{
				return this->id != rhs.id;
			};
		};

		struct Node
		{
			std::array<Node*, 2> child;
			sf::IntRect rect;
			PackingElement* ptr = nullptr;

			bool insert(std::list<Node>& storeNodesHere, PackingElement* el);
		};

		class PackedTexture
		{
			PackedTextureId m_id;

			bool m_isGenerated = false;

			std::vector<std::pair<TextureId, sf::Texture>> m_subTextures;

			const unsigned int m_maximumSize = 0;
			std::unordered_map<TextureId, TextureReference> m_generatedTextureReferences;
			std::deque<sf::RenderTexture> m_generatedTextures;

			void m_throwIfGenerated();
			void m_throwIfNotGenerated();

			static unsigned int constructMaximumSize(unsigned int maximumSize, bool useRecommendedMaxSize);

		public:
			DLL_EXPORT PackedTexture(PackedTextureId id, unsigned int maximumSize, bool useRecommendedMaxSize = true);
			DLL_EXPORT PackedTexture(const PackedTexture& tex) = delete;
			DLL_EXPORT PackedTexture(PackedTexture&& tex) = delete;

			DLL_EXPORT PackedTextureId getId()const;

			DLL_EXPORT void addTexture(TextureId textureId, const sf::Image& image);
			DLL_EXPORT void addTexture(TextureId textureId, const sf::Texture& texture);

			DLL_EXPORT void generate();

			DLL_EXPORT std::vector<sf::Image> renderAsImages()const;

			DLL_EXPORT TextureReference getTextureReference(const TextureId& textureId)const;

			DLL_EXPORT static void packingAlgorithm(std::vector<PackingElement>& elements, const unsigned int maximumTextureSize);

			DLL_EXPORT static const unsigned int RECOMMENDED_MAX_SIZE = 8192;
		};
	}
}
