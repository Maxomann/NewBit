#pragma once
#include "stdafx.h"
#include "Factory.h"

namespace nb
{
	using FactoryLabels = std::vector<std::string>;

	template< class T, class ... CreateArgs >
	class LabeledFactory : public Factory< T, CreateArgs... >
	{
	public:
		using LABELS = FactoryLabels;

	private:
		LABELS labels;

	public:
		LabeledFactory( ID id,
						NAME name,
						LABELS labels )
			: Factory<T, CreateArgs...>( id, move( name ) ),
			labels( move( labels ) )
		{};
		virtual ~LabeledFactory() = default;

		const LABELS& getLabels()const
		{
			return labels;
		};
	};
}
