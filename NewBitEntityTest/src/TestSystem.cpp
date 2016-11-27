#include "TestSystem.h"

TestSystem::TestSystem()
	: nb::entity::System( this )
{}

void TestSystem::init( const nb::entity::SystemManager & systemManager, const nb::entity::EntityManager & entityManager )
{
	has_init = true;
}

void TestSystem::update( const nb::entity::SystemManager & systemManager, const nb::entity::EntityManager & entityManager )
{
	has_update = true;
}

void TestSystem::destroy( const nb::entity::SystemManager & systemManager, const nb::entity::EntityManager & entityManager )
{}