#pragma once
#include "stdafx.h"
#include "Factory.h"

namespace nb
{
	template< class FactoryType >
	class FactoryManager
	{
	public:
		using FACTORY_PTR = std::unique_ptr<FactoryType>;
		using FACTORIES = std::map<FactoryId, FACTORY_PTR>;

	private:
		FACTORIES factories;

	public:
		void addFactory( FACTORY_PTR factory )
		{
			factories.emplace( make_pair( factory->getId(), move( factory ) ) );
		};

		const FACTORY_PTR& getFactoryById( EntityFactory::ID id )const
		{
			return factories.at( id );
		};

		const FACTORIES& getAllFactories()const
		{
			return factories;
		};
	};
}
