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
	std::vector<std::string> imagesIds;

	// Load all test images
	for( auto& p : filesystem::directory_iterator( "data/TexturePackerTestImages" ) )
	{
		auto& path = p.path();
		if( path.extension() == ".png" )
		{
			imagesToPack.emplace_back();
			imagesToPack.back().loadFromFile( path.string() );
			imagesIds.push_back( path.filename().string() );
			cout << "Load image: " << path.string() << endl;
		}
	}

	auto maxTexSize = sf::Texture::getMaximumSize();
	cout << "MaxTextureSize: " << maxTexSize << endl;
	nb::tp::PackedTexture packedTexture( 4096 );
	unsigned int imagesToPackCounter = 0;
	for( const auto& el : imagesToPack )
	{
		packedTexture.addTexture( imagesIds.at( imagesToPackCounter ), el );
		imagesToPackCounter++;
	}
	packedTexture.generate();

	ofstream file;
	file.open( "data/TexturePackerTestImages/result/_debug_info.json", ios::out | ios::trunc );
	file << std::setw( 4 ) << packedTexture._debug_info() << std::endl;
	file.close();

	const auto renderResult = packedTexture.renderAsImages();
	unsigned int count = 0;
	for( const auto& el : renderResult )
	{
		el.saveToFile( "data/TexturePackerTestImages/result/result_image" + std::to_string( count ) + ".png" );
		count++;
	}
}
