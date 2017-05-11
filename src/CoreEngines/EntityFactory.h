#pragma once
#include "stdafx.h"
#include "Factory.h"

namespace nb
{
	class ResourceEngine;

	class EntityFactory : public Factory<Entity, const ResourceEngine&>
	{
	public:
		using LABELS = std::vector<std::string>;

	private:
		LABELS labels;

	public:
		EntityFactory( ID id,
					   NAME name,
					   LABELS labels );

		const LABELS& getLabels()const;
	};
}
