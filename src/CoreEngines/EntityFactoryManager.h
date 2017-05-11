#pragma once
#include "stdafx.h"
#include "EntityFactory.h"
#include "EntityFactories.h"
#include "FactoryManager.h"

namespace nb
{
	class EntityFactoryManager : public FactoryManager<EntityFactory>
	{
	public:
		void init();
	};
}
