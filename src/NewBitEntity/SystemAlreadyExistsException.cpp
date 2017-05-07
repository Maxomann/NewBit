#include "SystemAlreadyExistsException.h"

nb::exception::SystemAlreadyExistsException::SystemAlreadyExistsException( const std::string & systemTypeName )
	: std::runtime_error( "SystemAlreadyExistsException: TypeName: " + systemTypeName )
{}
