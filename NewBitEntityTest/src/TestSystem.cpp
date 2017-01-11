#include "TestSystem.h"

TestSystem::TestSystem()
	: nb::System( this )
{}

void TestSystem::init( const nb::SystemManager & systemManager, const nb::EntityManager & entityManager )
{
	has_init = true;
}

void TestSystem::update( const nb::SystemManager & systemManager, const nb::EntityManager & entityManager )
{
	has_update = true;
}

void TestSystem::destroy( const nb::SystemManager & systemManager, const nb::EntityManager & entityManager )
{}
