#include "stdafx.h"

using namespace std;
using namespace experimental;

SUITE( NewBitTexturePacker )
{
	TEST( PackSomeTextures )
	{}
}

int main()
{
	std::list<sf::Image> imagesToPack;

	// Load all test images
	for ( auto& p : filesystem::directory_iterator( "data/TexturePackerTestImages" ) )
	{
		auto& path = p.path();
		if ( path.extension() == ".png" )
		{
			imagesToPack.emplace_back();
			imagesToPack.back().loadFromFile( path.string() );
			cout << "Load image: " << path.string() << endl;
		}
	}

	auto maxTexSize = sf::Texture::getMaximumSize();
	cout << "MaxTextureSize: " << maxTexSize << endl;
	nb::tp::PackedTexture packedTexture( 0, 4096 );
	nb::tp::TextureId texId = 0;
	for ( const auto& el : imagesToPack )
	{
		packedTexture.addTexture( texId, el );
		texId++;
	}
	packedTexture.generate();

	auto& renderResult = packedTexture.renderAsImages();
	unsigned int count = 0;
	for ( const auto& el : renderResult )
	{
		el.saveToFile( "data/TexturePackerTestImages/result/result_image" + std::to_string( count ) + ".png" );
		count++;
	}
}