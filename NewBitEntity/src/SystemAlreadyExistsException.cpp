#include "SystemAlreadyExistsException.h"

nb::entity::exception::SystemAlreadyExistsException::SystemAlreadyExistsException( const std::string & systemTypeName )
	: std::runtime_error( "SystemAlreadyExistsException: TypeName: " + systemTypeName )
{}