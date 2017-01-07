#include "PackedTexture.h"
using namespace std;
using namespace sf;

void nb::tp::PackedTexture::m_throwIfGenerated()
{
	if (m_isGenerated)
		throw exception::PackedTextureGenerationStateException(m_id, m_isGenerated);
}

void nb::tp::PackedTexture::m_throwIfNotGenerated()
{
	if (!m_isGenerated)
		throw exception::PackedTextureGenerationStateException(m_id, m_isGenerated);
}

unsigned int nb::tp::PackedTexture::constructMaximumSize(unsigned int maximumSize, bool useRecommendedMaxSize)
{
	if (useRecommendedMaxSize)
	{
		if (maximumSize > nb::tp::PackedTexture::RECOMMENDED_MAX_SIZE)
			return nb::tp::PackedTexture::RECOMMENDED_MAX_SIZE;
		else
			return maximumSize;
	}
	else
		return maximumSize;
}

nb::tp::PackedTexture::PackedTexture(PackedTextureId id, unsigned int maximumSize, bool useRecommendedMaxSize)
	: m_id(id),
	m_maximumSize(constructMaximumSize(maximumSize, useRecommendedMaxSize))
{}

nb::tp::PackedTextureId nb::tp::PackedTexture::getId() const
{
	return m_id;
}

void nb::tp::PackedTexture::addTexture(TextureId textureId, const sf::Image& image)
{
	m_throwIfGenerated();

	sf::Texture texture;
	texture.loadFromImage(image);
	addTexture(textureId, texture);
}

void nb::tp::PackedTexture::addTexture(TextureId textureId, const sf::Texture & texture)
{
	m_throwIfGenerated();

	m_subTextures.emplace_back(textureId, texture);
}

void nb::tp::PackedTexture::generate()
{
	m_throwIfGenerated();

	// check for dublicates
	sort(m_subTextures.begin(), m_subTextures.end(), [](const std::pair<TextureId, sf::Texture>& lhs,
		const std::pair<TextureId, sf::Texture>& rhs) {
		return lhs.first < rhs.first;
	});
	auto uniqueIt = unique(m_subTextures.begin(), m_subTextures.end(), [](const decltype(m_subTextures)::value_type& lhs, const decltype(m_subTextures)::value_type& rhs) {
		return lhs.first == rhs.first;
	});
	// throw if duplicate textures exist
	if (uniqueIt != m_subTextures.end())
	{
		std::vector<TextureId> duplicateTextureIds;
		for (auto it = uniqueIt; it != m_subTextures.end(); ++it)
			duplicateTextureIds.push_back(it->first);
		throw exception::PackedTextureDuplicateException(duplicateTextureIds);
	}

	// generate
	std::vector<PackingElement> subTextureRects;
	// init rects
	for (auto& el : m_subTextures)
	{
		PackingElement pack;
		pack.id = el.first;
		pack.texture = &el.second;
		const auto& textureSize = pack.texture->getSize();
		pack.rect = sf::IntRect(0, 0, textureSize.x, textureSize.y);
		pack.destinationTextureId = 0;

		if (textureSize.x > m_maximumSize || textureSize.y > m_maximumSize)
			throw exception::TextureTooLargeException(pack.id);

		subTextureRects.push_back(pack);
	}

	// sort rects
	packingAlgorithm(subTextureRects, m_maximumSize);

	// prepare texture drawing
	unsigned int highestDestinationTextureId = 0;
	for (const auto& el : subTextureRects)
	{
		if (el.destinationTextureId > highestDestinationTextureId)
			highestDestinationTextureId = el.destinationTextureId;
	}
	for (unsigned int i = 0; i <= highestDestinationTextureId; ++i)
	{
		m_generatedTextures.emplace_back();
		m_generatedTextures.back().create(m_maximumSize, m_maximumSize, false);
	}
	// draw textures
	for (const auto& el : subTextureRects)
	{
		sf::Sprite sprite;
		sprite.setTexture(*el.texture);
		sprite.setPosition(sf::Vector2f((float)el.rect.left, (float)el.rect.top));
		m_generatedTextures.at(el.destinationTextureId).draw(sprite);
	}
	for (auto& el : m_generatedTextures)
		el.display();
	// generate TextureReferences
	for (const auto& el : subTextureRects)
	{
		m_generatedTextureReferences.emplace(
			make_pair(el.id,
				TextureReference(el.id,
					m_generatedTextures.at(el.destinationTextureId).getTexture(),
					sf::Vector2i(el.rect.top, el.rect.left)
				)));
	}
	// clear m_subTextures
	m_subTextures.clear();

	// set generated flag
	m_isGenerated = true;
}

