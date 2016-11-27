#pragma once
#include "stdafx.h"
#include "System.h"
#include "SystemAlreadyExistsException.h"
#include "SystemDoesNotExistException.h"
#include "SystemManagerAlreadyInitializedException.h"

namespace nb
{
	namespace entity
	{
		class EntityManager;

		class SystemManager
		{
			EntityManager* r_entityManager;

			std::unordered_map<std::type_index, std::unique_ptr<System>> m_systems;

			bool m_isInit = false;

		protected:
			void updateSystems();

		public:
			SystemManager( EntityManager& entityManager );

			template < class T >
			System* addSystem()
			{
				auto system = std::make_unique<T>();

				if ( m_isInit )
					system->init( *this, *r_entityManager );

				const auto& type = system->type;

				auto insertResult = m_systems.insert( std::make_pair( type, std::move( system ) ) );
				if ( !insertResult.second )
				{
					throw exception::SystemAlreadyExistsException( type.name() );
				}
				return insertResult.first->second.get();
			};

			template < class T >
			System* getSystem()const
			{
				const typeIndex = std::type_index( typeid( T ) );
				try
				{
					return m_systems.at( typeIndex ).get();
				}
				catch ( std::out_of_range )
				{
					throw exception::SystemDoesNotExistException( typeIndex.name() );
				}
			};

			template < class T >
			void removeSystem()
			{
				const typeIndex = std::type_index( typeid( T ) );
				try
				{
					auto& system = m_systems.at( typeIndex );
					system->destroy( *this, *r_entityManager );
					m_systems.erase( typeIndex );
				}
				catch ( std::out_of_range )
				{
					throw exception::SystemDoesNotExistException( typeIndex.name() );
				}
			};

			void initSystems();
		};
	}
}