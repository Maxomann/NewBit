#include "SystemDoesNotExistException.h"

nb::entity::exception::SystemDoesNotExistException::SystemDoesNotExistException( const std::string & systemTypeName )
	:std::runtime_error( "SystemDoesNotExistException: TypeName: " + systemTypeName )
{}