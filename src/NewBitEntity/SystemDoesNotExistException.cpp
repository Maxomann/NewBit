#include "SystemDoesNotExistException.h"

nb::exception::SystemDoesNotExistException::SystemDoesNotExistException( const std::string & systemTypeName )
	:std::runtime_error( "SystemDoesNotExistException: TypeName: " + systemTypeName )
{}
