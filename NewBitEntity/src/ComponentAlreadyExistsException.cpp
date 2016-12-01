#include "ComponentAlreadyExistsException.h"

nb::entity::exception::ComponentAlreadyExistsException::ComponentAlreadyExistsException( const std::string & componentTypeName )
	: std::runtime_error( "ComponentAlreadyExistsException: TypeName: " + componentTypeName )
{}