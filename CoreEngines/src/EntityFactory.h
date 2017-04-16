#pragma once
#include "stdafx.h"

namespace nb
{
	class ResourceEngine;

	class EntityFactory
	{
	public:
		using ID = unsigned int;
		using NAME = std::string;
		using LABELS = std::vector<std::string>;

	private:
		ID id;
		NAME name;
		LABELS labels;

	public:
		EntityFactory( ID id,
					   NAME name,
					   LABELS labels );

		ID getId()const;
		const NAME& getName()const;
		const LABELS& getLabels()const;

		virtual Entity create( const ResourceEngine& resources )const = 0;
	};
}
