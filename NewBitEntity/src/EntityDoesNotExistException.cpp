#include "EntityDoesNotExistException.h"

nb::entity::exception::EntityDoesNotExistException::EntityDoesNotExistException()
	: std::runtime_error( "EntityDoesNotExistException" )
{}