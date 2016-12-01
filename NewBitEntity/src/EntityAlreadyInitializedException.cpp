#include "EntityAlreadyInitializedException.h"

nb::entity::exception::EntityAlreadyInitializedException::EntityAlreadyInitializedException()
	: std::runtime_error( "EntityAlreadyInitializedException" )
{}