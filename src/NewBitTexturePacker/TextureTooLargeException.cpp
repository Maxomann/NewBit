#include "TextureTooLargeException.h"

nb::tp::exception::TextureTooLargeException::TextureTooLargeException( TextureId textureId )
	: std::logic_error( "TextureTooLargeException: TextureId: " + textureId )
{}