#include "TestSystem.h"

void TestSystem::init( nb::World& world )
{
	has_init = true;
}

void TestSystem::update( nb::World& world )
{
	has_update = true;
}

void TestSystem::destroy( nb::World& world )
{}
