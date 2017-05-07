#pragma once
#include "stdafx.h"
#include "EntityFactory.h"
#include "EntityFactories.h"

namespace nb
{
	class EntityFactoryManager
	{
	public:
		using FACTORY_PTR = std::unique_ptr<EntityFactory>;
		using FACTORIES = std::map<EntityFactory::ID, FACTORY_PTR>;

	private:
		FACTORIES factories;

	public:
		void init();

		void addFactory( FACTORY_PTR factory );

		const FACTORY_PTR& getFactoryById( EntityFactory::ID id )const;

		const FACTORIES& getAllFactories()const;
	};
}
