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
		using FACTORY_PTR_RAW = FactoryType*;
		using FACTORIES = std::map<FactoryId, FACTORY_PTR>;
		using FACTORY_VEC_RAW = std::vector<FACTORY_PTR_RAW>;

	private:
		FACTORIES factories;

	public:
		void addFactory( FACTORY_PTR factory )
		{
			factories.emplace( make_pair( factory->getId(), move( factory ) ) );
		};

		const FACTORY_PTR_RAW getFactoryById( FactoryId id )const
		{
			return factories.at( id ).get();
		};

		const FACTORIES& getAllFactories()const
		{
			return factories;
		};
	};
}
