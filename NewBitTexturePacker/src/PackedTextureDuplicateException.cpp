#include "PackedTextureDuplicateException.h"

nb::tp::exception::PackedTextureDuplicateException::PackedTextureDuplicateException( std::vector<TextureId> duplicateIds )
	: std::logic_error( generateErrorMessage( duplicateIds ) )
{}

std::string nb::tp::exception::PackedTextureDuplicateException::generateErrorMessage( std::vector<TextureId> duplicateIds )
{
	std::stringstream result;
	std::copy( duplicateIds.begin(), duplicateIds.end(), std::ostream_iterator<TextureId>( result, ", " ) );

	return "PackedTextureDuplicateException: DuplicateTextureIds: " + result.str();
}