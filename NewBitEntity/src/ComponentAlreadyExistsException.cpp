#include "ComponentAlreadyExistsException.h"

nb::exception::ComponentAlreadyExistsException::ComponentAlreadyExistsException( const std::string & componentTypeName )
	: std::runtime_error( "ComponentAlreadyExistsException: TypeName: " + componentTypeName )
{}
