#include "EntityDoesNotExistException.h"

nb::exception::EntityDoesNotExistException::EntityDoesNotExistException()
	: std::runtime_error( "EntityDoesNotExistException" )
{}
