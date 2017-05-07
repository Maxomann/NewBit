#include "EntityAlreadyInitializedException.h"

nb::exception::EntityAlreadyInitializedException::EntityAlreadyInitializedException()
	: std::runtime_error( "EntityAlreadyInitializedException" )
{}
