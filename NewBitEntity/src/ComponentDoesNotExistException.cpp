#include "ComponentDoesNotExistException.h"

nb::entity::exception::ComponentDoesNotExistException::ComponentDoesNotExistException( const std::string & componentTypeName )
	: std::runtime_error( "ComponentDoesNotExistException: TypeName: " + componentTypeName )
{}