std::vector<sf::Image> nb::tp::PackedTexture::renderAsImages() const
{
	std::vector<sf::Image> retVal;
	retVal.resize(m_generatedTextures.size());

	for (unsigned int i = 0; i < m_generatedTextures.size(); ++i)
		retVal.at(i) = m_generatedTextures.at(i).getTexture().copyToImage();

	return retVal;
}

nb::tp::TextureReference nb::tp::PackedTexture::getTextureReference(const TextureId & textureId) const
{
	return m_generatedTextureReferences.at(textureId);
}

void nb::tp::PackedTexture::packingAlgorithm(std::vector<PackingElement>& elements,
	const unsigned int maximumTextureSize)
{
	//sort by size
	std::sort(elements.begin(), elements.end(), [](const PackingElement& lhs, const PackingElement& rhs) {
		return ((lhs.rect.height*lhs.rect.width) > (rhs.rect.height*rhs.rect.width));
	});

	std::list<Node> childrenNodeContainer;
	std::vector<Node> textures;
	textures.emplace_back();
	textures.back().rect = IntRect(0, 0, maximumTextureSize, maximumTextureSize);

	for (auto& el : elements)
	{
		int counter = 0;
		bool lastInsertSuccess = false;
		for (auto& tex : textures)
		{
			if (tex.insert(childrenNodeContainer, &el))
			{
				lastInsertSuccess = true;
				el.destinationTextureId = counter;
				break;
			}
			counter++;
		}
		if (!lastInsertSuccess)
		{
			//insert new texture
			textures.emplace_back();
			textures.back().rect = IntRect(0, 0, maximumTextureSize, maximumTextureSize);
			if (textures.back().insert(childrenNodeContainer, &el))
				el.destinationTextureId = counter;//no +1 since counter gets increased by one before here
			else
				throw exception::TextureTooLargeException(el.id);
		}
	}

	return;
}

bool nb::tp::Node::insert(std::list<Node>& storeNodesHere, PackingElement * el)
{
	//fits?
	if (this->rect.width >= this->rect.width && el->rect.height >= el->rect.height)
	{
		//isEmpty?
		if (this->ptr == nullptr)
		{
			//insert here
			this->ptr = el;
			ptr->rect.left = this->rect.left;
			ptr->rect.top = this->rect.top;

			storeNodesHere.emplace_back();
			child[0] = &storeNodesHere.back();
			storeNodesHere.emplace_back();
			child[1] = &storeNodesHere.back();

			//create children
			child[0]->rect.left = this->rect.left + ptr->rect.width;
			child[0]->rect.top = this->rect.top;

			child[1]->rect.left = this->rect.left;
			child[1]->rect.top = this->rect.top + ptr->rect.height;

			child[0]->rect.width = this->rect.width - ptr->rect.width;
			child[0]->rect.height = this->rect.height;

			child[1]->rect.width = this->rect.width;
			child[1]->rect.height = this->rect.height - ptr->rect.height;

			return true;
		}
		else
		{
			//insert in child
			auto dw = this->rect.width - el->rect.width;
			auto dh = this->rect.height - el->rect.height;
			if (dw > dh)
				return child[0]->insert(storeNodesHere, el);
			else
				return child[1]->insert(storeNodesHere, el);
		}
	}


	return false;
}