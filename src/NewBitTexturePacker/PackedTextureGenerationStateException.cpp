#include "PackedTextureGenerationStateException.h"

nb::tp::exception::PackedTextureGenerationStateException::PackedTextureGenerationStateException( bool state )
	: std::runtime_error( "PackedTextureGenerationStateException: State is: " + std::to_string( state ) + ", expected: " + std::to_string( !state ) )
{}