#include "PackedTextureGenerationStateException.h"

nb::tp::exception::PackedTextureGenerationStateException::PackedTextureGenerationStateException( PackedTextureId id, bool state )
	: std::runtime_error( "PackedTextureGenerationStateException: PackedTextureId: " + std::to_string( id ) + " State is: " + std::to_string( state ) + ", expected: " + std::to_string( !state ) )
{}