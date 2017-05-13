#pragma once
#include "stdafx.h"
#include "LabeledFactory.h"
#include "FactoryManager.h"

namespace nb
{
	template< class FactoryType >
	class LabeledFactoryManager : public FactoryManager<FactoryType>
	{
	public:
		FACTORY_VEC_RAW getFactoriesWithLabels( const std::vector<FactoryLabels>& labels )const
		{
			FACTORY_VEC_RAW retVal;
			for( auto& el : getAllFactories() )
			{
				bool doesFactoryHaveAllLabels = true;
				const auto& labelsOfFactory = el.second->getLabels();
				for( const auto& label : labels )
				{
					auto found = std::find( labelsOfFactory.begin(), labelsOfFactory.end(), label );
					if( found == labelsOfFactory.end() )
					{
						doesFactoryHaveAllLabels = false;
						break;
					}
				}

				if( doesFactoryHaveAllLabels )
					retVal.pushBack( el.second.get() );
			}

			return retVal;
		};
	};
}
