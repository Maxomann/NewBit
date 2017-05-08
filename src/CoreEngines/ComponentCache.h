#pragma once
#include "stdafx.h"

namespace nb
{
	template<class T>
	class ComponentCache
	{
		std::vector<T*> components;

		Connections connections;

	public:

		void connectToWorld( World* world )
		{
			connectToWorld( *world );
		}

		void connectToWorld( World& world )
		{
			components.clear();
			connections.clear();

			world.s_onEntityAdded.connect_track( connections, [&]( Entity* entity ) {
				T* comp = entity->getComponent_try<T>();
				if (comp != nullptr)
				{
					components.push_back( comp );
					s_componentAdded.call( comp );
				}
			} );

			world.s_onEntitiesRemoved.connect_track( connections, [&]( const std::vector<Entity*>& entities ) {
				std::vector<T*> toRemove;

				for (const auto& entity : entities)
				{
					T* comp = entity->getComponent_try<T>();
					if (comp != nullptr)
					{
						toRemove.push_back( comp );
						s_beforeComponentRemoved.call( comp );
					}
				}

				components.erase( remove_if( components.begin(), components.end(), [&]( const T* el ) -> bool {
					return (find( toRemove.begin(), toRemove.end(), el ) != toRemove.end());
				} ), components.end() );
			} );
		};

		void clear()
		{
			components.clear();
		};

		const std::vector<T*>& get()const
		{
			return components;
		};

		Signal<void( T* )> s_componentAdded;
		Signal<void( T* )> s_beforeComponentRemoved;
	};
}
