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
		using FACTORY_VEC_RAW = std::vector<FactoryType*>;

	private:
		FACTORIES factories;

	public:
		void addFactory( FACTORY_PTR factory )
		{
			factories.emplace( make_pair( factory->getId(), move( factory ) ) );
		};

		const FACTORY_PTR& getFactoryById( FactoryId id )const
		{
			return factories.at( id );
		};

		const FACTORIES& getAllFactories()const
		{
			return factories;
		};
	};
}
