#pragma once
#include "stdafx.h"
#include "EntityFactory.h"
#include "EntityFactories.h"
#include "FactoryManager.h"
#include "LabeledFactoryManager.h"

namespace nb
{
	class EntityFactoryManager : public LabeledFactoryManager<EntityFactory>
	{
	public:
		void init();
	};
}
