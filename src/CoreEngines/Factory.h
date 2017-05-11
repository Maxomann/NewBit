#pragma once
#include "stdafx.h"

namespace nb
{
	using FactoryId = unsigned int;
	using FactoryName = std::string;

	template< class T, class ... CreateArgs >
	class Factory
	{
	public:
		using ID = FactoryId;
		using NAME = FactoryName;

	private:
		const ID id;
		const NAME name;

	public:
		Factory( ID id, NAME name )
			:id( id ),
			name( name )
		{};
		virtual ~Factory() = default;

		ID getId()const
		{
			return id;
		};
		const NAME& getName()const
		{
			return name;
		};

		virtual T create( CreateArgs... args )const = 0;
	};
}
